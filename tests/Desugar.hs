module Desugar where

import SRA
import Data.List
import Debug.Trace

desugar :: TableMap -> SRA -> RA
-- desugaring a table name means looking up the table, which
-- will be a list of (name, type) pairs, and creating a list
-- of expressions from those pairs, where each expression is
-- a single column (toExpr)
desugar tables (TableName name Nothing) = case tLookup name tables of
  Just cols -> Table name cols
  Nothing -> error $ "No table named " ++ name

desugar tables (TableName name (Just n)) = 
  -- if there is a table alias given, we wrap our table in a Rho
  -- operator.
  RhoTable n $ desugar tables (TableName name Nothing)

desugar tables (Project nes sra) =
  -- desugaring a projection, we need to get the list of expressions
  -- we want to project, and then apply a rho operator for each one
  -- in the list that has an alias. We also need to check for *s.
  let 
    ra = desugar tables sra
    -- get whatever we need to project, meaning fst of each (String, Type)
    toProject = (map fst nes)
    expand :: RA -> [Expression]
    -- expand returns a list of all of the expressions in an RA
    expand ra = map (\(n,_) -> Col n Nothing) $ getCols ra
    -- starExpand replaces any stars in a list with their expressions
    starExpand [] = []
    -- later we'll specifically address t.* vs u.*
    starExpand ((Col "*" _):es) = expand ra ++ starExpand es
    starExpand (e:es) = e : starExpand es
    -- build the full star-expanded Pi statement
    project = Pi (starExpand toProject) ra
    doRename :: [NamedExpr] -> RA -> RA
    -- if we have a renaming, we need to apply a rho operator
    doRename ((e, Just n):nes) ra = Rho e n (doRename nes ra)
    -- if we have an expression which is not renamed, don't add anything
    doRename ((_, Nothing):nes) ra = doRename nes ra
    -- if no more expressions to do, return RA
    doRename [] ra = ra
  in
  doRename nes project

-- desugaring a select operator is simple
desugar tables (Select cond sra) = Sigma cond (desugar tables sra)

desugar tables (Join Inner l r jc) = 
  -- for an Inner join, it's a cross product but it might have a join
  -- condition specified, which would mean a Sigma operator.
  let (raL, raR) = (desugar tables l, desugar tables r) in
  case jc of
    Nothing -> Cross raL raR
    Just cond -> Sigma cond $ Cross raL raR

desugar tables (NaturalJoin l r) =
  -- we have this formula from wikipedia for the natural join:
  -- L ⋈ R = 
  --    π([l1,..lN ∪ r1,..,rN], 
  --       σ(l.a1 = r.a1 ^ l.a2 = r.a2 ^ ... ^ r.aN = l.aN, 
  --          (L × R)))
  -- in other words, we find all of the columns that they have in common,
  -- and select on equality on those columns, and then project the union of
  -- columns (so no repetition)
  let
    (raL, raR) = (desugar tables l, desugar tables r)
    cross = (Cross raL raR)
    (colsL, colsR) = (getCols raL, getCols raR)
    -- get list of columns in both and those in either
    inBoth = colsL `intersect` colsR
    inEither = colsL `union` colsR
    -- to construct the equalities, we need to perform this transformation
    -- Col "foo" Nothing -> 
    --   Compare "=" (Col "foo" (Just "l")) (Col "foo" (Just "r"))
    -- this means that we need to know the names of the L and R tables
    (lName, rName) = (getName raL, getName raR)
    trans (n, _) = Compare "=" (Col n $ Just lName) (Col n $ Just rName)
    eqs = map trans inBoth
  in
  -- if no columns in common, then it's just a cross product
  if inBoth == [] then cross 
    -- otherwise, AND all of the equality statements together, put it in a
    -- Sigma statement, and project whichever columns are in either
    else Pi (map colToExpr $ inEither)
      (Sigma (foldr1 (BinaryCond "and") eqs) cross)

-- for left/right outer joins, we have some magic juju identities...
desugar tables (Join LeftOuter l r jc) =
  -- Wikipedia states that L (left outer join) R can be expressed as
  -- L loj R = (L ⋈ R) ∪ ((L - π([l1,..,lN], L ⋈ R))×{(ω,..,ω)})
  -- where [l1,..,lN] are attributes of L, and ωs are a relation consisting
  -- of the columns which are in R but not in L.
  let
    (raL, raR) = (desugar tables l, desugar tables r)
    (colsL, colsR) = (getCols raL, getCols raR)
    exprsL = map colToExpr colsL
    inRightOnly = colsR \\ colsL -- (\\) is set difference
    ω = Table "ω" inRightOnly
    natJoin = (desugar tables $ NaturalJoin l r)
    res = Union natJoin (Cross (Diff (raL) (Pi exprsL natJoin)) ω)
  in
  case jc of Nothing -> res
             Just cond -> Sigma cond res

-- right outer same as above but swapped
desugar tables (Join RightOuter l r jc) =
  let 
    (raL, raR) = (desugar tables l, desugar tables r)
    (colsL, colsR) = (getCols raL, getCols raR)
    exprsR = map colToExpr colsR
    inLeftOnly = colsL \\ colsR
    ω = Table "ω" inLeftOnly
    natJoin = (desugar tables $ NaturalJoin l r)
    res = Union natJoin (Cross (Diff (raR) (Pi exprsR natJoin)) ω)
  in
  case jc of Nothing -> res
             Just cond -> Sigma cond res

-- full outer join can be defined as (L foj R) = (L loj R) U (L roj R)
desugar tables (Join FullOuter l r jc) = 
  let
    oj typ = desugar tables (Join typ l r Nothing)
    res = (oj LeftOuter) `Union` (oj RightOuter)
  in
  case jc of Nothing -> res
             Just cond -> Sigma cond res

desugar tables (SRAUnion l r) = (desugar tables l) `Union` (desugar tables r)
desugar tables (Intersect l r) = 
  let (raL, raR) = (desugar tables l, desugar tables r) in
  (raL `Union` raR) `Diff` (raL `Diff` raR) `Diff` (raR `Diff` raL)
desugar tables (Except l r) = (desugar tables l) `Diff` (desugar tables r)


-- convenience function which creates an expression out of a column
colToExpr :: (String, Type) -> Expression
colToExpr (n,_) = Col n Nothing

getName :: RA -> String
-- throws an error if RA is not either a Table or a RhoTable
getName (Table name _) = name
getName (RhoTable name _) = name
getName _ = error "Every derived table must have its own alias"

getCols :: RA -> [Column]
-- getCols will return a list of (String, Type) from any table;
-- a.k.a. the names and types of the columns to be found in this table.

-- in the simplest case, we already know the answer
getCols (Table name cols) = cols

-- when we have a project, we are specifying the names of columns to be
-- carried through. We simply use the show function to get a string
-- representation of the expression. Table name qualifiers will be kept.
getCols (Pi exprs ra) = map toCols exprs where
  toCols expr = (show expr, getType expr ra)

-- to get the columns of a renamed table, we first get the columns
-- of its subtable. Then, say we're renaming x+y to z. We find the column
-- called x+y and store it instead as z. Others, we don't touch.
getCols (Rho e s ra) = 
  let 
    cols = getCols ra
    rename :: Column -> Column
    rename (cName, t) = if cName == show e then (show e, t) else (cName, t)
  in
  map rename cols

-- renaming a table doesn't change the name of its columns, so we leave it
getCols (RhoTable _ ra) = getCols ra

-- similarly with a selection
getCols (Sigma _ ra) = getCols ra

-- in a union or difference, we require the columns be the same, so we make
-- sure that's the case and if so, we return it.
getCols (Union l r) =
  let (colsL, colsR) = (getCols l, getCols r) in
  if colsL == colsR then colsL 
    else error $ "Mismatched attributes: " ++ show (getCols l) ++ 
                   " != " ++ show (getCols r)

-- difference is same as union here.
getCols (Diff l r) = getCols (Union l r)

-- with a cross product, the columns will be concatenated.
getCols (Cross l r) = getCols l ++ getCols r


getType :: Expression -> RA -> Type
-- Small type checking function for getCols; also will report type
-- mismatch errors or non-existent columns.
getType (Col name _) ra = case lookup name (getCols ra) of
  -- todo: examine cases where table name is specified
  Just t -> t
  Nothing -> error $ "Column " ++ name ++ " does not exist" 
getType (Neg e) ra = case getType e ra of
  Int -> Int
  String -> error "Can't apply (-) to a string"
getType (Binary "||" e1 e2) ra = 
  case (getType e1 ra, getType e2 ra) of
    (String, String) -> String
    otherwise -> error "Can't concat anything but strings"
getType (Binary op e1 e2) ra = 
  let (t1, t2) = (getType e1 ra, getType e2 ra) in
  if t1 == t2 then t1 else error $ "Mismatched types in " ++ op
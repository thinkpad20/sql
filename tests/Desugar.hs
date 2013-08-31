module Desugar where

import SRA
import Data.List

desugar :: TableMap -> SRA -> RA

-- desugaring a table name means looking up the table, which
-- will be a list of (name, type) pairs, and creating a list
-- of expressions from those pairs, where each expression is
-- a single column (toExpr)
desugar tables (TableName name Nothing) = case tLookup name tables of
  Just cols -> Table name cols
  Nothing -> error $ "No table named " ++ name

-- if there is a table alias given, we wrap our table in a Rho
-- operator.
desugar tables (TableName name (Just n)) = 
  RhoTable n $ desugar tables (TableName name Nothing)

-- desugaring a projection, we need to get the list of expressions
-- we want to project, and then apply a rho operator for each one
-- in the list that has an alias. We also need to check for *s.
desugar tables (Project nes sra) =
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
     -- if no more expressions to do, return RA
    doRename [] ra = ra
    -- if we have an expression which is not renamed, don't add anything
    doRename ((_, Nothing):nes) ra = doRename nes ra
    -- if we have a renaming, now we need to apply a rho operator
    doRename ((e, Just n):nes) ra = Rho e n (doRename nes ra)
  in
  doRename nes project

-- desugaring a select operator is simple
desugar tables (Select cond sra) = Sigma cond (desugar tables sra)

-- for an Inner join, it's a cross product but it might have a join
-- condition specified, which would mean a Sigma operator.
desugar tables (Join Inner l r jc) = 
  let (raL, raR) = (desugar tables l, desugar tables r) in
  case jc of
    Nothing -> Cross raL raR
    Just cond -> Sigma cond $ Cross raL raR

-- for left/right outer joins, we need to see what columns the two tables
-- have in common.
desugar tables (Join LeftOuter l r jc) =
  let 
    -- Wikipedia states that L (left outer join) R can be expressed as
    -- (L ⋈ R) ∪ ((L - π(l1,..,lN, L ⋈ R))×{(ω,..,ω)})
    -- where l1,..,lN are attributes of L, and ωs are a relation consisting
    -- of the columns which are in R but not in L.
    (raL, raR) = (desugar tables l, desugar tables r)
    natJoin = (desugar tables $ NaturalJoin l r)
    (colsL, colsR) = (getCols raL, getCols raR)
    exprsL = map (\(n,t) -> Col n Nothing) colsL
    inRightOnly = colsR \\ colsL
    ω = Table "ω" inRightOnly
  in
  Union natJoin (Cross (Difference (raL) (Pi exprsL natJoin)) ω)


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
getCols (Difference l r) = getCols (Union l r)

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
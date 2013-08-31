module Desugar where

import SRA
import Data.List
import qualified Data.Map as M
import Control.Monad (forM_)

{------------------- Example queries/tables -------------------}
tables :: M.Map String [(String, Type)]
t = [("x", Int), ("y", Int)]
u = [("x", Int), ("y", Int), ("z", Int)]
tables = M.fromList [("t", t), ("u", u)]

tblT = (TableName "t" Nothing)
tblU = (TableName "u" Nothing)
-- select x, y from t;
ex0 = Project [(Col "x" Nothing, Nothing), (Col "y" Nothing, Nothing)] tblT

-- select x, x + y as z from t;
ex1 = Project [(Col "x" Nothing, Nothing), 
                (Binary "+" (Col "x" Nothing) (Col "y" Nothing), Just "z")] 
                  tblT

-- select z from (select x, x+y as z from t);
ex2 = Project [(Col "z" Nothing, Nothing)] ex1

-- select x, z from (select x, x+y as z from t) where x = z;
ex3 = Project [(Col "x" Nothing, Nothing), (Col "z" Nothing, Nothing)] $
       Select (Compare "=" (Col "x" Nothing) (Col "z" Nothing)) ex1

-- select x, y, z as foo from u;
ex4 = Project [(Col "x" Nothing, Nothing),
               (Col "y" Nothing, Nothing),
               (Col "z" Nothing, Just "foo")] tblU

-- select * from u;
ex5 = Project [(Col "*" Nothing, Nothing)] tblU

-- select * from t, u;
ex6 = Project [(Col "*" Nothing, Nothing)] $ Join Inner tblT tblU Nothing

-- select * from t,u where t.x = u.x;
ex7 = Project [(Col "*" Nothing, Nothing)] $
        Join Inner tblT tblU $ 
          Just $ Compare "=" (Col "x" $ Just "t") (Col "x" $ Just "u")

examples = [ex0, ex1, ex2, ex3, ex4, ex5, ex6, ex7]

runTests = forM_ examples (putStrLn . show . desugar) 

desugar :: SRA -> RA
-- desugaring a table name means looking up the table, which
-- will be a list of (name, type) pairs, and creating a list
-- of expressions from those pairs, where each expression is
-- a single column (toExpr)
desugar (TableName name Nothing) = case M.lookup name tables of
  Just cols -> Table name cols
  Nothing -> error $ "No table named " ++ name

-- if there is a table alias given, we wrap our table in a Rho
-- operator.
desugar (TableName name (Just n)) = 
  RhoTable n $ desugar $ TableName name Nothing
-- desugaring a projection, we need to get the list of expressions
-- we want to project, and then apply a rho operator for each one
-- in the list that has an alias. We also need to check for *s.
desugar (Project nes sra) =
  let 
    ra = desugar sra
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
    -- if we have an expression, but not renamed, no need to add anything
    doRename ((_, Nothing):nes) ra = doRename nes ra
    -- if we have a renaming, now we need to apply a rho operator
    doRename ((e, Just n):nes) ra = Rho e n (doRename nes ra)
  in
  doRename nes project
-- desugaring a select operator is simple
desugar (Select cond sra) = Sigma cond (desugar sra)
-- for an Inner join, it's a cross product but it might have a join
-- condition specified, which would mean a Sigma operator.
desugar (Join Inner l r jc) = 
  let (raL, raR) = (desugar l, desugar r) in
  case jc of
    Nothing -> Cross raL raR
    Just cond -> Sigma cond $ Cross raL raR


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
    newCols = map rename cols
  in
  newCols

-- renaming a table doesn't change the name of its columns, so we leave it
getCols (RhoTable _ ra) = getCols ra

-- similarly with a selection
getCols (Sigma _ ra) = getCols ra

-- in a union or difference, we require the columns be the same, so we make
-- sure that's the case and if so, we return it.
getCols (Union l r) =
  let 
    colsL = getCols l
    colsR = getCols r
  in
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
  let 
    t1 = getType e1 ra
    t2 = getType e2 ra
  in
  if t1 == t2 then t1 else error $ "Mismatched types in " ++ op
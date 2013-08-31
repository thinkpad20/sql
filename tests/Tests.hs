module Tests where

import Desugar
import SRA
import Control.Monad (forM_)

{------------------- Example queries/tables -------------------}
t = [("x", Int), ("y", Int)]
u = [("x", Int), ("y", Int), ("z", Int)]
tables :: TableMap
tables = tFromList [("t", t), ("u", u)]

-- simplifying things...
selectStar = Project [(Col "*" Nothing, Nothing)]
col x = Col x Nothing
dot tname colname = Col colname (Just tname)
colN x = (col x, Nothing)
as :: Expression -> String -> NamedExpr
as expr name = (expr, Just name)
plus = Binary "+"
eq = Compare "="
innerJoin t u = Join Inner t u Nothing
innerJoinOn t u cond = Join Inner t u (Just cond)

-- t;
tblT = (TableName "t" Nothing)
-- u;
tblU = (TableName "u" Nothing)
-- select x, y from t;
ex0 = Project [colN "x", colN "y"] tblT

-- select x, x + y as z from t;
ex1 = Project [colN "x", ((col "x" `plus` col "y") `as` "z")] tblT

-- select z from (select x, x+y as z from t);
ex2 = Project [colN "z"] ex1

-- select x, z from (select x, x+y as z from t) where x = z;
ex3 = Project [colN "x", colN "z"] $ Select (col "x" `eq` col "z") ex1

-- select x, y, z as foo from u;
ex4 = Project [colN "x", colN "y", col "z" `as` "foo"] tblU

-- select * from u;
ex5 = selectStar tblU

-- select * from t, u;
ex6 = selectStar $ tblT `innerJoin` tblU

-- select * from t,u where t.x = u.x;
ex7 = selectStar $ innerJoinOn tblT tblU (("t" `dot` "x") `eq` ("u" `dot` "x"))

-- select * from t natural join u;
ex8 = selectStar (tblT `NaturalJoin` tblU)

examples = [ex0, ex1, ex2, ex3, ex4, ex5, ex6, ex7, ex8]

runTests = forM_ examples (putStrLn . show . desugar tables) 
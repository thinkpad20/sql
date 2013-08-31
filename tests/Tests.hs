module Tests where

import Desugar
import SRA
import Control.Monad (forM_)

{------------------- Example queries/tables -------------------}
t = [("x", Int), ("y", Int)]
u = [("x", Int), ("y", Int), ("z", Int)]
tables :: TableMap
tables = tFromList [("t", t), ("u", u)]

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

runTests = forM_ examples (putStrLn . show . desugar tables) 
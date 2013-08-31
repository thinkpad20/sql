module SRA where

import qualified Data.Map as M

data Type = Int | String deriving (Show, Eq)

type Column = (String, Type)
type TableMap = M.Map String [Column]
type NamedExpr = (Expression, Maybe String)

-- second string is optional table's name
data Expression = Col String (Maybe String)
           | Binary String Expression Expression
           | Neg Expression
           deriving (Eq)

data Condition = Bool Bool
               | Compare String Expression Expression
               | BinaryCond String Condition Condition
               | Not Condition
               deriving (Eq)

data JoinType = Inner
              | LeftOuter
              | RightOuter
              | FullOuter
              deriving (Eq, Show)

data SRA = TableName String (Maybe String)
      | Project [NamedExpr] SRA
      | Select Condition SRA
      | NaturalJoin SRA SRA
      | Join JoinType SRA SRA (Maybe Condition)
      | SRAUnion SRA SRA
      | Intersect SRA SRA
      | Except SRA SRA
      deriving (Eq)

data RA = Table String [Column]
      | Pi [Expression] RA
      | Rho Expression String RA
      | RhoTable String RA
      | Sigma Condition RA
      | Union RA RA
      | Diff RA RA
      | Cross RA RA
      deriving (Show, Eq)

instance Show Expression where
  show (Col name Nothing) = name
  show (Col name (Just tname)) = tname ++ "." ++ name
  show (Binary op ex1 ex2) = show ex1 ++ op ++ show ex2
  show (Neg ex) = "-(" ++ show ex ++ ")" 

instance Show SRA where
  show (TableName name Nothing) = name
  show (TableName name (Just n) ) = name ++ " as " ++ n
  show (Project es sra) = "select " ++ show es ++ " from (" ++ show sra ++ ")"
  show (Select cond sra) = show sra ++ " where " ++ show cond
  show (NaturalJoin l r) = "(" ++ show l ++ ") ⋈ (" ++ show r ++ ")"
  show (Join t l r cond) = "(" ++ show l ++ ") " ++ show t ++ 
                            " join (" ++ show r ++ ")" ++ c
    where c = case cond of
                Nothing -> ""
                Just co -> " on " ++ show co
  show (SRAUnion l r) = show l ++ " union " ++ show r
  show (Except l r) = show l ++ " except " ++ show r

instance Show Condition where
  show (Bool b) = show b
  show (Compare op e1 e2) = show e1 ++ op ++ show e2
  show (BinaryCond op c1 c2) = "(" ++ show c1 ++ " " ++
                                 op ++ " " ++ show c2 ++ ")"
  show (Not c) = "not (" ++ show c ++ ")"


tLookup :: String -> TableMap -> Maybe [Column]
tLookup = M.lookup

tFromList :: [(String,[Column])] -> TableMap
tFromList = M.fromList
module Main where

import Text.ParserCombinators.Parsec
import System.Environment

symbol :: Parser Char
symbol = oneOf "!#$%&|*+-/:<=>?@^_~"

readExpr :: String -> String
readExpr input = case parse symbol "statua" input of
     Left err -> "No match: " ++ show err
     Right val -> "Found value"


main = do
   args <- getArgs
   putStrLn $ readExpr $ args !! 0
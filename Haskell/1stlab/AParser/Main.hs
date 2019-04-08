module Main where
import Grammar(Expr (..))
import Lexer(alexScanTokens)
import Parser(parser)
main :: IO ()
main = do
  string <- getLine
  case parser(alexScanTokens string) of
    Right expr -> putStrLn (show expr)
    Left error -> putStrLn error

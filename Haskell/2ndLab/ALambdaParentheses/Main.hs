module Main where
import Grammar
import Lexer
import Parser
main :: IO ()
main = do
  string <- getContents
  putStrLn (show (parser (alexScanTokens string)))

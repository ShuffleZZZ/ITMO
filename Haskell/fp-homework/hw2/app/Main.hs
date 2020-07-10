module Main
  ( main
  ) where

import System.Directory (getCurrentDirectory)

import InitFS (initFS)

-- | Application entry point, takes path to initialize file-system in.
main :: IO ()
main = do
  putStrLn
    "Enter the FilePath you want to initialize the file-system in (leave empty to init in current directory)"
  path <- getLine
  if path == ""
    then do
      curPath <- getCurrentDirectory
      initFS curPath
    else initFS path

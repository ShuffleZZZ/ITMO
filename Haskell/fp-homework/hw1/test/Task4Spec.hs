module Task4Spec where

import Data.List.NonEmpty (NonEmpty((:|)))
import Test.Hspec

import Task4

spec :: Spec
spec = do
  describe "splitOn" $
    it "splits the list on given separator" $ do
      splitOn '/' "path/to/file"   `shouldBe` ("path" :| ["to", "file"])
      splitOn '/' "path/to/file/"  `shouldBe` ("path" :| ["to", "file", ""])
      splitOn '@' "@path@to@file"  `shouldBe` ("" :| ["path", "to", "file"])
      splitOn '/' "/path/to/file/" `shouldBe` ("" :| ["path", "to", "file", ""])

  describe "joinWith" $
    it "concatinate list of chunks with given joiner" $ do
      joinWith '/' ("path" :| ["to", "file"])         `shouldBe` "path/to/file"
      joinWith '/' ("path" :| ["to", "file", ""])     `shouldBe` "path/to/file/"
      joinWith '@' ("" :| ["path", "to", "file"])     `shouldBe` "@path@to@file"
      joinWith '/' ("" :| ["path", "to", "file", ""]) `shouldBe` "/path/to/file/"

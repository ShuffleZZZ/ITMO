module Task3Spec where

import Test.Hspec

import Task3 (append, doubleVal, log2, runWithVar, toHS)

spec :: Spec
spec =
  describe "checks 'HS' functions results" $ do
    it "checking the 'doubleVal' function result" $ do
      runWithVar (0 :: Int) doubleVal `shouldBe` toHS "val is mempty"
      runWithVar "" doubleVal `shouldBe` toHS "val is mempty"
      runWithVar False doubleVal `shouldBe` toHS "val is mempty"

      runWithVar (1 :: Int) doubleVal `shouldBe` toHS "2"
      runWithVar (2 :: Int) doubleVal `shouldBe` toHS "4"
      runWithVar (4 :: Int) doubleVal `shouldBe` toHS "8"

      runWithVar "str" doubleVal `shouldBe` toHS "strstr"
      runWithVar "rts" doubleVal `shouldBe` toHS "rtsrts"

    it "checking the 'log2' function result" $ do
      runWithVar (1 :: Int) log2 `shouldBe` toHS "0"
      runWithVar (2 :: Int) log2 `shouldBe` toHS "1"
      runWithVar (4 :: Int) log2 `shouldBe` toHS "2"
      runWithVar (5 :: Int) log2 `shouldBe` toHS "3"
      runWithVar (8 :: Int) log2 `shouldBe` toHS "3"
      runWithVar (17 :: Int) log2 `shouldBe` toHS "5"

    it "checking the 'append' function result" $ do
      runWithVar (1 :: Int) append `shouldBe` toHS "1extra"
      runWithVar (1 :: Double) append `shouldBe` toHS "1.0extra"
      runWithVar "str" append `shouldBe` toHS "strextra"

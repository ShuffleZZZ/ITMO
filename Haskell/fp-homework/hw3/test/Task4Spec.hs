module Task4Spec where

import Test.Hspec

import Task3 (append, doubleVal, log2)
import Task4 (printFunc)

log2Str :: String
log2Str = "function(x0) {\n  let x1;\n  let x2 = 1;\n  let x3 = 1;\n"
  <> "  let x4 = 0;\n  x1 = (x4);\n  while (x0 > (x2)) {\n"
  <> "    x2 = (x2) + (x2);\n    x1 = (x1) + (x3);\n  }\n  return x1;\n}\n"

doubleValStr :: String
doubleValStr = "function(x0) {\n  let x1;\n  let x2 = \"\";\n"
  <> "  let x3 = \"val is mempty\";\n  x2 = x0 + x0;\n  if (x0 === (x2)) {\n"
  <> "    x1 = (x3);\n  } else {\n    x1 = (x2);\n  }\n  return x1;\n}\n"

appendStr :: String
appendStr = "function(x0) {\n  let x1;\n  let x2 = \"extra\";\n"
  <> "  x1 = x0 + (x2);\n  return x1;\n}\n"

spec :: Spec
spec =
  describe "checks 'toString' function functionality" $ do
    it "checking the 'doubleVal' function representation" $ do
      printFunc doubleVal `shouldBe` doubleValStr

    it "checking the 'log2' function representation" $ do
      printFunc log2 `shouldBe` log2Str

    it "checking the 'append' function representation" $ do
      printFunc append `shouldBe` appendStr

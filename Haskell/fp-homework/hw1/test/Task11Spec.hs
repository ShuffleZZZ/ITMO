module Task11Spec where

import Test.Hspec

import Task11

spec :: Spec
spec =
  describe "check easy combined parsers" $ do
    it "checking the 'balancedParentheses' parser" $ do
      runParser balancedParentheses ""         `shouldBe` Just ((), [])
      runParser balancedParentheses "()"       `shouldBe` Just ((), [])
      runParser balancedParentheses "()()"     `shouldBe` Just ((), [])
      runParser balancedParentheses "(()())"   `shouldBe` Just ((), [])
      runParser balancedParentheses "(()())()" `shouldBe` Just ((), [])

      runParser balancedParentheses "(("    `shouldBe` Nothing
      runParser balancedParentheses "(()"   `shouldBe` Nothing
      runParser balancedParentheses "())"   `shouldBe` Nothing
      runParser balancedParentheses ")"     `shouldBe` Nothing
      runParser balancedParentheses "()()(" `shouldBe` Nothing

    it "checking the 'int' parser" $ do
      runParser int "1"     `shouldBe` Just (1, [])
      runParser int "12"    `shouldBe` Just (12, [])
      runParser int "1234"  `shouldBe` Just (1234, [])
      runParser int "+1234" `shouldBe` Just (1234, [])
      runParser int "-1234" `shouldBe` Just (-1234, [])
      runParser int "-12a34" `shouldBe` Just (-12, "a34")
      runParser int "1+4"    `shouldBe` Just (1,"+4")
      runParser int "1-27"   `shouldBe` Just (1,"-27")

      runParser int ""         `shouldBe` Nothing
      runParser int "-"        `shouldBe` Nothing
      runParser int "-+"       `shouldBe` Nothing
      runParser int "+"        `shouldBe` Nothing
      runParser int "++"       `shouldBe` Nothing
      runParser int "abc"      `shouldBe` Nothing
      runParser int "abc42"    `shouldBe` Nothing


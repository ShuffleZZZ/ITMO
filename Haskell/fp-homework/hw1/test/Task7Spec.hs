module Task7Spec where

import Test.Hspec

import Task7

spec :: Spec
spec =
  describe "eval" $
    it "computing the result of all expressions" $ do
      eval (Add (Const 2) (Const 2))                     `shouldBe` Right 4
      eval (Sub (Const 0) (Div (Const 4) (Const 4)))     `shouldBe` Right (-1)
      eval (Mul (Const 4) (Pow (Const 2) (Const 6)))     `shouldBe` Right 256
      eval (Div (Const 5) (Add (Const (-8)) (Const 12))) `shouldBe` Right 1

      eval (Div (Const 1) (Const 0))                 `shouldBe` Left DivByZero
      eval (Pow (Const 6) (Sub (Const 0) (Const 4))) `shouldBe` Left NegPow

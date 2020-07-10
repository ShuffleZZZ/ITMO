module Task2Spec where

import Test.Hspec

import Task2

spec :: Spec
spec = do
  describe "binary operations on natural numbers" $ do
    it "summary" $ do
      (+) (toEnum 2  :: Nat) (toEnum 3  :: Nat) `shouldBe` (toEnum 5  :: Nat)
      (+) (toEnum 3  :: Nat) (toEnum 2  :: Nat) `shouldBe` (toEnum 5  :: Nat)
      (+) (toEnum 2  :: Nat) (toEnum 0  :: Nat) `shouldBe` (toEnum 2  :: Nat)
      (+) (toEnum 0  :: Nat) (toEnum 7  :: Nat) `shouldBe` (toEnum 7  :: Nat)
      (+) (toEnum 7  :: Nat) (toEnum 8  :: Nat) `shouldBe` (toEnum 15 :: Nat)
      (+) (toEnum 31 :: Nat) (toEnum 28 :: Nat) `shouldBe` (toEnum 59 :: Nat)

    it "muiltiplication" $ do
      (*) (toEnum 3  :: Nat) (toEnum 2  :: Nat) `shouldBe` (toEnum 6   :: Nat)
      (*) (toEnum 2  :: Nat) (toEnum 0  :: Nat) `shouldBe` (toEnum 0   :: Nat)
      (*) (toEnum 0  :: Nat) (toEnum 7  :: Nat) `shouldBe` (toEnum 0   :: Nat)
      (*) (toEnum 7  :: Nat) (toEnum 8  :: Nat) `shouldBe` (toEnum 56  :: Nat)
      (*) (toEnum 31 :: Nat) (toEnum 28 :: Nat) `shouldBe` (toEnum 868 :: Nat)

    it "minus (with 'monus' behaivor)" $ do
      (-) (toEnum 3  :: Nat) (toEnum 2  :: Nat) `shouldBe` (toEnum 1 :: Nat)
      (-) (toEnum 2  :: Nat) (toEnum 0  :: Nat) `shouldBe` (toEnum 2 :: Nat)
      (-) (toEnum 0  :: Nat) (toEnum 7  :: Nat) `shouldBe` (toEnum 0 :: Nat)
      (-) (toEnum 7  :: Nat) (toEnum 8  :: Nat) `shouldBe` (toEnum 0 :: Nat)
      (-) (toEnum 31 :: Nat) (toEnum 28 :: Nat) `shouldBe` (toEnum 3 :: Nat)

  describe "Integer to Nat conversion and vice versa" $ do
    it "Integer to Nat conversion" $ do
      (fromInteger (-2) :: Nat) `shouldBe` Z
      (fromInteger 0    :: Nat) `shouldBe` Z
      (fromInteger 2    :: Nat) `shouldBe` (S (S Z))
      (fromInteger 5    :: Nat) `shouldBe` (S (S (S (S (S Z)))))

    it "Int to Nat conversion" $ do
      (toEnum (-2) :: Nat) `shouldBe` Z
      (toEnum 0    :: Nat) `shouldBe` Z
      (toEnum 2    :: Nat) `shouldBe` S (S Z)
      (toEnum 5    :: Nat) `shouldBe` S (S (S (S (S Z))))

    it "Nat to Int conversion" $ do
      fromEnum Z                     `shouldBe` 0
      fromEnum (S Z)                 `shouldBe` 1
      fromEnum (S (S Z))             `shouldBe` 2
      fromEnum (S (S (S (S (S Z))))) `shouldBe` 5

  describe "Comparison and equalation of Nat numbers" $ do
    it "Equalation" $ do
      (==) (toEnum 0 :: Nat) (toEnum 0  :: Nat) `shouldBe` True
      (==) (toEnum 1 :: Nat) (toEnum 1  :: Nat) `shouldBe` True
      (==) (toEnum 4 :: Nat) (toEnum 4  :: Nat) `shouldBe` True

      (==) (toEnum 0 :: Nat) (toEnum 2  :: Nat) `shouldBe` False
      (==) (toEnum 4 :: Nat) (toEnum 0  :: Nat) `shouldBe` False

      (==) (toEnum 5 :: Nat) (toEnum 4  :: Nat) `shouldBe` False
      (==) (toEnum 7 :: Nat) (toEnum 11 :: Nat) `shouldBe` False

    it "Comparison" $ do
      compare (toEnum 0 :: Nat) (toEnum 0  :: Nat) `shouldBe` EQ
      compare (toEnum 1 :: Nat) (toEnum 1  :: Nat) `shouldBe` EQ
      compare (toEnum 4 :: Nat) (toEnum 4  :: Nat) `shouldBe` EQ

      compare (toEnum 0 :: Nat) (toEnum 2  :: Nat) `shouldBe` LT
      compare (toEnum 4 :: Nat) (toEnum 0  :: Nat) `shouldBe` GT

      compare (toEnum 5 :: Nat) (toEnum 4  :: Nat) `shouldBe` GT
      compare (toEnum 7 :: Nat) (toEnum 11 :: Nat) `shouldBe` LT

  describe "isEven" $
    it "check if Nat number is even" $ do
      isEven (toEnum 0   :: Nat) `shouldBe` True
      isEven (toEnum 1   :: Nat) `shouldBe` False
      isEven (toEnum 2   :: Nat) `shouldBe` True
      isEven (toEnum 3   :: Nat) `shouldBe` False
      isEven (toEnum 4   :: Nat) `shouldBe` True

      isEven (toEnum 237 :: Nat) `shouldBe` False


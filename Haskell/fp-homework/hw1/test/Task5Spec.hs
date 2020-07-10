module Task5Spec where

import Test.Hspec

import Task5

spec :: Spec
spec = do
  describe "maybeConcat" $
    it "Unpucks maybe and concatinates the elements of given list." $ do
      maybeConcat []                               `shouldBe` ([] :: [Int])
      maybeConcat [Nothing, Nothing, Nothing]      `shouldBe` ([] :: [Int])
      maybeConcat [Just [1, 2, 3], Nothing]        `shouldBe` [1, 2, 3]
      maybeConcat [Just [1, 2, 3, 4, 5]]           `shouldBe` [1, 2, 3, 4, 5]
      maybeConcat [Just [0], Nothing, Just [4, 5]] `shouldBe` [0, 4, 5]

  describe "NonEmpty and ThisOrThat" $ do
    it "Checks semigroup rules for 'NonEmpty'" $ do
      (2 :| [])     <> (3 :| [])     `shouldBe` (2 :| [3])
      (0 :| [1, 2]) <> (3 :| [4, 5]) `shouldBe` (0 :| [1, 2, 3, 4, 5])

    it "Checks semigroup rules for 'ThisOrThat'" $ do
      This 4 <> This 6    `shouldBe` (This 6 :: ThisOrThat Int Int)
      This 4 <> That 6    `shouldBe` Both 4 6
      This 4 <> Both 3 1  `shouldBe` Both 3 1

      That 4 <> This 6    `shouldBe` Both 6 4
      That 4 <> That 6    `shouldBe` (That 6 :: ThisOrThat Int Int)
      That 4 <> Both 3 1  `shouldBe` Both 3 1

      Both 2 4 <> This 1    `shouldBe` Both 1 4
      Both 2 4 <> That 3    `shouldBe` Both 2 3
      Both 2 4 <> Both 3 1  `shouldBe` Both 3 1

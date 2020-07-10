module Task3Spec where

import Data.List.NonEmpty (NonEmpty((:|)), fromList)
import Test.Hspec

import Task3

fromNonEmptyList = Task3.fromList . Data.List.NonEmpty.fromList

spec :: Spec
spec = do
  describe "isEmpty" $
    it "checks if the tree is empty" $ do
      isEmpty Leaf                            `shouldBe` True
      isEmpty (Node Leaf (1 :| []) Leaf)      `shouldBe` False
      isEmpty (fromNonEmptyList [1, 4, 3, 2]) `shouldBe` False
      isEmpty (fromNonEmptyList [0])          `shouldBe` False

  describe "size" $
    it "returns the size of the tree" $ do
      size Leaf                               `shouldBe` 0
      size (Node Leaf (1 :| []) Leaf)         `shouldBe` 1
      size (fromNonEmptyList [1, 2, 3, 4])    `shouldBe` 4
      size (fromNonEmptyList [2, 2, 2, 2, 3]) `shouldBe` 5
      size (fromNonEmptyList [1, 2, 2])       `shouldBe` 3
      size (fromNonEmptyList [0])             `shouldBe` 1

  describe "find" $
    it "finds the element in the tree" $ do
      find Leaf                               4 `shouldBe` False
      find (fromNonEmptyList [1, 2, 3, 4])    4 `shouldBe` True
      find (fromNonEmptyList [2, 2, 2, 2, 3]) 4 `shouldBe` False
      find (fromNonEmptyList [1, 2, 2])       2 `shouldBe` True
      find (fromNonEmptyList [0, 2, 5])       1 `shouldBe` False

  describe "insert" $
    it "inserts the element into the tree" $ do
      toList (insert Leaf                         4) `shouldBe` [4]
      toList (insert (fromNonEmptyList [1, 2, 3]) 3) `shouldBe` [1, 2, 3, 3]
      toList (insert (fromNonEmptyList [2, 3, 2]) 4) `shouldBe` [2, 2, 3, 4]
      toList (insert (fromNonEmptyList [2, 1, 2]) 2) `shouldBe` [1, 2, 2, 2]
      toList (insert (fromNonEmptyList [5, 0, 2]) 1) `shouldBe` [0, 1, 2, 5]

  describe "fromList" $
    it "makes a tree out of a list" $ do
      toList (fromNonEmptyList [1, 2, 3, 4]) `shouldBe` [1, 2, 3, 4]
      toList (fromNonEmptyList [2, 2, 3, 2]) `shouldBe` [2, 2, 2, 3]
      toList (fromNonEmptyList [2, 1, 2])    `shouldBe` [1, 2, 2]
      toList (fromNonEmptyList [5, 0, 2])    `shouldBe` [0, 2, 5]


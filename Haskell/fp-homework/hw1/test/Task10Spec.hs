module Task10Spec where

import Test.Hspec

import Task10

spec :: Spec
spec =
  describe "check basic parser combinators" $ do
    it "checking the 'ok' combinator" $ do
      runParser ok ""            `shouldBe` Just ((), [])
      runParser ok ([] :: [Int]) `shouldBe` Just ((), [])
      runParser ok "tail"        `shouldBe` Just ((), "tail")

    it "checking the 'eof' combinator" $ do
      runParser eof ""            `shouldBe` Just ((), [])
      runParser eof ([] :: [Int]) `shouldBe` Just ((), [])
      runParser eof "tail"        `shouldBe` Nothing

    it "checking the 'satisfy' combinator" $ do
      runParser (satisfy (== 13))     [13]       `shouldBe` Just (13, [])
      runParser (satisfy (== 'a'))    "a"        `shouldBe` Just ('a', [])
      runParser (satisfy (== 'a'))    "abc"      `shouldBe` Just ('a', "bc")
      runParser (satisfy (== "ok"))   ["ok"]     `shouldBe` Just ("ok", [])
      runParser (satisfy (== [1, 2])) [[1, 2]]   `shouldBe` Just ([1, 2], [])
      runParser (satisfy (== [1]))    [[1], [2]] `shouldBe` Just ([1], [[2]])

      runParser (satisfy (== ""))            []       `shouldBe` Nothing
      runParser (satisfy (== ([] :: [Int]))) []       `shouldBe` Nothing
      runParser (satisfy (== 48))            [37]     `shouldBe` Nothing
      runParser (satisfy (== 'o'))           "a"      `shouldBe` Nothing
      runParser (satisfy (== "ok"))          ["fail"] `shouldBe` Nothing
      runParser (satisfy (== [0]))           [[1]]    `shouldBe` Nothing
      runParser (satisfy (== [1, 2]))        [[2, 2]] `shouldBe` Nothing

    it "checking the 'element' combinator" $ do
      runParser (element 31)   [31, 47]     `shouldBe` Just (31, [47])
      runParser (element 'a')  "a"          `shouldBe` Just ('a', [])
      runParser (element 'a')  "abc"        `shouldBe` Just ('a', "bc")
      runParser (element "ac") ["ac", "bd"] `shouldBe` Just ("ac", ["bd"])

      runParser (element 31)  [17, 31] `shouldBe` Nothing
      runParser (element 'a') "w"      `shouldBe` Nothing
      runParser (element 'o') "wok"    `shouldBe` Nothing

    it "checking the 'stream' combinator" $ do
      runParser (stream "ok")   "ok"         `shouldBe` Just ("ok", [])
      runParser (stream "ok")   "okey"       `shouldBe` Just ("ok", "ey")
      runParser (stream "a")    "abc"        `shouldBe` Just ("a", "bc")
      runParser (stream [3, 7]) [3, 7, 2, 3] `shouldBe` Just ([3, 7], [2, 3])

      runParser (stream [3, 1]) [2, 3, 1, 4] `shouldBe` Nothing
      runParser (stream "ok")   "wok"        `shouldBe` Nothing
      runParser (stream "ok")   "fail"       `shouldBe` Nothing

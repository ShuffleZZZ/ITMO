module Task1Spec where

import Test.Hspec

import Task1

spec :: Spec
spec = do
  describe "nextDay" $
    it "returns the tomorrow day for a given one" $ do
      nextDay Sunday    `shouldBe` Monday
      nextDay Monday    `shouldBe` Tuesday
      nextDay Tuesday   `shouldBe` Wednesday
      nextDay Wednesday `shouldBe` Thursday
      nextDay Thursday  `shouldBe` Friday
      nextDay Friday    `shouldBe` Saturday
      nextDay Saturday  `shouldBe` Sunday

  describe "afterDays" $
    it "returns the day in the given number of days from taken" $ do
      afterDays Monday (-7) `shouldBe` Monday
      afterDays Monday (-6) `shouldBe` Tuesday
      afterDays Monday (-5) `shouldBe` Wednesday
      afterDays Monday (-4) `shouldBe` Thursday
      afterDays Monday (-3) `shouldBe` Friday
      afterDays Monday (-2) `shouldBe` Saturday
      afterDays Monday (-1) `shouldBe` Sunday
      afterDays Monday 0    `shouldBe` Monday
      afterDays Monday 1    `shouldBe` Tuesday
      afterDays Monday 2    `shouldBe` Wednesday
      afterDays Monday 3    `shouldBe` Thursday
      afterDays Monday 4    `shouldBe` Friday
      afterDays Monday 5    `shouldBe` Saturday
      afterDays Monday 6    `shouldBe` Sunday
      afterDays Monday 7    `shouldBe` Monday

      afterDays Friday (-7) `shouldBe` Friday
      afterDays Friday (-6) `shouldBe` Saturday
      afterDays Friday (-5) `shouldBe` Sunday
      afterDays Friday (-4) `shouldBe` Monday
      afterDays Friday (-3) `shouldBe` Tuesday
      afterDays Friday (-2) `shouldBe` Wednesday
      afterDays Friday (-1) `shouldBe` Thursday
      afterDays Friday 0    `shouldBe` Friday
      afterDays Friday 1    `shouldBe` Saturday
      afterDays Friday 2    `shouldBe` Sunday
      afterDays Friday 3    `shouldBe` Monday
      afterDays Friday 4    `shouldBe` Tuesday
      afterDays Friday 5    `shouldBe` Wednesday
      afterDays Friday 6    `shouldBe` Thursday
      afterDays Friday 7    `shouldBe` Friday

      afterDays Tuesday (-22) `shouldBe` Monday
      afterDays Saturday 48   `shouldBe` Friday

  describe "isWeekend" $
    it "shows whether the day is weekend or not" $ do
      isWeekend Sunday    `shouldBe` True
      isWeekend Monday    `shouldBe` False
      isWeekend Tuesday   `shouldBe` False
      isWeekend Wednesday `shouldBe` False
      isWeekend Thursday  `shouldBe` False
      isWeekend Friday    `shouldBe` False
      isWeekend Saturday  `shouldBe` True

  describe "daysToParty" $
    it "shows amount of days left until friday" $ do
      daysToParty Sunday    `shouldBe` 5
      daysToParty Monday    `shouldBe` 4
      daysToParty Tuesday   `shouldBe` 3
      daysToParty Wednesday `shouldBe` 2
      daysToParty Thursday  `shouldBe` 1
      daysToParty Friday    `shouldBe` 0
      daysToParty Saturday  `shouldBe` 6

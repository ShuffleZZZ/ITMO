module Task6
  ( whnf1
  , whnf2
  ) where

-- | WHNF of @distributivity (Left ("harold" ++ " hide " ++ "the " ++ "pain"))@.
-- As we know from the "Task1" @distributivvity (Left a) = (Left a, Left a)@.
whnf1 :: (Either String a, Either String a)
whnf1 = (Left ("harold" ++ " hide " ++ "the " ++ "pain"),
          Left ("harold" ++ " hide " ++ "the " ++ "pain"))

-- | WHNF of @null $ mapMaybe foo "pole chudes ochen' chudesno"@.
-- Because there is \'o\' char in the given 'String', 'foo' will return
-- @Just $ exp pi@ and 'mapMaybe' function will shift it to the start of list.
-- At least one 'Just' return from 'foo' is enough, there is 3 in example.
-- It means, that at the time function 'null' will take this list as
-- an argument, list will not be empty, which results in 'False' return value.
whnf2 :: Bool
whnf2 = False

{-
foo      :: Char -> Maybe Double
foo char =
  case char == 'o' of
    True -> Just $ exp pi
    False -> Nothing

-- not actually, but good enough for this task
null    :: [a] -> Bool
null [] = True
null _  = False

mapMaybe          :: (a -> Maybe b) -> [a] -> [b]
mapMaybe _ []     = []
mapMaybe f (x:xs) =
  let rs = mapMaybe f xs in
  case f x of
    Nothing -> rs
    Just r  -> r:rs
-}

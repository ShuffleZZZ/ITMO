module Task4
  ( joinWith
  , splitOn
  ) where

import Data.List.NonEmpty (NonEmpty(..), fromList, toList)

-- | Splits given list with the given element.
splitOn
  :: Eq a  -- ^ property for equalation
  => a  -- ^ separator
  -> [a]  -- ^ list to split
  -> NonEmpty [a]  -- ^ 'NonEmpty' list of chunks
splitOn separator = foldr processChar (fromList [[]])
  where
    processChar cur (x :| xs) =
      if cur == separator
      then [] :| x : xs
      else (cur : x) :| xs

-- | Joins the nonempty list of elements with given element in between.
joinWith
  :: Eq a  -- ^ property for equalation
  => a  -- ^ joiner
  -> NonEmpty [a]  -- ^ list of elements to join
  -> [a]  -- ^ Joined list
joinWith joiner list = init $ foldr joinHelper [] (toList list)
  where
    joinHelper x chunk = x ++ joiner : chunk

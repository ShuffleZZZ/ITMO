module Task5
  ( NonEmpty(..)
  , ThisOrThat(..)

  , maybeConcat
  ) where

import Data.Semigroup (Semigroup(..))

-- | Unpucks from 'Maybe' and concatinates the elements of given list.
maybeConcat
  :: [Maybe [a]]  -- ^ list of lists wrapped with 'Maybe'
  -> [a]  -- ^ concatinated and unwrapped list
maybeConcat []            = []
maybeConcat (Just x : xs) = x ++ maybeConcat xs
maybeConcat (_      : xs) = maybeConcat xs

-- | List with atleast 1 element.
data NonEmpty a
  = a :| [a] -- Element and the tail
  deriving(Eq, Show)

instance Semigroup (NonEmpty a) where
  (x :| xs) <> (y :| ys) = x :| (xs ++ (y : ys))

-- | Data with one of 2 states or both at the same time.
data ThisOrThat a b
  = This a  -- ^ 'This' state
  | That b  -- ^ 'That' state
  | Both a b  -- ^ 'Both' at the same time
  deriving(Eq, Show)

instance Semigroup (ThisOrThat a b) where
  This _   <> This a   = This a
  This a   <> That b   = Both a b
  This _   <> Both b c = Both b c

  That a   <> This b   = Both b a
  That _   <> That b   = That b
  That _   <> Both b c = Both b c

  Both _ b <> This c   = Both c b
  Both a _ <> That c   = Both a c
  Both _ _ <> Both c d = Both c d


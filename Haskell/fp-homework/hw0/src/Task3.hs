module Task3
  ( identity
  , contraction
  , composition
  , permutation
  ) where

s :: (a -> b -> c) -> (a -> b) -> a -> c
s f g x = f x (g x)

-- | Composition function with bahaivor of operator (.) from standard library.
-- Corresponds to B combinator of BCKW-basis.
composition :: (b -> c) -> (a -> b) -> a -> c
composition = s (const s) const

-- | Ordinary interpretation of 'identity' function in SK-basis.
identity :: a -> a
identity = s const const

-- | Corresponds to W combinator of BCKW-basis.
contraction :: (a -> a -> b) -> a -> b
contraction = s s (s const)

-- | Corresponds to C combinator of BCKW-basis.
permutation :: (a -> b -> c) -> b -> a -> c
permutation = s (s (const (s (const s) const)) s) (const const)

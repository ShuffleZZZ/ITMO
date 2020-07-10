module Task2
  ( doubleNeg
  , doubleNegElim
  , excludedNeg
  , pierce
  , thirdNegElim
  ) where

import Data.Void (Void)

type Neg a = a -> Void

-- | Flip of 2 arguments is an example of the following type.
doubleNeg     :: a -> Neg (Neg a)
doubleNeg x y = y x

excludedNeg :: Neg (Neg (Either a (Neg a)))
excludedNeg = undefined

-- | There is no expression of this type, as pierce arrow corresponds to
-- the rule of excluded third, which has no proof in intuitionistic logic.
-- And by isomorphism of Curry-Howard, lack of proof for expression leads
-- to the fact that there is no non-undefuned expression of this type.
pierce :: ((a -> b) -> a) -> a  -- ^ Pierce arrow
pierce = undefined

-- | This type matches the 10th axiom of classical propositional calculus,
-- which, in fact, has no proof in intuitionistic logic. And lack of proof,
-- once again, means that there is no expression of this type,
-- other than 'undefined'.
doubleNegElim :: Neg (Neg a) -> a  -- ^ 10th axiom of classical calculus
doubleNegElim = undefined

-- | Composition of argument and 'doubleNeg' function is an example of type.
thirdNegElim   :: Neg (Neg (Neg a)) -> Neg a
thirdNegElim a = a . doubleNeg

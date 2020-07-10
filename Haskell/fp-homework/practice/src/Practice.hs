{-# LANGUAGE BangPatterns      #-}
{-# LANGUAGE DataKinds         #-}
{-# LANGUAGE FlexibleContexts  #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE GADTs             #-}
{-# LANGUAGE KindSignatures    #-}
module Practice where

-- | Type for Natural numbers.
data Nat
  = Z  -- ^ Zero
  | S Nat  -- ^ Successor
  deriving(Show)

instance Num Nat where
  (+) a Z     = a
  (+) a (S b) = S $ a + b

  (*) _ Z     = Z
  (*) a (S b) = a * b + a

  -- | Subtraction with 'Data.Nat.monus' behaivor.
  (-) Z     _     = Z
  (-) a     Z     = a
  (-) (S a) (S b) = a - b

  abs = id

  signum Z     = Z
  signum (S _) = S Z

  fromInteger a = if a > 0 then S $ fromInteger $ a - 1 else Z

toInt :: Nat -> Int
toInt Z     = 0
toInt (S a) = 1 + toInt a

-- | Type for Vector of 'Nat' with given length.
data Vec :: * -> Nat -> * where
  Nil  ::Vec a 'Z  -- ^ empty vector
  (:>) ::a -> Vec a n -> Vec a ('S n)  -- ^ concat operation

instance Show (Vec a 'Z) where
  show = const "Nil"

instance (Show a, Show (Vec a n)) => Show (Vec a ('S n)) where
  show (a :> as) = show a ++ ":" ++ show as

len :: Vec a n -> Int
len = helper 0
 where
  helper :: Int -> Vec a n -> Int
  helper !acc Nil       = acc
  helper !acc (_ :> as) = helper (acc + 1) as

dotProduct :: (Num a) => Vec a n -> Vec a n -> a
dotProduct Nil       Nil       = 0
dotProduct (a :> as) (b :> bs) = a * b + dotProduct as bs

nat0 :: Nat
nat0 = Z

int0 :: Int
int0 = 0


nat1 :: Nat
nat1 = S nat0

int1 :: Int
int1 = 1


nat2 :: Nat
nat2 = S nat1

int2 :: Int
int2 = 2


nat3 :: Nat
nat3 = S nat2

int3 :: Int
int3 = 3


nat4 :: Nat
nat4 = S nat3

int4 :: Int
int4 = 4


vecNat :: Vec Nat ( 'S ( 'S ( 'S ( 'S 'Z))))
vecNat = nat1 :> (nat2 :> (nat3 :> (nat4 :> Nil)))

vecNatRev :: Vec Nat ( 'S ( 'S ( 'S ( 'S 'Z))))
vecNatRev = nat4 :> (nat3 :> (nat2 :> (nat1 :> Nil)))

vecNatRand :: Vec Nat ( 'S ( 'S ( 'S ( 'S 'Z))))
vecNatRand = nat3 :> (nat0 :> (nat4 :> (nat1 :> Nil)))


vecInt :: Vec Int ( 'S ( 'S ( 'S ( 'S 'Z))))
vecInt = int1 :> (int2 :> (int3 :> (int4 :> Nil)))

vecIntRev :: Vec Int ( 'S ( 'S ( 'S ( 'S 'Z))))
vecIntRev = int4 :> (int3 :> (int2 :> (int1 :> Nil)))

vecIntRand :: Vec Int ( 'S ( 'S ( 'S ( 'S 'Z))))
vecIntRand = int3 :> (int0 :> (int4 :> (int1 :> Nil)))

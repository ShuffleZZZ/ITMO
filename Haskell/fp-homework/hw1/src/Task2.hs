module Task2
  ( Nat(..)

  , isEven
  ) where

-- | Type for Natural numbers.
data Nat
  = Z  -- ^ Zero
  | S Nat  -- ^ Successor
  deriving(Show)

instance Eq Nat where
  Z     == Z     = True
  Z     == (S _) = False
  (S _) == Z     = False
  (S a) == (S b) = a == b

instance Ord Nat where
  compare Z     Z     = EQ
  compare (S _) Z     = GT
  compare Z     (S _) = LT
  compare (S a) (S b) = compare a b


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

  fromInteger = intToEnum

instance Enum Nat where
  toEnum = intToEnum

  fromEnum Z     = 0
  fromEnum (S a) = 1 + fromEnum a


-- | Implementation of 'toEnum' and 'fromInteger' for 'Nat' numbers.
intToEnum
  :: Num a  -- ^ property for calculations
  => Ord a  -- ^ property for comparison
  => a  -- ^ 'Int' or 'Integer' value
  -> Nat  -- ^ corresponding 'Nat' number
intToEnum a =
  if a > 0
  then S $ intToEnum $ a - 1
  else Z

-- | Checks if 'Nat' number is even.
isEven
  :: Nat  -- ^ 'Nat' number to check
  -> Bool  -- ^ 'True' if even and 'False' if odd
isEven Z     = True
isEven (S a) = not $ isEven a

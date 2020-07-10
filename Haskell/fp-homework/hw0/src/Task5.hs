module Task5
  ( churchMult
  , churchPlus
  , churchToInt
  , succChurch
  , zero
  ) where

type Nat a = (a -> a) -> a -> a

-- | Zero Church numeral.
zero     :: Nat a
zero _ x = x

-- | Successor for Church numerals.
succChurch
  :: Nat a  -- ^ Given Church numeral
  -> Nat a  -- ^ Increased Church numeral
succChurch n f x = n f (f x)

-- | Plus operation for Church numerals.
churchPlus
  :: Nat a  -- ^ First Church numeral for sum
  -> Nat a  -- ^ Second Church numeral for sum
  -> Nat a  -- ^ Summarised Church numeral
churchPlus n m f x = n f (m f x)

-- | Multiplication operation for Church numerals.
churchMult
  :: Nat a  -- ^ First Church numeral for product
  -> Nat a  -- ^ Second Church numeral for product
  -> Nat a  -- ^ Product Church numeral
churchMult n m f = n (m f)

-- | Translate Church numeral to 'Integer'.
churchToInt
  :: Nat Integer  -- ^ Church numeral to translate
  -> Integer  -- ^ Translated number
churchToInt n = n (+ 1) 0

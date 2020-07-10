{-# LANGUAGE TypeOperators #-}

module Task1
  ( associator
  , distributivity
  , eitherAssoc
  ) where

-- | Aplies distributivity rule for 'Either' expression.
distributivity
  :: Either a (b, c)  -- ^ 'Either' expression, only pair possible in 'Right'
  -> (Either a b, Either a c)  -- ^ Pair of distributed 'Either' expressions
distributivity (Left a)       = (Left a, Left a)
distributivity (Right (b, c)) = (Right b, Right c)

-- | Switches the associativity of given expression with right-associative pair
-- applied on 3 arguments to the left one.
associator
  :: (a, (b, c))  -- ^ Expression wrapped with right-associative pair
  -> ((a, b), c)  -- ^ The same expression wrapped with left-associative pair
associator (a, (b, c)) = ((a, b), c)

type (<->) a b = (a -> b, b -> a)

-- | Returns a pair of functions: taking right-associative 'Either',
-- applied on 3 arguments, the first function returns an expression with
-- left-associative 'Either', while the second function works vice versa.
eitherAssoc
  :: Either a (Either b c)  -- ^ expression with right-associative 'Either'
  <-> Either (Either a b) c  -- ^ same expression with left associativity
eitherAssoc = (straightImpl, backImpl)
  where
    -- | Returns the value in left-associative expression, which corresponds
    -- to the given in right-associative one.
    straightImpl :: Either a (Either b c) -> Either (Either a b) c
    straightImpl (Left a)          = Left $ Left a
    straightImpl (Right (Left b))  = Left $ Right b
    straightImpl (Right (Right c)) = Right c

    -- | Returns the value in right-associative expression, which corresponds
    -- to the given in left-associative one.
    backImpl :: Either (Either a b) c -> Either a (Either b c)
    backImpl (Left (Left a))  = Left a
    backImpl (Left (Right b)) = Right $ Left b
    backImpl (Right c)        = Right $ Right c

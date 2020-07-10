{-# LANGUAGE LambdaCase #-}

module Task10
  ( module Task9

  , element
  , eof
  , ok
  , satisfy
  , stream
  ) where

import Task9 (Parser(..))

-- | Parser that always returns 'Just' without processing the input.
ok
  :: Parser s ()  -- ^ parser type
ok = Parser $ \s -> Just ((), s)

-- | Parser that returns 'Nothing' if not the whole stream of input processed.
eof
  :: Parser s ()  -- ^ parser type
eof = Parser $ \case
  [] -> Just ((), [])
  _  -> Nothing

-- | Parser that not fails only if current element satisfies given predicate.
satisfy
  :: (s -> Bool)  -- ^ predicate
  -> Parser s s  -- ^ parser type
satisfy p = Parser $ \case
  []       -> Nothing
  (x : xs) -> if p x then Just (x, xs) else Nothing

-- | Parser that proccesses a single element.
element
  :: Eq s  -- ^ property for equalation
  => s  -- ^ given element
  -> Parser s s  -- ^ parser type
element c = satisfy (== c)

-- | Parser that processes a list of elements.
stream
  :: Eq s  -- ^ property for equalation
  => [s]  -- ^ list of elements to parse
  -> Parser s [s]  -- ^ parser type
stream = mapM element

module Task9
  ( Parser(..)
  ) where

import Control.Applicative (Alternative, empty, (<|>))
import Data.Bifunctor (first)

-- | Parser type for stream of any data.
newtype Parser s a
  = Parser { runParser
    :: [s]  -- ^ parser input
    -> Maybe (a, [s])  -- ^ Pair of parsed element and rest of input or 'Nothing'
  }

instance Functor (Parser s) where
  fmap f (Parser parser) = Parser $ fmap (first f) . parser

instance Applicative (Parser s) where
  pure a = Parser $ \s -> Just (a, s)

  Parser pf <*> Parser pa = Parser $ \s -> case pf s of
    Nothing     -> Nothing
    Just (f, t) -> case pa t of
      Nothing     -> Nothing
      Just (a, r) -> Just (f a, r)

instance Monad (Parser s) where
  Parser pa >>= f = Parser $ \s -> uncurry runParser =<< (first f <$> pa s)

instance Alternative (Parser s) where
  empty = Parser $ const Nothing

  (Parser a) <|> (Parser b) = Parser $ \s -> a s <|> b s

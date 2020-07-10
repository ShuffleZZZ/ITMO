module Task11
  ( module Task9

  , balancedParentheses
  , int
  ) where

import Control.Applicative (many, some, (<|>))
import Data.Char (digitToInt, isDigit)

import Task10 (element, eof, satisfy)
import Task9 (Parser(..))

-- | Parse digit from a char.
digit
  :: Parser Char Int  -- ^ parser type
digit = digitToInt <$> satisfy isDigit

-- | Parse sign of number and returns a function to apply on the rest of it.
sign
  :: Parser Char (Int -> Int)  -- ^ parser type
sign = negate <$ element '-' <|> id <$ element '+'

-- | Parse number without sign.
natural
  :: Parser Char Int  -- ^ parser type
natural = foldl (\acc val -> acc * 10 + val) 0 <$> some digit

-- | Parse 'Int' values with '+' or '-' signs.
int
  :: Parser Char Int  -- ^ parser type
int = natural <|> sign <*> natural

-- | Parse balanced parentheses, return 'Nothing' on unbalanced sequense.
balancedParentheses
  :: Parser Char ()  -- ^ parser type
balancedParentheses = balance *> eof
  where
    balance = many $ element '(' *> balance *> element ')'

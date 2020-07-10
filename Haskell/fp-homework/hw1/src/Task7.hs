module Task7
  ( ArithmeticError(..)
  , Expr(..)

  , eval
  ) where

import Data.Either (fromRight)

-- | Arithmetic expression.
data Expr
  = Const Int  -- ^ constant
  | Add Expr Expr  -- ^ binary addition
  | Sub Expr Expr  -- ^ binary substraction
  | Mul Expr Expr  -- ^ binary multiplication
  | Div Expr Expr  -- ^ binary division
  | Pow Expr Expr  -- ^ exponentiation
  deriving(Show)


-- | Error that might occur during calculation.
data ArithmeticError
  = DivByZero  -- ^ occurs in division by zero case
  | NegPow  -- ^ occurs in case of negative exponentiation
  deriving(Show, Eq)

-- | Applies all operations and computes value of the 'Expr'.
eval
  :: Expr  -- ^ given 'Expr'
  -> Either ArithmeticError Int  -- ^ 'Left' error or 'Right' value.
eval (Const a) = Right a
eval (Add a b) = (+) <$> eval a <*> eval b
eval (Sub a b) = (-) <$> eval a <*> eval b
eval (Mul a b) = (*) <$> eval a <*> eval b
eval (Div a b) =
  let divider = fromRight 0 $ eval b
  in  if divider == 0
      then Left DivByZero
      else div <$> eval a <*> pure divider
eval (Pow a b) =
  let power = fromRight (-1) $ eval b
  in  if power < 0
      then Left NegPow
      else (^) <$> eval a <*> pure power

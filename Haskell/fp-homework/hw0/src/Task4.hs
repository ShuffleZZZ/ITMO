module Task4
  ( factorial
  , fibonacci
  , iterateElement
  , mapFix
  ) where

import Data.Function (fix)

-- | Returns an infinite list filled with given element.
iterateElement
  :: a  -- ^ given element
  -> [a]  -- ^ infinite list consisting only of given argument
iterateElement a = fix $ \x -> a : x

-- | Returns the fibonacci number of given index.
fibonacci
  :: Integer  -- ^ index of requested fibonacci number
  -> Integer  -- ^ fibonacci number
fibonacci =
  fix $ \fib n -> if n == 0 || n == 1
    then n
    else if n > 0
      then fib(n - 2) + fib(n - 1)
      else fib(n + 2) - fib(n + 1)

-- | Returns the factorial of given number.
factorial
  :: Integer  -- ^ The number to calculate the factorial for.
  -> Integer  -- ^ Result of calculation.
factorial =
  fix $ \fact n -> if n > 0
    then n * fact(n - 1)
    else if n == 0
      then 1
      else error "factorial function expected non-negative argument"

-- | Implementation of standard map function.
mapFix
  :: (a -> b)  -- ^ function to apply on elements of list
  -> [a]  -- ^ first element of remaining list
  -> [b]  -- ^ rest of the list
mapFix f =
  fix $ \mapF (x:xs) -> if null xs
    then [f x]
    else f x : mapF xs

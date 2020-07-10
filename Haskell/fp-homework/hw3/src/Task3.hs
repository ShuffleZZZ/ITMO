{-# LANGUAGE FlexibleInstances      #-}
{-# LANGUAGE FunctionalDependencies #-}
{-# LANGUAGE RankNTypes             #-}
{-# LANGUAGE TypeFamilies           #-}

module Task3
  ( HS(..)

  , append
  , doubleVal
  , log2
  , runWithVar
  , toHS
  ) where

import Control.Monad.ST (ST, runST)
import Data.STRef (STRef, newSTRef, readSTRef, writeSTRef)

-- | 'HS' number representation.
data Number
  = Round Int  -- ^ integer numbers
  | Fract Double  -- ^ double numbers

instance Show Number where
  show (Round a) = show a
  show (Fract a) = show a

instance Eq Number where
  (Round a) == (Round b) = a == b
  (Fract a) == (Fract b) = a == b
  (Round a) == (Fract b) = fromIntegral a == b
  (Fract a) == (Round b) = a == fromIntegral b

instance Ord Number where
  compare (Round a) (Round b) = compare a b
  compare (Fract a) (Fract b) = compare a b
  compare (Round a) (Fract b) = compare (fromIntegral a) b
  compare (Fract a) (Round b) = compare a (fromIntegral b)

instance Num Number where
  (+) (Round a) (Round b) = Round $ a + b
  (+) (Fract a) (Fract b) = Fract $ a + b
  (+) (Round a) (Fract b) = Fract $ fromIntegral a + b
  (+) (Fract a) (Round b) = Fract $ a + fromIntegral b

  (*) (Round a) (Round b) = Round $ a * b
  (*) (Fract a) (Fract b) = Fract $ a * b
  (*) (Round a) (Fract b) = Fract $ fromIntegral a * b
  (*) (Fract a) (Round b) = Fract $ a * fromIntegral b

  (-) (Round a) (Round b) = Round $ a - b
  (-) (Fract a) (Fract b) = Fract $ a - b
  (-) (Round a) (Fract b) = Fract $ fromIntegral a - b
  (-) (Fract a) (Round b) = Fract $ a - fromIntegral b

  abs (Round a) = Round $ abs a
  abs (Fract a) = Fract $ abs a

  signum (Round a) = Round $ signum a
  signum (Fract a) = Fract $ signum a

  fromInteger a = Round $ fromIntegral a


-- | data types available for storing in 'HS'.
data HSVar
  = Bin Bool  -- ^ 'Bool' values
  | Str String  -- ^ strings
  | Num Number  -- ^ numbers
  | Any  -- ^ bottom-like type

instance Show HSVar where
  show (Bin a) = show a
  show (Str a) = show a
  show (Num a) = show a
  show (Any  ) = "any"

instance Eq HSVar where
  (Any  ) == _       = True
  (Bin a) == (Bin b) = a == b
  (Bin a) == (Str b) = show a == b
  (Bin a) == (Num b) = (Round $ fromEnum a) == b
  (Str a) == (Str b) = a == b
  (Str a) == (Num b) = a == show b
  (Num a) == (Num b) = a == b
  a       == b       = b == a

instance Ord HSVar where
  compare (Any  ) _       = LT
  compare (Bin a) (Bin b) = compare a b
  compare (Bin a) (Str b) = compare (show a) b
  compare (Bin a) (Num b) = compare (Round $ fromEnum a) b
  compare (Str a) (Str b) = compare a b
  compare (Str a) (Num b) = compare a $ show b
  compare (Num a) (Num b) = compare a b
  compare a       b       = compare b a

instance Num HSVar where
  (+) (Any  ) _       = Any
  (+) (Bin a) (Bin b) = Bin $ a || b
  (+) (Bin a) (Str b) = Str $ (show a) <> b
  (+) (Bin a) (Num b) = Num $ (Round $ fromEnum a) + b
  (+) (Str a) (Str b) = Str $ a <> b
  (+) (Str a) (Num b) = Str $ a <> show b
  (+) (Str a) (Bin b) = Str $ a <> show b
  (+) (Num a) (Num b) = Num $ a + b
  (+) (Num a) (Str b) = Str $ show a <> b
  (+) a       b       = (+) b a

  (*) (Any  ) _       = Any
  (*) (Bin a) (Bin b) = Bin $ a && b
  (*) (Bin _) (Str _) = Any
  (*) (Bin a) (Num b) = Num $ (Round $ fromEnum a) * b
  (*) (Str _) (Str _) = Any
  (*) (Str _) (Num _) = Any
  (*) (Str _) (Bin _) = Any
  (*) (Num a) (Num b) = Num $ a * b
  (*) (Num _) (Str _) = Any
  (*) a       b       = (*) b a

  (-) (Any  ) _       = Any
  (-) (Bin a) (Bin b) = Num $ Round $ fromEnum a - fromEnum b
  (-) (Bin _) (Str _) = Any
  (-) (Bin a) (Num b) = Num $ (Round $ fromEnum a) - b
  (-) (Str _) (Str _) = Any
  (-) (Str _) (Num _) = Any
  (-) (Str _) (Bin _) = Any
  (-) (Num a) (Num b) = Num $ a - b
  (-) (Num _) (Str _) = Any
  (-) (Num a) (Bin b) = Num $ a - (Round $ fromEnum b)
  (-) a       b       = (-) b a

  abs (Num a) = Num $ abs a
  abs a       = a

  signum (Num a) = Num $ signum a
  signum (Bin _) = Bin $ True
  signum _       = Any

  fromInteger a = Num $ Round $ fromIntegral a

-- | Class to convert value to 'HS' representation.
class Show a => ToHS a where
  toHS :: a -> HSVar

instance ToHS Bool where
  toHS = Bin

instance ToHS Int where
  toHS = Num . Round

instance ToHS Double where
  toHS = Num . Fract

instance ToHS String where
  toHS = Str

-- | HalyavaScript tagless final declararion class.
class HS expr where
  type Ref expr a :: *

  (@=) :: expr (Ref expr HSVar) -> expr HSVar -> expr ()

  (#) :: expr a -> expr b -> expr b

  (@>)  :: expr HSVar -> expr HSVar -> expr Bool
  (@<)  :: expr HSVar -> expr HSVar -> expr Bool
  (@>=) :: expr HSVar -> expr HSVar -> expr Bool
  (@<=) :: expr HSVar -> expr HSVar -> expr Bool
  (@==) :: expr HSVar -> expr HSVar -> expr Bool
  (@/=) :: expr HSVar -> expr HSVar -> expr Bool

  (@+)  :: expr HSVar -> expr HSVar -> expr HSVar
  (@-)  :: expr HSVar -> expr HSVar -> expr HSVar
  (@*)  :: expr HSVar -> expr HSVar -> expr HSVar

  hsWhile :: expr Bool -> expr () -> expr ()
  hsIf    :: expr Bool -> expr () -> expr () -> expr ()

  hsFun1 :: (expr HSVar -> expr (Ref expr HSVar) -> expr ())
         -> expr HSVar
         -> expr HSVar
  hsFun2 :: (expr HSVar -> expr HSVar -> expr (Ref expr HSVar) -> expr ())
         -> expr HSVar
         -> expr HSVar
         -> expr HSVar

  hsReadVar  :: expr (Ref expr HSVar) -> expr HSVar
  hsVarScope :: ToHS a => a -> (expr (Ref expr HSVar) -> expr ()) -> expr ()

infix 4 @=
infixl 1 #

infix 4 @>
infix 4 @<
infix 4 @>=
infix 4 @<=
infix 4 @==
infix 4 @/=

instance HS (ST s) where
  type Ref (ST s) a = STRef s a

  ref @= arg = do
    hsRef <- ref
    hsArg <- arg
    writeSTRef hsRef hsArg

  (#) = (>>)


  a @> b = do
    hsA <- a
    hsB <- b
    return $ hsA > hsB

  a @< b = do
    hsA <- a
    hsB <- b
    return $ hsA < hsB

  a @>= b = do
    hsA <- a
    hsB <- b
    return $ hsA >= hsB

  a @<= b = do
    hsA <- a
    hsB <- b
    return $ hsA <= hsB

  a @== b = do
    hsA <- a
    hsB <- b
    return $ hsA == hsB

  a @/= b = do
    hsA <- a
    hsB <- b
    return $ hsA /= hsB


  a @+ b = do
    hsA <- a
    hsB <- b
    return $ hsA + hsB

  a @- b = do
    hsA <- a
    hsB <- b
    return $ hsA - hsB

  a @* b = do
    hsA <- a
    hsB <- b
    return $ hsA * hsB


  hsWhile cond body = do
    isExec <- cond
    if (isExec)
      then do
        _ <- body
        hsWhile cond body
      else pure ()

  hsIf cond body1 body2 = do
    isExec <- cond
    if (isExec) then body1 else body2


  hsFun1 body arg = do
    res <- newSTRef Any
    body arg $ return res
    readSTRef res

  hsFun2 body arg1 arg2 = do
    res <- newSTRef Any
    body arg1 arg2 $ return res
    readSTRef res


  hsReadVar hsVar = do
    var <- hsVar
    readSTRef var

  hsVarScope var body = do
    ref <- newSTRef $ toHS var
    body (return ref)


-- | Takes convertable variable and 'HS' code, runs it and returns the result.
runWithVar
  :: ToHS a  -- ^ constraint for variable conversion
  => a  -- ^ variable to run with
  -> (forall s . ST s HSVar -> ST s HSVar)  -- ^ 'HS' executable code
  -> HSVar  -- ^ resulting value
runWithVar var code = runST $ code $ return $ toHS var

-- | Doubles the given value, if result is equal to value, returns the 'String'
-- "val is mempty".
doubleVal
  :: HS a
  => a HSVar  -- ^ initial value
  -> a HSVar  -- ^ doubled value or "val is mempty"
doubleVal =
  hsFun1 $ \arg res ->
    hsVarScope "" $ \b ->
      hsVarScope "val is mempty" $ \c ->
        b @= arg @+ arg #
        hsIf (arg @== hsReadVar b)
          (res @= hsReadVar c)
          (res @= hsReadVar b)

-- | For a given @x@ calculates @ceiling (log2 (x))@
log2
  :: HS a
  => a HSVar  -- ^ argument
  -> a HSVar  -- ^ @ceiling . log2@
log2 =
  hsFun1 $ \arg logCnt ->
    hsVarScope (1 :: Int) $ \acc ->
      hsVarScope (1 :: Int) $ \one ->
        hsVarScope (0 :: Int) $ \zero ->
          logCnt @= hsReadVar zero #
          hsWhile (arg @> hsReadVar acc)
            ( acc @= hsReadVar acc @+ hsReadVar acc #
              logCnt @= hsReadVar logCnt @+ hsReadVar one
            )

-- | Appends const 'String' to the end.
append
  :: HS a
  => a HSVar  -- ^ initial value
  -> a HSVar  -- ^ 'String' with appended tail
append =
  hsFun1 $ \a out ->
    hsVarScope "extra" $ \b ->
      out @= a @+ hsReadVar b

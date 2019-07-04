{-# LANGUAGE FlexibleContexts #-}
--https://github.com/artemohanjanyan/university/blob/master/3_term/logic/rec_functions.hs
import           Control.Applicative ((*>), (<*))
import           Control.Monad       (foldM_, void)
import           Data.Char           (isDigit, isLower)
import           Text.Parsec

data N0
  = Zero
  | Succ N0

toInt :: N0 -> Int
toInt Zero     = 0
toInt (Succ x) = 1 + toInt x

fromInt :: Int -> N0
fromInt x = foldr (const Succ) Zero [1..x]

instance Show N0 where
  show = show . toInt

type RecFunc = [N0] -> N0

z :: RecFunc
z [_] = Zero
z _   = error "bad arity for Z"

n :: RecFunc
n [x] = Succ x
n _   = error "bad arity for N"

p :: Int -> Int -> RecFunc
p nn _ xs | nn /= length xs = error "bad arity for U"
p _ j xs  = xs !! (j - 1)

s :: RecFunc -> [RecFunc] -> RecFunc
s f gs xs = f $ map ($ xs) gs

r :: RecFunc -> RecFunc -> RecFunc
r f g args =
  case y of
    Zero     -> f xs
    (Succ i) -> g $ xs ++ [i] ++ [r f g $ xs ++ [i]]
  where
    xs = init args
    y = last args

------------
-- Parser --
------------

type Parser a = Parsec String () a

type CustomFunc = (String, RecFunc)

number :: Parser Int
number = (<?> "number") $ lexeme $ read <$> (many1 $ satisfy isDigit)

function :: [CustomFunc] -> Parser RecFunc
function fs = fParser
  where
    fsParsers = map (\(funcName, func) -> func <$ try (symb funcName)) fs
    fParser = foldr (<|>)
      (   do
          symb "Z"
          return z
      <|> do
          symb "N"
          return n
      <|> do
          symb "Pi" <|> symb "U"
          nn <- number
          j <- number
          return $ p nn j
      <|> do
          symb "S"
          symb "<"
          f <- fParser
          comma
          gs <- fParser `sepBy` comma
          symb ">"
          return (s f gs)
      <|> do
          symb "R"
          symb "<"
          f <- fParser
          comma
          g <- fParser
          symb ">"
          return (r f g)
      ) fsParsers

lexeme :: Parser a -> Parser a
lexeme = (<* spaces)

symb :: String -> Parser ()
symb = void . lexeme . string

comma :: Parser ()
comma = symb ","

identifier :: Parser String
identifier = lexeme $ many1 (satisfy isLower)

expression :: [CustomFunc] -> Parser N0
expression fs = spaces *>
  do
    f <- function fs
    symb "("
    xs <- (fromInt <$> number) `sepBy` comma
    symb ")"
    return $ f xs

assignment :: [CustomFunc] -> Parser CustomFunc
assignment fs = spaces *>
  do
    funcName <- identifier
    symb "="
    func <- function fs
    pure (funcName, func)

statement :: [CustomFunc] -> Parser (Either N0 CustomFunc)
statement fs = Left <$> try (expression fs) <|> Right <$> assignment fs

main :: IO ()
main = (zip [1..] . lines) <$> getContents >>= foldM_ goMain []
  where
    goMain :: [CustomFunc] -> (Int, String) -> IO [CustomFunc]
    goMain fs (lineN, stmt) =
      case parse (statement fs) (show lineN) stmt of
        Left e -> fs <$ putStrLn (show e)
        Right stmt' ->
          case stmt' of
            Left res -> fs <$ print (toInt res)
            Right f  -> pure $ f:fs

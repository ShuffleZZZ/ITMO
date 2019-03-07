import Data.Char

main = putStrLn "Hello, world!"

sumSquares x y = x ^ 2 + y ^ 2
lenVec3 x y z = sqrt (x ^ 2 + y ^ 2 + z ^ 2)

func x = if x > 0 then "YES" else "NO"
secFunc x = (if x > 0 then 5 else (-5)) + 3

sign x = if x > 0 then 1 else if x < 0 then -1 else 0

max5' = max 5
discount :: Double -> Double -> Double -> Double
discount limit proc sum = if sum >= limit then sum * (100 - proc) / 100 else sum
standardDiscount :: Double -> Double
standardDiscount = discount 1000 5
text languageTo languageFrom text = "Snälla mannikhor"

log = logBase 4 (min 20 (9 + 7))
log2 = logBase 4 $ min 20 $ 9 + 7

alpha = 3 :: Int

letter x = toLower x

twoDigits2Int :: Char -> Char -> Int
twoDigits2Int x y = if isDigit x && isDigit y then digitToInt x * 10 + digitToInt y else 100

dist :: (Double, Double) -> (Double, Double) -> Double
dist p1 p2 = sqrt $ (snd p2 - snd p1) ^ 2 + (fst p2 - fst p1) ^ 2

str = 'H' : "ello"
welcome = str ++ " World!"

doubleFact :: Integer -> Integer
doubleFact n = if n < 0 then error "Negative argument given" else if n > 0 then n * doubleFact (n - 2) else 1

factorial :: Integer -> Integer
factorial n | n == 0 = 1
            | n > 0  = n * factorial (n - 1)
            | otherwise = error "Negative argument given"

fibonacci :: Integer -> Integer
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci (-1) = 1
fibonacci n | n > 0 = fibonacci (n - 1) + fibonacci (n - 2)
            | n < 0 = (-1)^(1-n) * fibonacci (-n)
factorial2 :: Integer -> Integer
factorial2 n | n >= 0 = helper 1 0
             | otherwise = error "Negative argument given"
helper acc 0 = acc
helper acc n = helper (acc * n) (n - 1)

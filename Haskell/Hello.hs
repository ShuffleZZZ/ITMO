main = putStrLn "Hello, world!"

sumSquares x y = x ^ 2 + y ^ 2
lenVec3 x y z = sqrt (x ^ 2 + y ^ 2 + z ^ 2)

func x = if x > 0 then "YES" else "NO"
secFunc x = (if x > 0 then 5 else (-5)) + 3

sign x = if x > 0 then 1 else if x < 0 then -1 else 0

max5' = max 5
discount limit proc sum = if sum >= limit then sum * (100 - proc) / 100 else sum
standardDiscount = discount 1000 5
text languageTo languageFrom text = "Jävla pojkarna"

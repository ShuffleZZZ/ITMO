
main = do
    a <- getLine
    b <- getLine
    let x = (read a :: Integer)
    let y = (read b :: Integer)
    print (x * y)

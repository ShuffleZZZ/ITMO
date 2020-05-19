module Grammar where
data Expr = Lambda String Expr | Apl Expr Expr | Var String
instance Show Expr where
    show (Lambda var expr) = "(\\" ++ var ++ "." ++ show expr ++ ")"
    show (Apl a b) = "(" ++ show a ++ " " ++ show b ++ ")"
    show (Var var) = var

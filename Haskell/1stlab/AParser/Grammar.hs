module Grammar where
data BinaryOp = Impl | And | Or
instance Show BinaryOp where
  show Impl = "->"
  show And = "&"
  show Or = "|"
data Expr = Binary BinaryOp Expr Expr | Not Expr | Var String
instance Show Expr where
  show (Binary op a b) = "(" ++ show op ++ "," ++ show a ++ "," ++ show b ++ ")"
  show (Not var) = "(!" ++ show var ++ ")"
  show (Var var) = var

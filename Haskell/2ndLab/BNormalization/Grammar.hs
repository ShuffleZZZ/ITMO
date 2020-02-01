module Grammar where
import qualified Data.Map.Strict
data Expr = Lambda String Expr | Apl Expr Expr | Var String | Redex Int
instance Show Expr where
    show (Lambda var expr) = "(\\" ++ var ++ "." ++ show expr ++ ")"
    show (Apl a b) = "(" ++ show a ++ " " ++ show b ++ ")"
    show (Var var) = var

data CurData = CurData { step :: Int,
                         typeId :: Int,
                         redexMap :: Data.Map.Strict.Map Int Expr }

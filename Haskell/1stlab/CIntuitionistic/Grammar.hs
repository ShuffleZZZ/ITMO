module Grammar where
import Data.List (intercalate)
import qualified Data.Map.Strict (Map)
import Data.Hashable
import Data.Bits (complement, xor)
import qualified Data.HashSet (HashSet)
import qualified Data.HashMap.Strict (HashMap)
data BinaryOp = Impl | And | Or
                deriving(Eq, Ord)
instance Show BinaryOp where
  show Impl = "->"
  show And = "&"
  show Or = "|"
instance Hashable BinaryOp where
  hashWithSalt salt op = xor salt (inv op) where
    inv Impl = 50
    inv And = 76
    inv Or = 385
data Expr = Binary BinaryOp Expr Expr | Not Expr | Var String
            deriving(Eq, Ord)
instance Show Expr where
  show (Binary op a b) = "(" ++ show a ++ " " ++ show op ++ " " ++ show b ++ ")"
  show (Not var) = "!" ++ show var
  show (Var var) = var
instance Hashable Expr where
  hashWithSalt salt expr = xor salt (inv expr) where
    inv (Binary op a b) = xor (inv b) (xor (hash op) (inv a))
    inv (Not var) = complement (inv var)
    inv (Var var) = hash var
data ToProof = ToProof { hypos :: [Expr],
                         proofable :: Expr }
instance Show ToProof where
  show str = showHypos (hypos str) ++ "|- " ++ show (proofable str)
showHypos hypos = (intercalate ", ") ((map show) hypos) ++ " "
showHypos [] = ""
data CurData = CurData { hyps :: Data.HashSet.HashSet Expr,
                         exprs :: Data.HashSet.HashSet Expr,
                         partOf :: Data.HashMap.Strict.HashMap Expr [Expr] }

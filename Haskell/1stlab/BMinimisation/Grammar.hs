module Grammar where
import Data.List (intercalate)
import qualified Data.Map.Strict (Map)
data BinaryOp = Impl | And | Or
                deriving(Eq, Ord)
instance Show BinaryOp where
  show Impl = "->"
  show And = "&"
  show Or = "|"
data Expr = Binary BinaryOp Expr Expr | Not Expr | Var String
            deriving(Eq, Ord)
instance Show Expr where
  show (Binary op a b) = "(" ++ show a ++ " " ++ show op ++ " " ++ show b ++ ")"
  show (Not var) = "!" ++ show var
  show (Var var) = var
data ToProof = ToProof { hypos :: [Expr],
                         proofable :: Expr }
instance Show ToProof where
  show str = showHypos (hypos str) ++ "|- " ++ show (proofable (str))
showHypos hypos = (intercalate ", ") ((map show) hypos) ++ " "
showHypos [] = ""
data CurData = CurData { str :: Expr,
                         hypo :: Data.Map.Strict.Map Expr Int,
                         annotation :: Data.Map.Strict.Map Expr (Type, Int),
                         checker :: Bool,
                         count :: Int,
                         partOf :: Data.Map.Strict.Map Expr [(Expr, Int)] }
data Type = Hypo Int | Ax Int | MP Int Int
            deriving (Eq, Ord)
instance Show Type where
  show (Hypo a) = "Hypothesis " ++ show a
  show (Ax a) = "Ax. sch. " ++ show a
  show (MP a b) = "M.P. " ++ show a ++ ", " ++ show b
data ResStrings = ResStrings { toProof :: ToProof,
                               exprs :: [(Expr, (Type, Int))] }

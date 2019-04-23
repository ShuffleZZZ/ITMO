module Main where
import Grammar
import Lexer
import Parser
import ProofParser
import Proofs
import qualified Data.HashSet (empty, fromList, insert, member)
import qualified Data.HashMap.Strict (HashMap, empty, member, insert, update, lookup, fromList)
import System.IO
import Data.Maybe
main :: IO ()
main = do
  string <- getLine
  putStrLn (show (ToProof (hypos (proofparser (alexScanTokens string)))
                          (Not (Not (proofable (proofparser (alexScanTokens string)))))))
  readProof (CurData (Data.HashSet.fromList (hypos (proofparser (alexScanTokens string))))
                      Data.HashSet.empty Data.HashMap.Strict.empty)
readProof cur = do
  end <- isEOF
  if end then return ()
  else do proof <- getLine
          mapM_ putStrLn ((map show) (newExprs cur (parser (alexScanTokens proof))))
          readProof (newData cur (parser (alexScanTokens proof)))
newExprs cur expr | Data.HashSet.member expr (hyps cur) = toNeg2 expr
                  | isAx expr = toNeg2 expr
                  | is10Ax expr = to10Int expr
                  | otherwise = toMP expr cur
isAx (Binary Impl a (Binary Impl b c))
    | (a == c) = True
isAx (Binary Impl (Binary Impl a b) (Binary Impl (Binary Impl c (Binary Impl d e)) (Binary Impl f g)))
    | (a == c) && (c == f) && (b == d) && (e == g) = True
isAx (Binary Impl a (Binary Impl b (Binary And c d)))
    | (a == c) && (b == d) = True
isAx (Binary Impl (Binary And a b) c)
    | (a == c) || (b == c) = True
isAx (Binary Impl a (Binary Or b c))
    | (a == b) || (a == c) = True
isAx (Binary Impl (Binary Impl a b) (Binary Impl (Binary Impl c d) (Binary Impl (Binary Or e f) g)))
    | (a == e) && (b == d) && (d == g) && (c == f) = True
isAx (Binary Impl (Binary Impl a b) (Binary Impl (Binary Impl c (Not d)) (Not e)))
    | (a == c) && (c == e) && (b == d) = True
isAx _ = False
is10Ax (Binary Impl (Not (Not a)) b)
    | (a == b) = True
is10Ax _ = False
newData cur expr = cur { exprs = Data.HashSet.insert expr (exprs cur),
                         partOf = fill expr cur }
toNeg2 expr = replace (Data.HashMap.Strict.fromList [("A", expr)]) toNeg2Str
toMP expr cur = replace (Data.HashMap.Strict.fromList [("A", getLeft expr cur), ("B", expr)]) mPStr
to10Int (Binary Impl a b) = replace (Data.HashMap.Strict.fromList [("A", b)]) ax10Str
replace exprs proof = map (apply exprs . parser . alexScanTokens) proof
fill (Binary Impl a b) cur = if Data.HashMap.Strict.member b (partOf cur) then
      Data.HashMap.Strict.update (\old -> Just (old ++ [a])) b (partOf cur)
      else Data.HashMap.Strict.insert b [a] (partOf cur)
fill _ cur = partOf cur
apply exprs (Binary op a b) = Binary op (apply exprs a) (apply exprs b)
apply exprs (Var var) = fromJust(Data.HashMap.Strict.lookup var exprs)
apply exprs (Not var) = Not (apply exprs var)
getLeft expr cur = func cur (fromJust (Data.HashMap.Strict.lookup expr (partOf cur)))
func cur (next:parts) = if Data.HashSet.member next (exprs cur) then next else func cur (parts)

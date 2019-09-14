module Main where
import Grammar
import Lexer
import Parser
import ProofParser
import Data.List (foldl', sortOn)
import qualified Data.Map.Strict (fromList, empty, toList, insert, lookup, update, member)
import System.IO
import Data.Maybe
main :: IO ()
main = do
    string <- getLine
    readProof (CurData (proofable (proofparser (alexScanTokens string)))
                        (Data.Map.Strict.fromList (folding (hypos (proofparser (alexScanTokens string)))))
                         Data.Map.Strict.empty False 1 Data.Map.Strict.empty)
folding hyps = fst (foldl' (\(fi, se) ls -> ([(ls, se)] ++ fi, se + 1)) ([], 1) hyps)
readProof cur = do
    end <- isEOF
    if end then if checker cur then putStrLn "Proof is incorrect"
                else foldProof (ordExp cur)
    else do proof <- getLine
            newExprs cur (parser (alexScanTokens proof))
ordExp cur = ResStrings (ToProof (map fst (sortOn snd (Data.Map.Strict.toList (hypo cur)))) (str cur))
                    (sortOn (snd . snd) (Data.Map.Strict.toList (annotation cur)))
foldProof list | proofable (toProof list) /= fst (last (exprs list)) = putStrLn "Proof is incorrect"
               | null (exprs list) = putStrLn "Proof is incorrect"
               | otherwise = printRes list
printRes list = do putStrLn (show (toProof (list { exprs = reducer })))
                   printStrings (length resStrings) resStrings
                   where reducer = cut (foldl' redr ([], needed list, 1, 1) (exprs list))
                         resStrings = exprs (list { exprs = reducer })
printStrings len (part:parts) = do
  printStrings (len - 1) parts
  putStrLn (showExpr part len)
printStrings _ [] = putStr ""
showExpr (str, (ann, int)) num = "[" ++ show num ++ ". " ++ show ann ++ "] " ++ show str
cut (fi, _, _, _) = fi
needed list = fst (makeMap (length (exprs list)) (exprs list))
makeMap ln ((_, (MP lf rt, _)):list) = memSd lf rt (makeMap ln list)
makeMap ln (_:list) = redSd (makeMap ln list)
makeMap ln [] = (Data.Map.Strict.fromList [(ln, 0)], ln)
redSd (fi, sd) = (fi, sd - 1)
memSd lf rt (fi, sd) = redSd(if Data.Map.Strict.member sd fi then
        Data.Map.Strict.insert lf 0 (Data.Map.Strict.insert rt 0 fi) else fi, sd)
redr (prev, mapped, num, cur) expr = if Data.Map.Strict.member cur mapped then
        (fillPrt expr prev mapped, Data.Map.Strict.insert cur num mapped, num + 1, cur + 1)
        else (prev, mapped, num, cur + 1)
fillPrt (expr, (MP lf rt, _)) prev mapped = (expr, (MP (fromJust(Data.Map.Strict.lookup lf mapped))
                                            (fromJust(Data.Map.Strict.lookup rt mapped)), 0)) : prev
fillPrt dfr prev mapped = dfr : prev
newExprs cur expr = if Data.Map.Strict.member expr (annotation cur) then
            if expr == str cur then readProof cur {
                annotation = Data.Map.Strict.update (\(old, _) -> Just (old, count cur)) expr (annotation cur),
                checker = False,
                count = (count cur) + 1 }
            else readProof cur { checker = True } else addExpr cur expr
addExpr cur expr | (axNum expr) /= -1 = wrap (Ax (axNum expr)) cur expr
                 | isJust (Data.Map.Strict.lookup expr (hypo cur)) = wrap (Hypo (fromJust (Data.Map.Strict.lookup expr (hypo cur)))) cur expr
                 | (mapperMP cur expr) /= (-1, 0) = wrap (uncurry MP (mapperMP cur expr)) cur expr
                 | otherwise = putStrLn "Proof is incorrect"
axNum (Binary Impl a (Binary Impl b c))
    | (a == c) = 1
axNum (Binary Impl (Binary Impl a b) (Binary Impl (Binary Impl c (Binary Impl d e)) (Binary Impl f g)))
    | (a == c) && (c == f) && (b == d) && (e == g) = 2
axNum (Binary Impl a (Binary Impl b (Binary And c d)))
    | (a == c) && (b == d) = 3
axNum (Binary Impl (Binary And a b) c)
    | (a == c) = 4
axNum (Binary Impl (Binary And a b) c)
    | (b == c) = 5
axNum (Binary Impl a (Binary Or b c))
    | (a == b) = 6
axNum (Binary Impl a (Binary Or b c))
    | (a == c) = 7
axNum (Binary Impl (Binary Impl a b) (Binary Impl (Binary Impl c d) (Binary Impl (Binary Or e f) g)))
    | (a == e) && (b == d) && (d == g) && (c == f) = 8
axNum (Binary Impl (Binary Impl a b) (Binary Impl (Binary Impl c (Not d)) (Not e)))
    | (a == c) && (c == e) && (b == d) = 9
axNum (Binary Impl (Not (Not a)) b)
    | (a == b) = 10
axNum _ = -1
wrap newExpr cur expr = readProof cur {
     annotation = Data.Map.Strict.insert expr (newExpr, count cur) (annotation cur),
     checker = False,
     count = (count cur) + 1,
     partOf = fill expr cur }
mapperMP cur expr = case Data.Map.Strict.lookup expr (partOf cur) of
            Nothing -> (-1, 0)
            Just numsMP -> func cur numsMP
func cur ((va, ho):numsMP) = if fst (func cur numsMP) /= -1 then
        func cur numsMP else case Data.Map.Strict.lookup va (annotation cur) of
                                        Nothing -> (-1, 0)
                                        Just (fi, se) -> (ho, se)
func cur [] = (-1, 0)
fill (Binary Impl a b) cur = if Data.Map.Strict.member b (partOf cur) then
      Data.Map.Strict.update (\old -> Just ((a, count cur) : old)) b (partOf cur)
      else Data.Map.Strict.insert b [(a, count cur)] (partOf cur)
fill _  cur = partOf cur

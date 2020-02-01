module Main where
import Grammar
import Lexer
import Parser
import qualified Data.Map.Strict (empty, member, lookup, insert)
import qualified Data.Set (empty, member, notMember, insert, singleton, union)
import System.IO
import Data.Maybe
main :: IO ()
main = do
  numbers <- getLine
  strings <- getContents
  let expr = parser (alexScanTokens strings)
  putStrLn (show expr)
  printRes (normalize (read (takeWhile (/= ' ') numbers) :: Int)
                      (read (drop 1 (dropWhile (/= ' ') numbers)) :: Int)
                      expr [] (CurData 1 0 Data.Map.Strict.empty))
normalize m k expr res cur = do
    let ((newExpr, toMemoize), nCur) = reduce expr cur
    if toMemoize == False then
        if mod ((step nCur) - 1) k /= 0 then
            memoization newExpr (redexMap nCur) : res
        else res
    else if m <= (step nCur) then res
    else if mod (step nCur) k == 0 then
        normalize m k newExpr (memoization newExpr (redexMap nCur) : res) (inc nCur)
    else normalize m k newExpr res (inc nCur)
    where inc cur = cur { step = (step cur) + 1 }
memoization (Var var) _ = (Var var)
memoization (Lambda var expr) redexMap = (Lambda var (memoization expr redexMap))
memoization (Apl a b) redexMap = (Apl (memoization a redexMap) (memoization b redexMap))
memoization (Redex a) redexMap = memoization (fromJust (Data.Map.Strict.lookup a redexMap)) redexMap
reduce (Var var) cur = ((Var var, False), cur)
reduce (Lambda var expr) cur = do
    let ((newExpr, toMemoize), newCur) = reduce expr cur
    ((Lambda var newExpr, toMemoize), newCur)
reduce (Apl (Redex key) b) cur = do
    let expr = isLambda (Redex key) (redexMap cur)
    case expr of
        Nothing -> reduceFinalApl (Apl (Redex key) b) cur
        Just lambda -> reduce (Apl lambda b) cur
reduce (Apl (Lambda var expr) b) cur = do
    let (newExpr, newCur) = (setName var (Just (Redex (step cur)))
                                     (getSet Data.Set.empty (memoization b (redexMap nCur)))
                                     Data.Map.Strict.empty (memoization expr (redexMap nCur))
                                     nCur)
    ((newExpr, True), newCur)
    where nCur = cur { redexMap = Data.Map.Strict.insert (step cur) b (redexMap cur) }
reduce (Apl a b) cur = reduceFinalApl (Apl a b) cur
reduce (Redex key) cur = do
    let ((newExpr, toMemoize), newCur) = reduce (fromJust (Data.Map.Strict.lookup key (redexMap cur))) cur
    ((Redex key, toMemoize), newCur { redexMap = Data.Map.Strict.insert key newExpr (redexMap newCur) })
reduceFinalApl (Apl a b) cur = do
    let ((newA, toMemoizeA), nCur) = reduce a cur
    if toMemoizeA then (((Apl newA b), True), nCur)
    else do
        let ((newB, toMemoizeB), newCur) = reduce b nCur
        (((Apl newA newB), toMemoizeB), newCur)
setName str redex bonded used (Var var) cur =
    if isJust redex && var == str then (fromJust redex, cur)
    else if Data.Map.Strict.member var used then
        ((Var (fromJust (Data.Map.Strict.lookup var used))), cur)
    else ((Var var), cur)
setName str redex bonded used (Apl a b) cur = do
    let (newLExpr, newCur) = setName str redex bonded used a cur
    let (newRExpr, nextCur) = setName str redex bonded used b newCur
    ((Apl newLExpr newRExpr), nextCur)
setName str redex bonded used (Lambda var expr) cur =
    if str == var then do
        let (newExpr, newCur) = setName str Nothing bonded used expr cur
        ((Lambda var newExpr), newCur)
    else if Data.Set.member var bonded then do
        let (newExpr, newCur) = (setName str redex bonded
                                         (Data.Map.Strict.insert var (nextName var (typeId cur)) used)
                                         expr nCur)
        ((Lambda (nextName var (typeId cur)) newExpr), newCur)
    else do
        let (newExpr, newCur) = setName str redex bonded used expr cur
        ((Lambda var newExpr), newCur)
    where nCur = cur { typeId = (typeId cur) + 1 }
          nextName str num = str ++ (show (num + 1))
isLambda (Redex key) redexMap = func (fromJust (Data.Map.Strict.lookup key redexMap)) redexMap
func (Lambda var expr) _ = Just (Lambda var expr)
func (Redex a) redexMap = isLambda (Redex a) redexMap
func _ _ = Nothing
getSet bonded (Lambda var expr) = getSet (Data.Set.insert var bonded) expr
getSet bonded (Apl a b) = Data.Set.union (getSet bonded a) (getSet bonded b)
getSet bonded (Var var) = if Data.Set.notMember var bonded then
    Data.Set.singleton var else Data.Set.empty
printRes (part:parts) = do
    printRes parts
    putStrLn (show part)
printRes [] = putStr ""

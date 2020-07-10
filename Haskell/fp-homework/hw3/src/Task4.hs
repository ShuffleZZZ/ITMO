{-# LANGUAGE TypeFamilies #-}

module Task4
  ( printFunc
  ) where

import Data.Functor.Const (Const)

import Task3 (HS(..))

-- | Type for 'HS' to 'String' interpreter.
newtype Printable a = Printable { toString :: Int -> String }

instance HS Printable where
  type Ref Printable a = Const String a

  ref @= arg =
    Printable $ \n -> toString ref n <> " = " <> toString arg n <> ";\n"

  line1 # line2 = Printable $ \n -> toString line1 n <> toString line2 n

  a @> b = Printable $ \n -> toString a n <> " > " <> toString b n
  a @< b = Printable $ \n -> toString a n <> " < " <> toString b n
  a @>= b = Printable $ \n -> toString a n <> " >= " <> toString b n
  a @<= b = Printable $ \n -> toString a n <> " <= " <> toString b n
  a @== b = Printable $ \n -> toString a n <> " === " <> toString b n
  a @/= b = Printable $ \n -> toString a n <> " !== " <> toString b n

  a @* b = Printable $ \n -> toString a n <> " * " <> toString b n
  a @+ b = Printable $ \n -> toString a n <> " + " <> toString b n
  a @- b = Printable $ \n -> toString a n <> " - " <> toString b n

  hsFun1 body _ = Printable $ \n -> "function(x" <> show n <> ") {\n"
    <> tabulator ("let x" <> show (n + 1) <> ";\n"
      <> toString (body (Printable $ const $ "x" <> show n)
        $ Printable $ const $ "x" <> show (n + 1))
        (n + 2)
      <> "return x" <> show (n + 1) <> ";"
      )<> "\n}\n"

  hsFun2 body _ _ = Printable $ \n ->
    "function(x" <> show n <> ", " <> show (n + 1) <> ") {\n"
    <> tabulator ("let x" <> show (n + 2) <> ";\n"
      <> toString
          (body (Printable $ const $ "x" <> show n)
                (Printable $ const $ "x" <> show (n + 1))
                (Printable $ const $ "x" <> show (n + 2)))
          (n + 3)
      <> "return x" <> show (n + 2) <> ";"
      ) <> "\n}\n"

  hsWhile cond body = Printable $ \n -> "while (" <> toString cond n <> ") {\n"
    <> tabulator (toString body n) <> "\n}\n"

  hsIf cond body1 body2 = Printable $ \n -> "if (" <> toString cond n <> ") {\n"
    <> tabulator (toString body1 n)
    <> "\n} else {\n"
    <> tabulator (toString body2 n)
    <> "\n}\n"

  hsReadVar var = Printable $ \n -> "(" <> toString var n <> ")"

  hsVarScope var body = Printable $
    \n -> "let x" <> show n <> " = " <> show var <> ";\n"
      <> toString (body $ Printable $ const $ "x" <> show n) (n + 1)

-- | Ident given 'String' with tabs implemented by 2 spaces.
tabulator
  :: String  -- ^ 'HS' code string representation
  -> String  -- ^ same indented 'String'
tabulator = tail . concatMap ("\n  " <>) . lines

-- | Takes 'HS' function and interprets it to JavaScript-like code.
printFunc
  :: (Printable a -> Printable a)  -- ^ function in 'HS' language
  -> String  -- ^ JavaScript representation
printFunc f = toString (f $ Printable $ const $ "arg") 0

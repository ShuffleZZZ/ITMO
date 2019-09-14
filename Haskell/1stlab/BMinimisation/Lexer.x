{ module Lexer where }
%wrapper "basic"
$alpha = [A-Z]
$digit = 0-9
$variable = [$alpha 0-9 \']
:-
$white+;
\( { \_ -> LeftP}
\) { \_ -> RightP}
\| { \_ -> OrOp}
& { \_ -> AndOp}
"->" { \_ -> ImplOp}
! { \_ -> NotOp}
"|-" { \_ -> Cart}
\, {\_ -> Coma}
$alpha [$variable]* { \s -> Id s}
{
data Token = AndOp | OrOp | ImplOp | NotOp | LeftP | RightP | Id String | Cart | Coma
            deriving (Eq, Show)
}

{ module Lexer where }
%wrapper "basic"
$alpha = [a-z]
$digit = 0-9
$variable = [$alpha 0-9 \']
:-
$white+;
[\n];
\( { \_ -> LeftP}
\) { \_ -> RightP}
\. { \_ -> DotOp}
\\ { \_ -> LambdaOp}
$alpha [$variable]* { \s -> Id s}
{
data Token = LambdaOp | DotOp | LeftP | RightP | Id String
           deriving (Eq, Show)
}

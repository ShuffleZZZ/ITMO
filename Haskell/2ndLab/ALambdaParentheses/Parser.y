{ module Parser where
import Grammar
import Lexer }

%name parser
%tokentype { Token }
%error { parsingError }
%token
ID { Id $$ }
DOT { DotOp }
LAMBDA { LambdaOp }
LEFTP { LeftP }
RIGHTP { RightP }
%%
Expr : Apply LAMBDA ID DOT Expr { Apl $1 (Lambda $3 $5) }
     | LAMBDA ID DOT Expr { Lambda $2 $4 }
     | Apply { $1 }
Apply : Apply Atom { Apl $1 $2 }
      | Atom { $1 }
Atom : LEFTP Expr RIGHTP { $2 }
     | ID { Var $1 }
{ parsingError = error "error" }

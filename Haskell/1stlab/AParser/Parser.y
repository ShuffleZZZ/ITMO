{ module Parser where
import Grammar
import Lexer }

%name parser
%tokentype { Token }
%monad { Either String }{ >>= }{ return }
%error { parsingError }
%token
ID { Id $$ }
IMPL { ImplOp }
OR { OrOp }
AND { AndOp }
NOT { NotOp }
LEFTP { LeftP }
RIGHTP { RightP }
%%
Expr : DisExpr { $1 }
     | DisExpr IMPL Expr { Binary Impl $1 $3 }
DisExpr : ConExpr { $1 }
     | DisExpr OR ConExpr { Binary Or $1 $3 }
ConExpr : NotExpr { $1 }
     | ConExpr AND NotExpr { Binary And $1 $3 }
NotExpr : NOT NotExpr { Not $2 }
     | ID { Var $1 }
     | LEFTP Expr RIGHTP { $2 }
{ parsingError = error "error" }

{ module ProofParser where
import Grammar
import Lexer }

%name proofparser
%tokentype { Token }
%error { parsingError }
%token
ID { Id $$ }
IMPL { ImplOp }
OR { OrOp }
AND { AndOp }
NOT { NotOp }
LEFTP { LeftP }
RIGHTP { RightP }
CART { Cart }
COMA { Coma }
%%
ProofExpr : Hypos CART Expr { ToProof $1 $3 }
     | CART Expr { ToProof [] $2 }
Hypos : Hypos COMA Expr { $1 ++ [$3] }
     | Expr { [$1] }
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

grammar GoodImpLang;

program: expressions EOF ;
expressions: expression+ ;
expression: functionDeclaration | line ;

functionDeclaration: FUN functionName OPEN_BRACKET args CLOSE_BRACKET(COLON type)? scope ;
line: flow | (( | declaration | assignment | function) LINE_SEPARATOR) ;

functionName: IDENTIFIER | NEXT_INT | NEXT_BOOL | NEXT_LONG |
                            NEXT_DOUBLE | NEXT_LINE | PRINT ;
type: INT_TYPE | LONG_TYPE | DOUBLE_TYPE | BOOL_TYPE | STRING_TYPE ;
scope: OPEN_SCOPE (line | (returnStatement LINE_SEPARATOR))* CLOSE_SCOPE ;
returnStatement: RETURN value ;

args: | arg | multiArgs ;
multiArgs: arg COMMA multiArg ;
multiArg: arg | arg COMMA multiArg ;
arg: name COLON type ;

flow: forLoop | whileLoop | ifStatement ;
declaration: name COLON type ;
assignment: name (COMMA name)* ASSIGN value (COMMA value)*;
function: functionName OPEN_BRACKET fargs CLOSE_BRACKET;

fargs: | farg | multifargs ;
farg: name | value ;
multifargs: farg COMMA multifarg ;
multifarg: farg | farg COMMA multifarg ;

operation: PLUS | MINUS | MULTIPLY | DIVIDE | MODULE | AND | XOR | OR ;
value: (name | function | literal) (operation (name | function | literal))* ;

literal: numberLiteral | doubleLiteral | boolLiteral | stringLiteral ;
numberLiteral: NUMBER (operation NUMBER)* ;
doubleLiteral: DOUBLE (operation DOUBLE)* ;
boolLiteral: BOOL ((AND | XOR | OR) BOOL)* ;
stringLiteral: STRING (PLUS STRING)* ;

name: IDENTIFIER ;

ifStatement: IF OPEN_BRACKET statement CLOSE_BRACKET scope ;
whileLoop: WHILE OPEN_BRACKET statement CLOSE_BRACKET scope ;
forLoop: FOR OPEN_BRACKET name IN ((NUMBER | name) DOT DOT)? (NUMBER | name) CLOSE_BRACKET scope ;

statement: NOT OPEN_BRACKET statement CLOSE_BRACKET| name | function | predicate ;
predicate: (name | function | literal)
            (LESS_OP | MORE_OP | LESS_OR_EQUAL | MORE_OR_EQUAL | EQUALS | NOT_EQUALS)
                (name | function | literal) ;

fragment EQUALS_SIGN: '=' ;
fragment AND_SIGN: '&' ;
fragment OR_SIGN: '|' ;
fragment XOR_SIGN: '^' ;
fragment NOT_SIGN: '!' ;
fragment LESS_SIGN: '<' ;
fragment MORE_SIGN: '>' ;
fragment DIGITS: [0-9]+ ;

COLON: ':' ;
DOT: '.' ;
COMMA: ',' ;
OPEN_BRACKET: '(' ;
CLOSE_BRACKET: ')' ;
OPEN_SCOPE: '{' ;
CLOSE_SCOPE: '}' ;
LINE_SEPARATOR: '\n' ;

NUMBER: (MINUS)?DIGITS ;
DOUBLE: NUMBER DOT DIGITS ;
STRING: ('"'.*?'"')|('\''.*?'\'') ;
BOOL: 'true'|'false' ;

IF: 'if' ;
WHILE: 'while' ;
FOR: 'for' ;
IN: 'in' ;
FUN: 'fun' ;
RETURN: 'return' ;

MULTIPLY: '*' ;
DIVIDE: '/' ;
PLUS: '+' ;
MINUS: '-' ;
MODULE: '%' ;
ASSIGN: EQUALS_SIGN ;

AND: AND_SIGN AND_SIGN ;
OR: OR_SIGN OR_SIGN ;
XOR: XOR_SIGN ;
NOT: NOT_SIGN ;
LESS_OP: LESS_SIGN ;
MORE_OP: MORE_SIGN ;
LESS_OR_EQUAL: LESS_SIGN EQUALS_SIGN ;
MORE_OR_EQUAL: MORE_SIGN EQUALS_SIGN ;
EQUALS: EQUALS_SIGN EQUALS_SIGN ;
NOT_EQUALS: NOT EQUALS_SIGN ;

INT_TYPE: 'Int' ;
LONG_TYPE: 'Long' ;
BOOL_TYPE: 'Bool' ;
STRING_TYPE: 'String' ;
DOUBLE_TYPE: 'Double' ;

NEXT_INT: 'nextInt' ;
NEXT_LONG: 'nextLong' ;
NEXT_BOOL: 'nextBool' ;
NEXT_DOUBLE: 'nextDouble' ;
NEXT_LINE: 'nextLine' ;

PRINT: 'print' ;

IDENTIFIER: [a-zA-Z][a-zA-Z0-9]* ;
WHITESPACE: [ \t\r\n] -> skip;

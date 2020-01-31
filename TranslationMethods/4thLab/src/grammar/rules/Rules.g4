grammar Rules;

metaGrammar: grammarName header fields? rules ;
grammarName: GRAMMAR IDENTIFIER ;
header: HEADER code ;
fields: FIELDS SQUARE_OPEN field+ SQUARE_CLOSE;
field: IDENTIFIER IDENTIFIER SEMICOLON ;
rules: grammarRule+ ;
grammarRule: tokenRule | syntaxRule ;
tokenRule: TOKEN_NAME COLON REGEX code? SKIP_RULE? SEMICOLON ;
syntaxRule: IDENTIFIER argumentWithType? COLON names SEMICOLON ;
name: TOKEN_NAME | IDENTIFIER argument? ;
names: moreNames | names OR names ;
moreNames: name+ code? ;
code: CODE ;
argument: ARGUMENT ;
argumentWithType: SQUARE_OPEN IDENTIFIER IDENTIFIER SQUARE_CLOSE ;

GRAMMAR: 'grammar' ;
IMPORT: 'import' ;
HEADER: 'header' ;
FIELDS: 'fields' ;
RETURNS: 'returns' ;
PACKAGE: 'package' ;
SKIP_RULE: '-> skip' ;

OR: '|' ;
COLON: ':' ;
SEMICOLON: ';' ;
CURLY_OPEN: '{' ;
CURLY_CLOSE: '}' ;
OPEN: '(' ;
CLOSE: ')' ;
DOT: '.' ;
ASTERISK: '*' ;
SQUARE_OPEN: '[' ;
SQUARE_CLOSE: ']' ;
EQUALS_SIGN: '=' ;

TOKEN_NAME: [A-Z_]+ ;
IDENTIFIER: [a-zA-Z]+ ;
CODE: CURLY_OPEN .+? CURLY_CLOSE ;
ARGUMENT: OPEN .+? CLOSE ;
REGEX: '"'.*?'"' ;
WHITESPACE: [ \t\r\n] -> skip ;
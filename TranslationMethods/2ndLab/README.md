# Descending parser

## C language variables declaration

Starting with type name, variable names, separated by comma, go on. 
To include variables of other type you have to finish previous declaration with semicolon. 
Included support for pointers and references.

Both variable and type names are using the same terminal in grammar for simplicity.

You can check out the <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/grammar.txt">grammar.txt</a> file for such information as: <br>
	• grammar structure <br>
	• states, terminals and their definitions <br>
	• "First" and "Follow" sets <br>

Samples of correct and incorrect expressions could be found at <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/tests">tests</a> folder

Running <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/src/Main.java">Main.java</a> would show the exception on every incorrect test and generate the parse trees of all the correct test files, which could be found in <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/ParseTree">ParseTree</a> folder.
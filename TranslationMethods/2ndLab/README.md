# Descending parser of <a href="https://wikipedia.org/wiki/LL(1)">`LL(1)`</a> grammar

## C language variables declaration

Each declaration starts with a type name, followed by a list of variables separated with comma, ending up with semicolon. Few declarations of the same or different types allowed. Declaration of pointers and references is supported, following the C language initialization `(not a declaration, as you can't leave the declaration of reference without initialization in C)`.

##### Both variable and type names are using the same terminal in grammar for simplicity.

You can check out the <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/grammar.txt">grammar.txt</a> file for such information as: 
* grammar structure
* states, terminals and their definitions
* `First` and `Follow` sets.

Samples of correct and incorrect expressions could be found at the <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/tests">tests</a> folder.

Running <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/src/Main.java">Main.java</a> would show the exception on every incorrect test and generate the parse trees of all the correct test files.
You can find generated HTML files in the <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/ParseTree">ParseTree</a> folder, where the template stylesheet <a href="https://github.com/ShuffleZZZ/ITMO/blob/master/TranslationMethods/2ndLab/ParseTree/ParseTree.css">ParseTree.css</a> is already stored.

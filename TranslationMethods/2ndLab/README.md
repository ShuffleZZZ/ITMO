# Descending parser of [`LL(1)`](https://wikipedia.org/wiki/LL(1)) grammar

## C language variables declaration

Each declaration starts with a type name, followed by a list of variables separated with comma, ending up with semicolon. Few declarations of the same or different types allowed. Declaration of pointers and references is supported, following the C language initialization `(not a declaration, as you can't leave the declaration of reference without initialization in C)`.

##### Both variable and type names are using the same terminal in grammar for simplicity.

You can check out the [grammar.txt](grammar.txt) file for such information as: 
* grammar structure
* states, terminals and their definitions
* `First` and `Follow` sets.

Samples of correct and incorrect expressions could be found at the [tests](tests/) folder.

Running [Main.java](src/Main.java) would show the exception on every incorrect test and generate the parse trees of all the correct test files.
You can find generated HTML files in the [ParseTree](ParseTree/) folder, where the template stylesheet [ParseTree/ParseTree.css](ParseTree/ParseTree.css) is already stored.

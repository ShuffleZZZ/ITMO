package generator

fun main() {
    val calculator = "src/grammar/input/calculator.gr"
    val CDeclaration = "src/grammar/input/CDeclaration.gr"
    val grammar = makeGrammar(calculator)
    LexerGenerator(grammar).generate()
    ParserGenerator(grammar).generate()
}
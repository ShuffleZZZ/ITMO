import calculator.CalculatorLexer
import calculator.CalculatorParser

fun main() {
    val input = "((4 - 2) & (1 - 2 + 3 + 4)) ^ (6 - 1)"
    val input1 = "2**--3"
    val lexer = CalculatorLexer(input1)
    val parser = CalculatorParser(lexer)
    val n = parser.start()
    println(n.`val`)
    println(4 - 2 and 1 - 2 + 3 + 4 xor 6 - 1)
}
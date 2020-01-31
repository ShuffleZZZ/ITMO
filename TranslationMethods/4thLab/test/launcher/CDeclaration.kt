/*import cdeclaration.CDeclarationLexer
import cdeclaration.CDeclarationParser
import java.io.File

var nesting = 3

fun printTree(node: CDeclarationParser.Node, ind: Int) {
    val out = File("ParseTree/ParseTree$ind.html")
    val result = StringBuilder()
    result.append(
            """
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="utf-8">
    <title>Parse tree</title>
    <link rel="stylesheet" href="./ParseTree.css">
</head>
<body>
    <div class="tree">
        <ul>
            """.trimIndent()
    )
    printNode(node, result)
    result.append(
            """
        </ul>
    </div>
</body>
            """.trimIndent()
    )

    out.writeText(result.toString())
}

fun printNode(node: CDeclarationParser.Node, result: StringBuilder) {
    result.append('\n' + "\t".repeat(nesting++) + "<li>\n" +
            "\t".repeat(nesting++) + "<a href=\"#\">\n" +
            "\t".repeat(nesting--) + node.text + '\n' +
            "\t".repeat(nesting) + "</a>\n")

    if (node.children.isNotEmpty()) {
        result.append("\t".repeat(nesting++) + "<ul>")

        node.children.forEach {
            printNode(it, result)
        }

        result.append("\t".repeat(--nesting) + "</ul>\n");
    }

    result.append("\t".repeat(--nesting) + "</li>\n")
}

fun main() {
    for (i in 0..25) {
        val input = File("test/input/input$i.in").readText()
        try {
            val lexer = CDeclarationLexer(input)
            val parser = CDeclarationParser(lexer)
            val function = parser.declaration()
            printTree(function, i)
        } catch (e: CDeclarationParser.ParseException) {
            println("ParseException in test$i \"$input\": ${e.message}")
        } catch (e: CDeclarationLexer.LexicalException) {
            println("LexicalException in test$i \"$input\": ${e.message}")
        }
    }
}*/



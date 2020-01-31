import grammar.GoodImpLangBaseVisitor
import grammar.GoodImpLangParser
import org.antlr.v4.runtime.tree.ParseTree
import org.antlr.v4.runtime.tree.TerminalNode

class GoodImpLangVisitor : GoodImpLangBaseVisitor<String>() {
    private val terms = mutableMapOf(
            Pair("nextInt", "int"), Pair("nextBool", "bool"), Pair("nextLong", "long long"),
            Pair("nextDouble", "double"), Pair("nextLine", "char*")
    )

    private val formats = mapOf(Pair("int", "%d"), Pair("long long", "%lld"), Pair("bool", "%d"), Pair("char*", "%s"), Pair("double", "%lf"))

    private var nesting = 0

    private fun defaultPrintImplementation(name: String): String {
        val varType = argTypes[name]
        return """
            void print($varType arg) {
                printf("${formats[varType]}", arg);
            }
        """.trimIndent()
    }

    private fun defaultNextLineImplementation(): String {
        return """
            char* nextLine() {
                char* result;
                size_t len = 0;
                getline(&result, &len, stdin);
                return result;
            }
        """.trimIndent()
    }

    private fun defaultNextImplementation(name: String): String {
        if (name.endsWith("Line")) return defaultNextLineImplementation()
        val funcType = terms[name]
        val varType = argTypes[name]
        return """
            $funcType $name() {
                $varType result;
                scanf("${formats[varType]}", &result);
                return result;
            }
        """.trimIndent()
    }

    private fun defaultImplementation(name: String) = when {
        name.startsWith("next") -> defaultNextImplementation(name)
        name.startsWith("print") -> defaultPrintImplementation(name)
        else -> ""
    }

    private val types = mapOf(
            Pair("Int", "int"), Pair("Bool", "bool"), Pair("String", "char*"),
            Pair("Double", "double"), Pair("Long", "long long")
    )

    private val argTypes = mapOf(
            Pair("nextInt", "int"), Pair("nextBool", "bool"), Pair("nextLong", "long long"),
            Pair("nextDouble", "double"), Pair("nextLine", "char*"),
            Pair("printInt", "int"), Pair("printLong", "long long"), Pair("printDouble", "double"),
            Pair("printBool", "bool"), Pair("printString", "char*")
    )

    private val defaultIO = argTypes.keys.toMutableSet()

    private val variables = mutableSetOf<String>()
    private val functions = mutableSetOf<String>()

    override fun visitProgram(ctx: GoodImpLangParser.ProgramContext?): String {
        return visit(ctx?.expressions())
    }

    override fun visitExpressions(ctx: GoodImpLangParser.ExpressionsContext?): String {
        val functions = mutableListOf<String>()
        val lines = mutableListOf<String>()
        for (expression in ctx!!.children) {
            val result = visit(expression)
            if (expression.getChild(0) is GoodImpLangParser.FunctionDeclarationContext) {
                functions.add(result)
            } else {
                if (expression.text != "\n") lines.add(result)
            }
        }
        return """#include "stdio.h"

${defaultIO.joinToString("\n\n") { name -> defaultImplementation(name) }}

${functions.joinToString("\n")}
int main() {
    ${lines.joinToString("").split('\n').joinToString("\n\t")}
    return 0;
}
        """.trimIndent()
    }

    override fun visitExpression(ctx: GoodImpLangParser.ExpressionContext?): String {
        return visit(ctx?.getChild(0))
    }

    override fun visitLine(ctx: GoodImpLangParser.LineContext?): String {
        return "${visit(ctx?.getChild(0))};\n"
    }

    override fun visitDeclaration(ctx: GoodImpLangParser.DeclarationContext?): String {
        val children = ctx!!.children
        val name = visit(children[0])
        if (name !in variables) {
            variables.add(name)
        }
        val type = visit(children[2])
        terms[name] = type
        return "$type $name"
    }

    override fun visitAssignment(ctx: GoodImpLangParser.AssignmentContext?): String {
        val children = ctx!!.children
        var eqIndex: Int
        for (i in children.indices) {
            if (children[i].text == "=") {
                eqIndex = i;
            }
        }
        //val eq: String = children.withIndex().map { v -> if (v.value.text == "=") return v.index.toString() }
        val result = StringBuilder()
        for (i in 0..children.size / 2) {
            if (i % 2 == 0) {
                result.append(visitAssignmentValues(i, children) + ";\n")
            }
        }

        return result.toString().dropLast(2)
    }

    private fun visitAssignmentValues(ind: Int, children: List<ParseTree>): String {
        val expressionInd = children.size / 2 + ind + 1
        val name = visit(children[ind])
        val expression = children[expressionInd]
        val value = expression.getChild(0)
        val rightHandSide = visit(expression)
        val term = if (value is GoodImpLangParser.FunctionContext) visit(value.functionName()) else rightHandSide
        var type: String? = terms[name] ?: ""
        if (name !in variables) {
            variables.add(name)
            type = terms[term]
            if (type != null) {
                terms[name] = type
            } else if (expression.getChild(0) is GoodImpLangParser.LiteralContext) {
                val literal = expression.getChild(0) as GoodImpLangParser.LiteralContext
                val inferredType = when {
                    literal.boolLiteral() != null -> "bool"
                    literal.stringLiteral() != null -> "char*"
                    literal.numberLiteral() != null -> "int"
                    literal.doubleLiteral() != null -> "double"
                    else -> ""
                }
                terms[name] = inferredType
                type = inferredType
            }
        }
        return "$type $name = $rightHandSide"
    }

    override fun visitLiteral(ctx: GoodImpLangParser.LiteralContext?): String {
        return ctx!!.children.withIndex().joinToString("") { v -> visit(v.value) }
    }

    override fun visitName(ctx: GoodImpLangParser.NameContext?): String {
        return ctx!!.text
    }

    override fun visitFunctionDeclaration(ctx: GoodImpLangParser.FunctionDeclarationContext?): String {
        val children = ctx!!.children
        val name = visit(children[1])
        val args = visit(children[3])
        val type = if (children.size == 8) visit(children[6]) else "void"
        terms[name] = type
        functions.add(name)
        if (name in defaultIO) defaultIO.remove(name)
        val currentVariables = variables.toMutableSet()
        val arguments = args.split(",")
        for (arg in arguments) {
            if (arg == "") continue
            val s = arg.trim().split(" ")
            val t = s[0]
            val n = s[1]
            variables.add(n)
            terms[n] = t
        }
        val scope = visit(children.last())
        val newcomers = variables.minus(currentVariables)
        for (n in newcomers) {
            terms.remove(n)
            variables.remove(n)
        }
        return "$type $name($args) $scope\n"
    }

    override fun visitFunction(ctx: GoodImpLangParser.FunctionContext?): String {
        return ctx!!.text
    }

    override fun visitFargs(ctx: GoodImpLangParser.FargsContext?): String {
        return ctx!!.text
    }

    override fun visitArgs(ctx: GoodImpLangParser.ArgsContext?): String {
        val children = ctx!!.children
        return if (children != null) visit(children[0]) else ""
    }

    override fun visitArg(ctx: GoodImpLangParser.ArgContext?): String {
        val children = ctx!!.children
        return "${visit(children[2])} ${visit(children[0])}"
    }

    override fun visitMultiArgs(ctx: GoodImpLangParser.MultiArgsContext?): String {
        return ctx!!.children.filter { t -> t !is TerminalNode }.joinToString(", ") { arg -> visit(arg) }
    }

    override fun visitMultiArg(ctx: GoodImpLangParser.MultiArgContext?): String {
        val children = ctx!!.children
        return if (children.size == 1) visit(children[0]) else children.joinToString(", ") { arg -> visit(arg) }
    }

    override fun visitFunctionName(ctx: GoodImpLangParser.FunctionNameContext?): String {
        return ctx!!.text
    }

    override fun visitType(ctx: GoodImpLangParser.TypeContext?): String {
        return types[ctx!!.text] ?: error("Unreachable")
    }

    override fun visitFlow(ctx: GoodImpLangParser.FlowContext?): String {
        return visit(ctx?.getChild(0))
    }

    override fun visitIfStatement(ctx: GoodImpLangParser.IfStatementContext?): String {
        val children = ctx!!.children
        return "if (${visit(children[2])}) ${visit(children[4])}"
    }

    override fun visitWhileLoop(ctx: GoodImpLangParser.WhileLoopContext?): String {
        val children = ctx!!.children
        return "while (${visit(children[2])}) ${visit(children[4])}"
    }

    override fun visitForLoop(ctx: GoodImpLangParser.ForLoopContext?): String {
        val children = ctx!!.children
        val name = visit(children[2])
        val left = if (children.size == 10) children[4].text else "0"
        val right = children[children.size - 3].text
        return "for (int $name = $left; $name <= $right; $name++) ${visit(children.last())}"
    }

    override fun visitScope(ctx: GoodImpLangParser.ScopeContext?): String {
        val children = ctx!!.children
        nesting++
        val s = children.withIndex().filter { v -> v.index > 0 && v.index < children.size - 1 }
                .joinToString("") { v -> if (v.value.text == "\n") "" else "\t".repeat(nesting) + visit(v.value) }
        nesting--
        val postfix = "\t".repeat(nesting)
        return "{\n$s$postfix}"
    }

    override fun visitStatement(ctx: GoodImpLangParser.StatementContext?): String {
        return ctx!!.children.withIndex().joinToString("") { v -> visit(v.value) }
    }

    override fun visitPredicate(ctx: GoodImpLangParser.PredicateContext?): String {
        return ctx!!.children.withIndex().joinToString("") { v ->
            if (v.index % 2 == 1) " ${v.value.text} " else visit(v.value)
        }
    }

    override fun visitReturnStatement(ctx: GoodImpLangParser.ReturnStatementContext?): String {
        return "return ${visit(ctx!!.children[1])};\n"
    }

    override fun visitValue(ctx: GoodImpLangParser.ValueContext?): String {
        return ctx!!.children.withIndex().joinToString("") { v ->
            if (v.index % 2 == 1) " ${v.value.text} " else visit(v.value)
        }
    }

    override fun visitNumberLiteral(ctx: GoodImpLangParser.NumberLiteralContext?): String {
        return ctx!!.children.withIndex().joinToString("") { v ->
            if (v.index % 2 == 1) " ${v.value.text} " else v.value.text
        }
    }

    override fun visitDoubleLiteral(ctx: GoodImpLangParser.DoubleLiteralContext?): String {
        return ctx!!.children.withIndex().joinToString("") { v ->
            if (v.index % 2 == 1) " ${v.value.text} " else v.value.text
        }
    }

    override fun visitBoolLiteral(ctx: GoodImpLangParser.BoolLiteralContext?): String {
        return ctx!!.children.withIndex().joinToString("") { v ->
            if (v.index % 2 == 1) " ${v.value.text} " else v.value.text
        }
    }

    override fun visitStringLiteral(ctx: GoodImpLangParser.StringLiteralContext?): String {
        return ctx!!.children.withIndex().joinToString("") { v ->
            if (v.index % 2 == 1) " ${v.value.text} " else v.value.text
        }
    }
}
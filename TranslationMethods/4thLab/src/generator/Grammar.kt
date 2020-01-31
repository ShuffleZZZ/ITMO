package generator

import grammar.rules.RulesLexer
import grammar.rules.RulesParser
import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import java.io.File

sealed class Rule(open val name: String, open val code: String)
data class Terminal(override val name: String, override val code: String, val pattern: String, val skip: Boolean) :
        Rule(name, code)

data class NonTerminal(override val name: String, override val code: String, val argument: String, val children: List<Pair<String, String>>) :
        Rule(name, code)

data class Grammar(val name: String, val header: String, val rules: List<Rule>, val fields: Set<String>)

const val filePrefix = "generated"
const val epsilon = "EPSILON"
const val empty = ""
const val fourWhitespaces = "    "

private fun makeRules(
        namesContext: RulesParser.NamesContext,
        rules: MutableList<Rule>,
        name: String,
        argument: String
) {
    if (namesContext.OR() != null) {
        makeRules(namesContext.names(0), rules, name, argument)
        makeRules(namesContext.names(1), rules, name, argument)
    } else {
        val moreNamesContext = namesContext.moreNames()
        val code = moreNamesContext.code()?.toStr() ?: empty
        val cnt = if (code == empty) moreNamesContext.childCount else moreNamesContext.childCount - 1
        val children = mutableListOf<Pair<String, String>>()
        for (i in 0 until cnt) {
            val n = moreNamesContext.name(i)
            var arg = if (n.argument() != null) n.argument().ARGUMENT().text else empty
            if (arg != empty) arg = arg.substring(1, arg.length - 1).trim()
            val ident = if (n.IDENTIFIER() != null) n.IDENTIFIER().text else n.TOKEN_NAME().text
            children.add(ident to arg)
        }
        rules.add(NonTerminal(name, code, argument, children))
    }
}

private fun makeRules(rulesContext: RulesParser.RulesContext): List<Rule> {
    val rules = mutableListOf<Rule>()
    val cnt = rulesContext.childCount
    for (i in 0 until cnt) {
        val rule = rulesContext.grammarRule(i)
        val parserRule = rule.syntaxRule()
        val tokenRule = rule.tokenRule()
        if (parserRule != null) {
            val name = parserRule.IDENTIFIER().text
            val names = parserRule.names()
            val argument = parserRule.argumentWithType()
            val arg = argument?.toStr() ?: empty
            makeRules(names, rules, name, arg)
        } else if (tokenRule != null) {
            val name = tokenRule.TOKEN_NAME().text
            val regex = tokenRule.REGEX().text
            val skip = tokenRule.SKIP_RULE() != null
            val code = tokenRule.code()
            rules.add(Terminal(name, code?.toStr() ?: empty, regex.substring(1, regex.length - 1), skip))
        }
    }
    rules.add(Terminal(epsilon, empty, empty, false))
    return rules
}

private fun makeFields(fields: RulesParser.FieldsContext?): Set<String> {
    if (fields == null) return emptySet()
    val result = mutableSetOf<String>()
    for (i in 0 until fields.childCount - 3) {
        result.add(fields.field(i).toStr())
    }
    return result
}

fun makeGrammar(filename: String): Grammar {
    val input = File(filename).readText()
    val lexer = RulesLexer(CharStreams.fromString(input))
    val parser = RulesParser(CommonTokenStream(lexer))
    val metaGrammar = parser.metaGrammar()
    val grammar = Grammar(
            metaGrammar.grammarName().IDENTIFIER().text,
            metaGrammar.header().code().toStr().toLowerCase(),
            makeRules(metaGrammar.rules()),
            makeFields(metaGrammar.fields())
    )
    grammar.validate()
    return grammar
}

private fun RulesParser.ArgumentWithTypeContext.toStr(): String {
    return "${IDENTIFIER(0).text} ${IDENTIFIER(1).text}"
}

private fun RulesParser.CodeContext.toStr(): String {
    val lines = text.substring(1, text.length - 1).split("\n").map { it.trim() }
    return lines.joinToString("\n")
}

private fun RulesParser.FieldContext.toStr(): String {
    return "${IDENTIFIER(0).text} ${IDENTIFIER(1).text}"
}

private fun Grammar.validate() {
    val r = rules.map { it.name }.toHashSet()
    for (rule in rules) {
        if (rule is NonTerminal) {
            val children = rule.children
            for (c in children) {
                if (c.first !in r) throw IllegalStateException("Rule $c is not present in the grammar!")
            }
        }
    }
}
package generator

import java.io.File

class ParserGenerator(val grammar: Grammar) {
    private val first = mutableMapOf<String, MutableSet<String>>()
    private val firstRight = mutableMapOf<List<Pair<String, String>>, MutableSet<String>>()
    private val follow = mutableMapOf<String, MutableSet<String>>()

    private val prefix = "${filePrefix}/${grammar.name.toLowerCase()}"

    private fun makeFirst() {
        for (r in grammar.rules) {
            first[r.name] = mutableSetOf()
            when (r) {
                is Terminal -> firstRight[listOf(r.name to empty)] = mutableSetOf()
                is NonTerminal -> firstRight[r.children] = mutableSetOf()
            }
        }
        var changed = true
        while (changed) {
            changed = false
            for (r in grammar.rules) {
                val cur = first[r.name]!!.toMutableSet()
                when (r) {
                    is Terminal -> {
                        first[r.name]!!.add(r.name)
                        firstRight[listOf(r.name to empty)]!!.add(r.name)
                    }
                    is NonTerminal -> {
                        first[r.name]!!.addAll(first[r.children[0].first]!!)
                        firstRight[r.children]!!.addAll(first[r.children[0].first]!!)
                        var i = 0
                        while (epsilon in first[r.children[i].first]!!) {
                            i++
                            if (i == r.children.size) break
                            first[r.name]!!.addAll(first[r.children[i].first]!!)
                            firstRight[r.children]!!.addAll(first[r.children[i].first]!!)
                        }
                    }
                }
                if (first[r.name]!! != cur) {
                    changed = true
                }
            }
        }
    }

    private fun makeFollow() {
        val rules = grammar.rules
        val nonTerminals = rules.filterIsInstance<NonTerminal>()
        val nonTerminalNames = nonTerminals.map { it.name }.toHashSet()
        for (r in rules) {
            follow[r.name] = mutableSetOf()
        }
        follow[rules[0].name]!!.add("EOF")
        var changed = true
        while (changed) {
            changed = false
            for (n in nonTerminals) {
                for (i in n.children.indices) {
                    val b = n.children[i].first
                    if (b in nonTerminalNames) {
                        val gamma = if (i == n.children.size - 1) epsilon else n.children[i + 1].first
                        val cur = follow[b]!!.toMutableSet()
                        follow[b]!!.addAll(first[gamma]!!.minus(epsilon))
                        if (epsilon in first[gamma]!!) {
                            follow[b]!!.addAll(follow[n.name]!!)
                        }
                        if (follow[b]!! != cur) {
                            changed = true
                        }
                    }
                }
            }
        }
    }

    private fun generateFunction(name: String): String {
        val follows = if (epsilon in first[name]!!) follow[name]!! else emptySet<String>()
        val alphas = grammar.rules.filter { it.name == name }.toMutableList()
        val firstToAlpha = HashMap<String, Rule>()
        val nonTerminals = grammar.rules.filterIsInstance<NonTerminal>()
        val nonTerminalNames = nonTerminals.map { it.name }
        val rule = nonTerminals.find { it.name == name }!!
        val epsilonCode = alphas.find { it is NonTerminal && it.children.map { p -> p.first }.contains(epsilon) }?.code ?: empty
        for (a in alphas) {
            when (a) {
                is Terminal -> firstToAlpha[a.name] = a
                is NonTerminal -> firstRight[a.children]!!.filter { it != epsilon }.forEach { firstToAlpha[it] = a }
            }
        }
        return """
    public Node $name(${rule.argument}) {
        Node res = new Node("$name", Rule.$name);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            ${firstToAlpha.entries.joinToString("\n${fourWhitespaces.repeat(3)}") {
            """
            case ${it.key}: {
                ${(it.value as NonTerminal).children.joinToString("\n${fourWhitespaces.repeat(4)}") { c ->
                when (c.first) {
                    !in nonTerminalNames -> {
                        """
                Node ${c.first} = new Node(lexer.getCurToken().getText(), Rule.${c.first});
                res.children.add(${c.first});
                consume(Rule.${c.first});
                        """.trim()
                    }
                    else -> {
                        """
                Node ${c.first} = ${c.first}(${if ("**" in c.second) {
                            val args = c.second.split(" ")
                            "(int) Math.pow(${args[0]}, ${args[2]})"
                        } else {
                        c.second
                        }});
                res.children.add(${c.first});
                        """.trim()
                    }
                }
            }}
                ${it.value.code}
                break;
            }
                """.trim()
        }}
            ${follows.joinToString("\n${fourWhitespaces.repeat(3)}") {
            """
            case ${it}:
                $epsilonCode
                break;
                """.trim()
        }}
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }
        """.trim()
    }

    private fun generateParser() {
        val parserName = "${grammar.name}Parser"
        val lexerName = "${grammar.name}Lexer"
        val nonTerminals = grammar.rules.filterIsInstance<NonTerminal>()
        val nonTerminalNames = nonTerminals.map { it.name }.toHashSet()
        File("${prefix}/${parserName}.java").writeText(
                """
${grammar.header}

import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("all")
public class $parserName {
    private final $lexerName lexer;
    
    public $parserName(final $lexerName lexer) {
        this.lexer = lexer;
        lexer.nextToken();
    }
    
    public static class Node {
        private final String text;
        private final Rule rule;
        ${grammar.fields.joinToString("\n${fourWhitespaces.repeat(2)}") { "public $it;" }}
        private List<Node> children = new ArrayList<>();
        
        public Node(final String text, final Rule rule) {
            this.text = text;
            this.rule = rule;
        }
        
        public String getText() {
            return text;
        }
        
        public Rule getRule() {
            return rule;
        }
        
        public List<Node> getChildren() {
            return children;
        }
    }
    
    public static class ParseException extends RuntimeException {
        public ParseException(String message) {
            super(message);
        }
    }
    
    ${nonTerminalNames.joinToString("\n\n${fourWhitespaces}") { generateFunction(it) }}
    
    private void consume(final Rule expected) {
        Rule actual = lexer.getCurToken().getRule();
        if (expected != actual) {
            throw new ParseException("Illegal token " + actual.name() + ", expected " + expected.name());
        }
        lexer.nextToken();
    }
}
            """.trim()
        )
    }

    fun generate() {
        makeFirst()
        makeFollow()
        generateParser()
    }
}
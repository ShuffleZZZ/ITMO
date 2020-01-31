package generator

import java.io.File

class LexerGenerator(val grammar: Grammar) {
    private val prefix = "${filePrefix}/${grammar.name.toLowerCase()}"

    private fun generateEnum() {
        if (!File(prefix).exists()) {
            File(prefix).mkdir()
        }
        val tokenRules = grammar.rules.map { when(it) {
            is Terminal -> "${it.name}(true)"
            is NonTerminal -> "${it.name}(false)"
        } }.toHashSet().joinToString(",\n$fourWhitespaces")
        File("${prefix}/Rule.java").writeText(
                """
${grammar.header}
public enum Rule {
    $tokenRules,
    EOF(true),
    DUMMY(true);
                    
    private final boolean isTerminal;
    Rule(final boolean isTerminal) {
        this.isTerminal = isTerminal;
    }
    public boolean isTerminal() {
        return isTerminal;
    }
}
            """.trimIndent()
        )
    }

    private fun generateLexer(tokens: List<Terminal>) {
        fun escape(s: String) = s.replace("\\", "\\\\").replace("\"", "\\\"")
        val allPatterns = tokens.joinToString("|") { "(${escape(it.pattern)})" }
        File("${prefix}/${grammar.name}Lexer.java").writeText(
                """
${grammar.header}

import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ${grammar.name}Lexer {
    private final String input;
    private final int length;
    private Token curToken;
    private StringBuilder word;
    private int index;
    
    public static class Token {
        private final Rule rule;
        private final String text;
        
        public Token(final Rule rule, final String text) {
            this.rule = rule;
            this.text = text;
        }
        
        public Rule getRule() {
            return rule;
        }
        
        public String getText() {
            return text;
        }
    }
    
    private static class TokenRule {
        private final Rule rule;
        private final Pattern pattern;
        
        private TokenRule(Rule rule, Pattern pattern) {
            this.rule = rule;
            this.pattern = pattern;
        }
    }
    
    public static class LexicalException extends RuntimeException {
        public LexicalException(String message) {
            super(message);
        }
    }
    
    private final Pattern allPatterns = Pattern.compile("$allPatterns");
    
    private final List<TokenRule> tokenRules = Arrays.asList(
            ${tokens.joinToString(",\n${fourWhitespaces.repeat(3)}") { "new TokenRule(Rule.${it.name}, Pattern.compile(\"${escape(it.pattern)}\"))" }}
    );
    
    private Set<Rule> ignore = Set.of(
            ${tokens.filter { it.skip }.joinToString(",\n${fourWhitespaces.repeat(3)}") { "Rule.${it.name}" }}
    );
    
    private Rule find(final String s) {
        Rule result = Rule.DUMMY;
        for (final TokenRule r : tokenRules) {
            if (r.pattern.matcher(s).matches()) {
                result = r.rule;
                break;
            }
        }
        return result;
    }
    
    public ${grammar.name}Lexer(final String input) {
        this.input = input;
        this.word = new StringBuilder();
        this.curToken = new Token(Rule.DUMMY, "");
        this.index = 0;
        this.length = input.length();
    }
    
    public Token getCurToken() {
        return curToken;
    }
    
    public void nextToken() {
        word = new StringBuilder();
        if (index == length) {
            curToken = new Token(Rule.EOF, "");
            return;
        }
        char cur = input.charAt(index);
        index++;
        word.append(cur);
        String s = word.toString();
        Rule t = find(s);
        Matcher m = allPatterns.matcher(s);
        if (m.matches()) {
            while (index < length) {
                cur = input.charAt(index);
                index++;
                word.append(cur);
                s = word.toString();
                t = find(s);
                m = allPatterns.matcher(s);
                if (!m.matches()) {
                    index--;
                    s = s.substring(0, s.length() - 1);
                    t = find(s);
                    if (ignore.contains(t)) {
                        nextToken();
                        return;
                    }
                    break;
                }
            }
            curToken = new Token(t, s);
        } else {
            throw new LexicalException("Unexpected token " + word.toString());
        }
    }
}
            """.trimIndent()
        )
    }

    fun generate() {
        generateEnum()
        generateLexer(grammar.rules.filterIsInstance<Terminal>().filter { it.name != epsilon })
    }
}
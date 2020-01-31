package calculator;

import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CalculatorLexer {
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
    
    private final Pattern allPatterns = Pattern.compile("(\\d+(\\.\\d+)?)|([\\n\\r\\t ]+)|(\\+)|(-)|(\\*\\*)|(\\*)|(/)|(\\()|(\\))|(\\|)|(&)|(\\^)|(!)");
    
    private final List<TokenRule> tokenRules = Arrays.asList(
            new TokenRule(Rule.NUMBER, Pattern.compile("\\d+(\\.\\d+)?")),
            new TokenRule(Rule.WHITESPACES, Pattern.compile("[\\n\\r\\t ]+")),
            new TokenRule(Rule.PLUS, Pattern.compile("\\+")),
            new TokenRule(Rule.MINUS, Pattern.compile("-")),
            new TokenRule(Rule.POW, Pattern.compile("\\*\\*")),
            new TokenRule(Rule.MULTIPLY, Pattern.compile("\\*")),
            new TokenRule(Rule.DIVIDE, Pattern.compile("/")),
            new TokenRule(Rule.OPEN, Pattern.compile("\\(")),
            new TokenRule(Rule.CLOSE, Pattern.compile("\\)")),
            new TokenRule(Rule.OR, Pattern.compile("\\|")),
            new TokenRule(Rule.AND, Pattern.compile("&")),
            new TokenRule(Rule.XOR, Pattern.compile("\\^")),
            new TokenRule(Rule.NOT, Pattern.compile("!"))
    );
    
    private Set<Rule> ignore = Set.of(
            Rule.WHITESPACES
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
    
    public CalculatorLexer(final String input) {
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
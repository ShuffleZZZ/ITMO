package cdeclaration;

import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("all")
public class CDeclarationParser {
    private final CDeclarationLexer lexer;
    
    public CDeclarationParser(final CDeclarationLexer lexer) {
        this.lexer = lexer;
        lexer.nextToken();
    }
    
    public static class Node {
        private final String text;
        private final Rule rule;
        public String val;
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
    
    public Node nextVar() {
        Node res = new Node("nextVar", Rule.nextVar);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case COMMA: {
                Node COMMA = new Node(lexer.getCurToken().getText(), Rule.COMMA);
                res.children.add(COMMA);
                consume(Rule.COMMA);
                Node vars = vars();
                res.children.add(vars);
                res.val = COMMA.text + " " + vars.val;
                break;
            }
            case SEMICOLON:
                res.val = "";
                break;
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node name() {
        Node res = new Node("name", Rule.name);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case IDENTIFIER: {
                Node IDENTIFIER = new Node(lexer.getCurToken().getText(), Rule.IDENTIFIER);
                res.children.add(IDENTIFIER);
                consume(Rule.IDENTIFIER);
                res.val = IDENTIFIER.text;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node variable() {
        Node res = new Node("variable", Rule.variable);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case POINTER: {
                Node POINTER = new Node(lexer.getCurToken().getText(), Rule.POINTER);
                res.children.add(POINTER);
                consume(Rule.POINTER);
                Node variable = variable();
                res.children.add(variable);
                res.val = POINTER.text + variable.val;
                break;
            }
            case IDENTIFIER: {
                Node name = name();
                res.children.add(name);
                res.val = name.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node vars() {
        Node res = new Node("vars", Rule.vars);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case POINTER: {
                Node variable = variable();
                res.children.add(variable);
                Node nextVar = nextVar();
                res.children.add(nextVar);
                res.val = variable.val + nextVar.val;
                break;
            }
            case IDENTIFIER: {
                Node variable = variable();
                res.children.add(variable);
                Node nextVar = nextVar();
                res.children.add(nextVar);
                res.val = variable.val + nextVar.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node type() {
        Node res = new Node("type", Rule.type);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case IDENTIFIER: {
                Node IDENTIFIER = new Node(lexer.getCurToken().getText(), Rule.IDENTIFIER);
                res.children.add(IDENTIFIER);
                consume(Rule.IDENTIFIER);
                res.val = IDENTIFIER.text;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node declaration() {
        Node res = new Node("declaration", Rule.declaration);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case IDENTIFIER: {
                Node type = type();
                res.children.add(type);
                Node vars = vars();
                res.children.add(vars);
                Node SEMICOLON = new Node(lexer.getCurToken().getText(), Rule.SEMICOLON);
                res.children.add(SEMICOLON);
                consume(Rule.SEMICOLON);
                Node declaration = declaration();
                res.children.add(declaration);
                res.val = type.val + " " + vars.val + "; " + declaration.val;
                break;
            }
            case EOF:
                res.val = "";
                break;
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }
    
    private void consume(final Rule expected) {
        Rule actual = lexer.getCurToken().getRule();
        if (expected != actual) {
            throw new ParseException("Illegal token " + actual.name() + ", expected " + expected.name());
        }
        lexer.nextToken();
    }
}
package calculator;

import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("all")
public class CalculatorParser {
    private final CalculatorLexer lexer;
    
    public CalculatorParser(final CalculatorLexer lexer) {
        this.lexer = lexer;
        lexer.nextToken();
    }
    
    public static class Node {
        private final String text;
        private final Rule rule;
        public int val;
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
    
    public Node a() {
        Node res = new Node("a", Rule.a);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NOT: {
                Node e = e();
                res.children.add(e);
                Node d = d(e.val);
                res.children.add(d);
                res.val = d.val;
                break;
            }
            case NUMBER: {
                Node e = e();
                res.children.add(e);
                Node d = d(e.val);
                res.children.add(d);
                res.val = d.val;
                break;
            }
            case MINUS: {
                Node e = e();
                res.children.add(e);
                Node d = d(e.val);
                res.children.add(d);
                res.val = d.val;
                break;
            }
            case OPEN: {
                Node e = e();
                res.children.add(e);
                Node d = d(e.val);
                res.children.add(d);
                res.val = d.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node d(int acc) {
        Node res = new Node("d", Rule.d);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case XOR: {
                Node XOR = new Node(lexer.getCurToken().getText(), Rule.XOR);
                res.children.add(XOR);
                consume(Rule.XOR);
                Node e = e();
                res.children.add(e);
                Node d = d(acc ^ e.val);
                res.children.add(d);
                res.val = d.val;
                break;
            }
            case OR:
                res.val = acc;
                break;
            case EOF:
                res.val = acc;
                break;
            case CLOSE:
                res.val = acc;
                break;
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node e() {
        Node res = new Node("e", Rule.e);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NOT: {
                Node s = s();
                res.children.add(s);
                Node q = q(s.val);
                res.children.add(q);
                res.val = q.val;
                break;
            }
            case NUMBER: {
                Node s = s();
                res.children.add(s);
                Node q = q(s.val);
                res.children.add(q);
                res.val = q.val;
                break;
            }
            case MINUS: {
                Node s = s();
                res.children.add(s);
                Node q = q(s.val);
                res.children.add(q);
                res.val = q.val;
                break;
            }
            case OPEN: {
                Node s = s();
                res.children.add(s);
                Node q = q(s.val);
                res.children.add(q);
                res.val = q.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node f() {
        Node res = new Node("f", Rule.f);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NUMBER: {
                Node h = h();
                res.children.add(h);
                res.val = h.val;
                break;
            }
            case MINUS: {
                Node MINUS = new Node(lexer.getCurToken().getText(), Rule.MINUS);
                res.children.add(MINUS);
                consume(Rule.MINUS);
                Node h = h();
                res.children.add(h);
                res.val = -h.val;
                break;
            }
            case OPEN: {
                Node h = h();
                res.children.add(h);
                res.val = h.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node g() {
        Node res = new Node("g", Rule.g);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NOT: {
                Node NOT = new Node(lexer.getCurToken().getText(), Rule.NOT);
                res.children.add(NOT);
                consume(Rule.NOT);
                Node g = g();
                res.children.add(g);
                res.val = ~g.val;
                break;
            }
            case NUMBER: {
                Node f = f();
                res.children.add(f);
                res.val = f.val;
                break;
            }
            case MINUS: {
                Node f = f();
                res.children.add(f);
                res.val = f.val;
                break;
            }
            case OPEN: {
                Node f = f();
                res.children.add(f);
                res.val = f.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node start() {
        Node res = new Node("start", Rule.start);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NOT: {
                Node v = v();
                res.children.add(v);
                res.val = v.val;
                break;
            }
            case NUMBER: {
                Node v = v();
                res.children.add(v);
                res.val = v.val;
                break;
            }
            case MINUS: {
                Node v = v();
                res.children.add(v);
                res.val = v.val;
                break;
            }
            case OPEN: {
                Node v = v();
                res.children.add(v);
                res.val = v.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node h() {
        Node res = new Node("h", Rule.h);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NUMBER: {
                Node j = j();
                res.children.add(j);
                Node k = k();
                res.children.add(k);
                res.val = (int) Math.pow(j.val, k.val);
                break;
            }
            case OPEN: {
                Node j = j();
                res.children.add(j);
                Node k = k();
                res.children.add(k);
                res.val = (int) Math.pow(j.val, k.val);
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node j() {
        Node res = new Node("j", Rule.j);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NUMBER: {
                Node NUMBER = new Node(lexer.getCurToken().getText(), Rule.NUMBER);
                res.children.add(NUMBER);
                consume(Rule.NUMBER);
                res.val = Integer.parseInt(NUMBER.text);
                break;
            }
            case OPEN: {
                Node OPEN = new Node(lexer.getCurToken().getText(), Rule.OPEN);
                res.children.add(OPEN);
                consume(Rule.OPEN);
                Node start = start();
                res.children.add(start);
                Node CLOSE = new Node(lexer.getCurToken().getText(), Rule.CLOSE);
                res.children.add(CLOSE);
                consume(Rule.CLOSE);
                res.val = start.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node k() {
        Node res = new Node("k", Rule.k);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case POW: {
                Node POW = new Node(lexer.getCurToken().getText(), Rule.POW);
                res.children.add(POW);
                consume(Rule.POW);
                Node h = h();
                res.children.add(h);
                res.val = h.val;
                break;
            }
            case MULTIPLY:
                res.val = 1;
                break;
            case DIVIDE:
                res.val = 1;
                break;
            case PLUS:
                res.val = 1;
                break;
            case MINUS:
                res.val = 1;
                break;
            case AND:
                res.val = 1;
                break;
            case XOR:
                res.val = 1;
                break;
            case OR:
                res.val = 1;
                break;
            case EOF:
                res.val = 1;
                break;
            case CLOSE:
                res.val = 1;
                break;
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node q(int acc) {
        Node res = new Node("q", Rule.q);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case AND: {
                Node AND = new Node(lexer.getCurToken().getText(), Rule.AND);
                res.children.add(AND);
                consume(Rule.AND);
                Node s = s();
                res.children.add(s);
                Node q = q(acc & s.val);
                res.children.add(q);
                res.val = q.val;
                break;
            }
            case XOR:
                res.val = acc;
                break;
            case OR:
                res.val = acc;
                break;
            case EOF:
                res.val = acc;
                break;
            case CLOSE:
                res.val = acc;
                break;
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node s() {
        Node res = new Node("s", Rule.s);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NOT: {
                Node t = t();
                res.children.add(t);
                Node x = x(t.val);
                res.children.add(x);
                res.val = x.val;
                break;
            }
            case NUMBER: {
                Node t = t();
                res.children.add(t);
                Node x = x(t.val);
                res.children.add(x);
                res.val = x.val;
                break;
            }
            case MINUS: {
                Node t = t();
                res.children.add(t);
                Node x = x(t.val);
                res.children.add(x);
                res.val = x.val;
                break;
            }
            case OPEN: {
                Node t = t();
                res.children.add(t);
                Node x = x(t.val);
                res.children.add(x);
                res.val = x.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node t() {
        Node res = new Node("t", Rule.t);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NOT: {
                Node g = g();
                res.children.add(g);
                Node y = y(g.val);
                res.children.add(y);
                res.val = y.val;
                break;
            }
            case NUMBER: {
                Node g = g();
                res.children.add(g);
                Node y = y(g.val);
                res.children.add(y);
                res.val = y.val;
                break;
            }
            case MINUS: {
                Node g = g();
                res.children.add(g);
                Node y = y(g.val);
                res.children.add(y);
                res.val = y.val;
                break;
            }
            case OPEN: {
                Node g = g();
                res.children.add(g);
                Node y = y(g.val);
                res.children.add(y);
                res.val = y.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node v() {
        Node res = new Node("v", Rule.v);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case NOT: {
                Node a = a();
                res.children.add(a);
                Node w = w(a.val);
                res.children.add(w);
                res.val = w.val;
                break;
            }
            case NUMBER: {
                Node a = a();
                res.children.add(a);
                Node w = w(a.val);
                res.children.add(w);
                res.val = w.val;
                break;
            }
            case MINUS: {
                Node a = a();
                res.children.add(a);
                Node w = w(a.val);
                res.children.add(w);
                res.val = w.val;
                break;
            }
            case OPEN: {
                Node a = a();
                res.children.add(a);
                Node w = w(a.val);
                res.children.add(w);
                res.val = w.val;
                break;
            }
            
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node w(int acc) {
        Node res = new Node("w", Rule.w);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case OR: {
                Node OR = new Node(lexer.getCurToken().getText(), Rule.OR);
                res.children.add(OR);
                consume(Rule.OR);
                Node a = a();
                res.children.add(a);
                Node w = w(acc | a.val);
                res.children.add(w);
                res.val = w.val;
                break;
            }
            case EOF:
                res.val = acc;
                break;
            case CLOSE:
                res.val = acc;
                break;
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node x(int acc) {
        Node res = new Node("x", Rule.x);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case PLUS: {
                Node PLUS = new Node(lexer.getCurToken().getText(), Rule.PLUS);
                res.children.add(PLUS);
                consume(Rule.PLUS);
                Node t = t();
                res.children.add(t);
                Node x = x(acc + t.val);
                res.children.add(x);
                res.val = x.val;
                break;
            }
            case MINUS: {
                Node MINUS = new Node(lexer.getCurToken().getText(), Rule.MINUS);
                res.children.add(MINUS);
                consume(Rule.MINUS);
                Node t = t();
                res.children.add(t);
                Node x = x(acc - t.val);
                res.children.add(x);
                res.val = x.val;
                break;
            }
            case AND:
                res.val = acc;
                break;
            case XOR:
                res.val = acc;
                break;
            case OR:
                res.val = acc;
                break;
            case EOF:
                res.val = acc;
                break;
            case CLOSE:
                res.val = acc;
                break;
            default:
                throw new ParseException("Illegal token " + currentRule.name());
        }
        return res;
    }

    public Node y(int acc) {
        Node res = new Node("y", Rule.y);
        Rule currentRule = lexer.getCurToken().getRule();
        switch (currentRule) {
            case MULTIPLY: {
                Node MULTIPLY = new Node(lexer.getCurToken().getText(), Rule.MULTIPLY);
                res.children.add(MULTIPLY);
                consume(Rule.MULTIPLY);
                Node g = g();
                res.children.add(g);
                Node y = y(acc * g.val);
                res.children.add(y);
                res.val = y.val;
                break;
            }
            case DIVIDE: {
                Node DIVIDE = new Node(lexer.getCurToken().getText(), Rule.DIVIDE);
                res.children.add(DIVIDE);
                consume(Rule.DIVIDE);
                Node g = g();
                res.children.add(g);
                Node y = y(acc / g.val);
                res.children.add(y);
                res.val = y.val;
                break;
            }
            case PLUS:
                res.val = acc;
                break;
            case MINUS:
                res.val = acc;
                break;
            case AND:
                res.val = acc;
                break;
            case XOR:
                res.val = acc;
                break;
            case OR:
                res.val = acc;
                break;
            case EOF:
                res.val = acc;
                break;
            case CLOSE:
                res.val = acc;
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
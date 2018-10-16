package expression.parser;

import expression.exceptions.TripleExpression;

public class Const implements TripleExpression {
    private Number s;
    public Const(Number x) {
        s = x;
    }
    public int evaluate(int x, int y, int z) {
        return s.intValue();
    }
}
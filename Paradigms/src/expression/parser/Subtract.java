package expression.parser;

import expression.exceptions.TripleExpression;

public class Subtract extends AbstractOperation {
    public Subtract(TripleExpression x, TripleExpression y) {
        super(x, y);
    }
    protected int count(int x, int y) {
        return x - y;
    }
}
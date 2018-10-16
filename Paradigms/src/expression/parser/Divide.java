package expression.parser;

import expression.exceptions.TripleExpression;

public class Divide extends AbstractOperation {
    public Divide(TripleExpression x, TripleExpression y) {
        super(x, y);
    }
    protected int count(int x, int y) {
        return x / y;
    }
}
package expression.parser;

import expression.exceptions.TripleExpression;

public class And extends AbstractOperation {
    public And(TripleExpression x, TripleExpression y) {
        super(x, y);
    }

    protected int count(int x, int y) {
        return x & y;
    }
}
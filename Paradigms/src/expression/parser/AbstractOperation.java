package expression.parser;

import expression.exceptions.TripleExpression;

public abstract class AbstractOperation implements TripleExpression {
    private TripleExpression a, b;

    public AbstractOperation(TripleExpression x, TripleExpression y) {
        a = x; b = y;
    }

    protected abstract int count(int x, int y);

    public int evaluate(int x, int y, int z) throws Exception {
        return count(a.evaluate(x, y, z), b.evaluate(x, y, z));
    }
}

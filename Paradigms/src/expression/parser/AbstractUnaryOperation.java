package expression.parser;

import expression.exceptions.TripleExpression;

public abstract class AbstractUnaryOperation implements TripleExpression {
    private TripleExpression a;

    public AbstractUnaryOperation(TripleExpression x) {
        a = x;
    }

    protected abstract int count(int x);

    public int evaluate(int x, int y, int z) throws Exception {
        return count(a.evaluate(x, y, z));
    }
}

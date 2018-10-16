package expression.exceptions;

public abstract class AbstractUnaryOperation implements TripleExpression {
    private TripleExpression a;

    protected AbstractUnaryOperation(TripleExpression x) {
        a = x;
    }

    protected abstract void check(int x) throws Exception;

    protected abstract int count(int x) throws Exception;

    public int evaluate(int x, int y, int z) throws Exception {
        return count(a.evaluate(x, y, z));
    }
}

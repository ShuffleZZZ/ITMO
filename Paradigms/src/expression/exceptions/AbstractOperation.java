package expression.exceptions;

public abstract class AbstractOperation implements TripleExpression {
    private TripleExpression a, b;

    protected AbstractOperation(TripleExpression x, TripleExpression y) {
        a = x; b = y;
    }

    protected abstract void check(int x, int y) throws Exception;

    protected abstract int count(int x, int y) throws Exception;

    public int evaluate(int x, int y, int z) throws Exception {
        return count(a.evaluate(x, y, z), b.evaluate(x, y, z));
    }
}
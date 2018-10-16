package expression.exceptions;

public class CheckedNegate extends AbstractUnaryOperation {
    public CheckedNegate(TripleExpression x) {
        super(x);
    }
    protected void check(int x) throws OverflowException {
        if (x == Integer.MIN_VALUE) {
            throw new OverflowException();
        }
    }
    protected int count(final int x) throws OverflowException {
        check(x);
        return -x;
    }
}
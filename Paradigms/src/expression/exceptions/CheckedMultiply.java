package expression.exceptions;

public class CheckedMultiply extends AbstractOperation {
    public CheckedMultiply(TripleExpression x, TripleExpression y) {
        super(x, y);
    }
    protected void check(int x, int y) throws OverflowException {
        if (x > 0 && y > 0 && Integer.MAX_VALUE / x < y) {
            throw new OverflowException();
        }
        if (x > 0 && y < 0 && Integer.MIN_VALUE / x > y) {
            throw new OverflowException();
        }
        if (x < 0 && y > 0 && Integer.MIN_VALUE / y > x) {
            throw new OverflowException();
        }
        if (x < 0 && y < 0 && Integer.MAX_VALUE / x > y) {
            throw new OverflowException();
        }
    }
    protected int count(int x, int y) throws OverflowException {
        check(x, y);
        return x * y;
    }
}

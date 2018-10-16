package expression.exceptions;

public class CheckedDivide extends AbstractOperation {
    public CheckedDivide(TripleExpression x, TripleExpression y) {
        super(x, y);
    }
    protected void check(int x, int y) throws OverflowException {
        if ( x == Integer.MIN_VALUE && y == -1) {
            throw new OverflowException();
        }
    }
    protected int count(int x, int y) throws OverflowException {
        check(x, y);
        return x / y;
    }
}
package expression.exceptions;

public class CheckedAdd extends AbstractOperation {
    public CheckedAdd(TripleExpression x, TripleExpression y) {
        super(x, y);
    }
    protected void check(int x, int y) throws OverflowException {
        if ((x > 0 && Integer.MAX_VALUE - x < y) || (x < 0 && Integer.MIN_VALUE - x  > y)) {
            throw new OverflowException();
        }
    }
    protected int count(int x, int y) throws OverflowException {
        check(x, y);
        return x + y;
    }
}

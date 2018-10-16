package expression.exceptions;

public class CheckedSubtract extends AbstractOperation {
    public CheckedSubtract(TripleExpression x, TripleExpression y) {
        super(x, y);
    }
    protected void check(int x, int y) throws OverflowException {
        if ((x >= 0 && y < 0 && x - Integer.MAX_VALUE > y) || (x <= 0 && y > 0 && Integer.MIN_VALUE - x > -y)) {
            throw new OverflowException();
        }
    }
    protected int count(int x, int y) throws OverflowException {
        check(x ,y);
        return x - y;
    }
}
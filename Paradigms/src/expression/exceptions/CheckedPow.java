package expression.exceptions;

public class CheckedPow extends AbstractUnaryOperation {
    public CheckedPow(final TripleExpression x) {
        super(x);
    }
    protected void check(int x) throws Exception {
        if (x < 0) {
            throw new BadOperationException("Pow is negative");
        }
        if (x >= 10) {
            throw new OverflowException();
        }
    }

    protected int count(int x) throws Exception {
        check(x);
        if (x < 0) {
            return 0;
        } else if ( x == 1) {
            return 10;
        } else {
            int n = 1;
            int res = 10;
            while(n <= x) {
                res *= 10;
                ++n;
            }
            if (n == 10) {
                return 1000000000;
            } else {
                return res / 10;
            }
        }
    }
}
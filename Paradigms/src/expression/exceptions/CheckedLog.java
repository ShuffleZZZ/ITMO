package expression.exceptions;

import expression.parser.Const;

public class CheckedLog extends AbstractUnaryOperation {
    public CheckedLog(TripleExpression x) {
        super(x);
    }
    protected void check(int x) throws Exception {
        if (x <= 0) {
            throw new BadOperationException("Log from negative");
        }
    }

    protected int count(int x) throws Exception {
        check(x);
        int l = 0;
        int r = 31;
        while (r - l > 1) {
            int m = (l + r) / 2;
            try {
                int res = new CheckedPow(new Const(m)).evaluate(0, 0, 0);
                if (res <= x) {
                    l = m;
                } else {
                    r = m;
                }
            } catch (Exception e) {
                r = m;
            }
        }
        return l;
    }
}
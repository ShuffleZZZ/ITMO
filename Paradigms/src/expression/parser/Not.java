package expression.parser;

import expression.exceptions.TripleExpression;

public class Not extends AbstractUnaryOperation {

    public Not(TripleExpression x) {
        super(x);
    }

    protected int count(final int x) {
        return -x;
    }
}
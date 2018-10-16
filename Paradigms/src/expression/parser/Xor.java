package expression.parser;

import expression.exceptions.TripleExpression;

public class Xor extends AbstractOperation {
    public Xor(TripleExpression x, TripleExpression y) {
        super(x, y);
    }

    protected int count(int x, int y) {
        return x ^ y;
    }
}
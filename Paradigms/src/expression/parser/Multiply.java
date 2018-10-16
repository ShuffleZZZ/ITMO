package expression.parser;

import expression.exceptions.TripleExpression;

public class Multiply extends AbstractOperation {
    public Multiply(TripleExpression x, TripleExpression y) {
        super(x, y);
    }
    protected int count(int x, int y) {
        return x * y;
    }
}

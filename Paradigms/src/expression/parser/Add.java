package expression.parser;

import expression.exceptions.TripleExpression;

public class Add extends AbstractOperation {
    public Add(TripleExpression x, TripleExpression y) {
        super(x, y);
    }
    protected int count(int x, int y) {
        return x + y;
    }
}

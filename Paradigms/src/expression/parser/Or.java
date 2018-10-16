package expression.parser;

import expression.exceptions.TripleExpression;

public class Or extends AbstractOperation {
    public Or(TripleExpression x, TripleExpression y) {
        super(x, y);
    }

    protected int count(int x, int y) {
        return x | y;
    }
}
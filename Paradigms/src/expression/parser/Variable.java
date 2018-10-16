package expression.parser;

import expression.exceptions.TripleExpression;

public class Variable implements TripleExpression {
    private char s;
    public Variable(char x) {
        s = x;
    }
    public Variable(String x) { s = x.charAt(0);}
    public int evaluate(int x, int y, int z) {
        switch (s) {
            case 'x':
                return x;
            case 'y':
                return y;
            case 'z':
                return z;
        }
        return 0;
    }
}
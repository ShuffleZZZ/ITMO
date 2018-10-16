package expression.parser;

import expression.exceptions.*;

public class ExpressionParser implements Parser {
    private Tokenizer tokenizer;

    private TripleExpression unary() throws Exception {
        TripleExpression res;
        switch (tokenizer.getNextToken()) {
            case NUMBER:
                res = new Const(tokenizer.value);
                tokenizer.getNextToken();
                break;
            case VARIABLE:
                res = new Variable(tokenizer.variable);
                tokenizer.getNextToken();
                break;
            case MINUS:
                res = new CheckedNegate(unary());
                break;
            case LOG:
                res = new CheckedLog(unary());
                break;
            case POW:
                res = new CheckedPow(unary());
                break;
            case OPEN:
                int pos = tokenizer.cur;
                res = addSub();
                if (tokenizer.curToken != Tokenizer.Token.CLOSE) {
                    throw new BraceException(tokenizer.in, pos - 1);
                }
                tokenizer.getNextToken();
                break;
            default:
                throw new Exception("Incorrect input" + "\n" + tokenizer.in);
        }
        return res;
    }


    private TripleExpression mulDiv() throws Exception {
        TripleExpression res = unary();
        while (true) {
            switch (tokenizer.curToken) {
                case MUL:
                    res = new CheckedMultiply(res, unary());
                    break;
                case DIV:
                    res = new CheckedDivide(res, unary());
                    break;
                default:
                    return res;
            }
        }
    }

    private TripleExpression addSub() throws Exception {
        TripleExpression res = mulDiv();
        while (true) {
            switch (tokenizer.curToken) {
                case ADD:
                    res = new CheckedAdd(res, mulDiv());
                    break;
                case SUB:
                    res = new CheckedSubtract(res, mulDiv());
                    break;
                default:
                    return res;
            }
        }
    }

    public TripleExpression parse(String s) throws Exception {
        tokenizer = new Tokenizer(s);
        return addSub();
    }
}
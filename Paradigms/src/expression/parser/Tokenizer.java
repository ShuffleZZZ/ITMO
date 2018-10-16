package expression.parser;

import expression.exceptions.*;

public class Tokenizer {
    enum Token {NUMBER, VARIABLE, MINUS, ADD, SUB, DIV, MUL, OPEN, CLOSE, END, BEGIN, OR, AND, XOR, POW, LOG}
    protected String in;
    protected int cur;
    protected int value;
    protected char variable;
    protected Token curToken;
    private int balance;

    public Tokenizer(String s) {
        in = s;
        cur = 0;
        curToken = Token.BEGIN;
        balance = 0;
    }

    public Token getNextToken() throws Exception {
        nextToken();
        return curToken;
    }

    private void Spaces() {
        while (cur < in.length() && Character.isWhitespace(in.charAt(cur))) {
            ++cur;
        }
    }

    private void checkForOperand(int cur) throws NoOperandException {
        if (curToken != Token.NUMBER && curToken != Token.VARIABLE && curToken != Token.CLOSE && curToken != Token.END) {
            throw new NoOperandException(in, cur);
        }
    }

    private void checkForOperation(int cur) throws NoOperationException {
        if (curToken == Token.CLOSE || curToken == Token.VARIABLE || curToken == Token.NUMBER) {
            throw new NoOperationException(in, cur);
        }
    }

    private String getNumber() {
        int l = cur;
        while (cur < in.length() && Character.isDigit(in.charAt(cur))) {
            ++cur;
        }
        int r = cur;
        cur--;
        return in.substring(l, r);
    }

    private String getString() throws BadSymbolException {
        if (!Character.isLetter(in.charAt(cur))) {
            throw new BadSymbolException(in, cur, in.substring(cur, cur + 1));
        }
        int l = cur;
        while (cur < in.length() && Character.isLetterOrDigit(in.charAt(cur))) {
            ++cur;
        }
        int r = cur;
        cur--;
        return in.substring(l, r);
    }

    private void nextToken() throws Exception {
        Spaces();
        if (cur >= in.length()) {
            checkForOperand(cur);
            curToken = Token.END;
            return;
        }
        switch (in.charAt(cur)) {
            case '-':
                if (curToken == Token.NUMBER || curToken == Token.VARIABLE || curToken == Token.CLOSE) {
                    curToken = Token.SUB;
                } else {
                    if (cur + 1 >= in.length()) {
                        throw new NoOperandException(in, cur + 1);
                    }
                    if (Character.isDigit(in.charAt(cur + 1))) {
                        ++cur;
                        String temp = getNumber();
                        try {
                            value = Integer.parseInt("-" + temp);
                        } catch (NumberFormatException NFE) {
                            throw new BadConstantException("-" + temp, in, cur - temp.length());
                        }
                        curToken = Token.NUMBER;
                    } else {
                        curToken = Token.MINUS;
                    }
                }
                break;
            case '+':
                checkForOperand(cur);
                curToken = Token.ADD;
                break;
            case '^':
                curToken = Token.XOR;
                break;
            case '&':
                curToken = Token.AND;
                break;
            case '|':
                curToken = Token.OR;
                break;
            case '*':
                checkForOperand(cur);
                curToken = Token.MUL;
                break;
            case '/':
                checkForOperand(cur);
                curToken = Token.DIV;
                break;
            case '(':
                checkForOperation(cur);
                ++balance;
                curToken = Token.OPEN;
                break;
            case ')':
                if (curToken == Token.OPEN || curToken == Token.SUB) {
                    throw new NoOperandException(in, cur);
                }
                balance--;
                if (balance < 0) {
                    throw new BraceException(in, cur);
                }
                curToken = Token.CLOSE;
                break;
            default:
                if (Character.isDigit(in.charAt(cur))) {
                    checkForOperation(cur);
                    String temp = getNumber();
                    try { value = Integer.parseInt(temp);
                    } catch (NumberFormatException NFE) {
                        throw new BadConstantException(temp, in, cur - temp.length() + 1);
                    }
                    curToken = Token.NUMBER;
                } else {
                    String curInd = getString();
                    if (!curInd.equals("x") && !curInd.equals("y") && !curInd.equals("z") && !curInd.equals("log10") && !curInd.equals("pow10")) {
                        throw new BadSymbolException(in, cur, curInd);
                    }
                    checkForOperation(cur - curInd.length() + 1);
                    if (curInd.equals("x") || curInd.equals("y") || curInd.equals("z")) {
                        curToken = Token.VARIABLE;
                        variable = curInd.charAt(0);
                    } else if (curInd.equals("pow10")) {
                        curToken = Token.POW;
                    } else if (curInd.equals("log10")) {
                        curToken = Token.LOG;
                    }
                }
        }
        ++cur;
    }
}
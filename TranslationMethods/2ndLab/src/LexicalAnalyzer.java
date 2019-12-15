class LexicalAnalyzer {

    private final String input;
    private int curPos;
    private Token curToken;
    private char curChar;
    private String nameTokenString;

    LexicalAnalyzer(String input) {
        this.input = input + "$";
        curPos = 0;

        nextChar();
    }

    private void nextChar() {
        curChar = input.charAt(curPos++);
    }

    String getName() {
        return curToken == Token.NAME ? nameTokenString : "";
    }

    Token curToken() {
        return curToken;
    }

    private boolean isBlank(char c) {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t';
    }

    private boolean isNameChar(char c) {
        return !isBlank(c) && c != ',' && c != ';' && c != '*' && c != '&';
    }

    private boolean next() {
        return curPos < input.length();
    }

    void nextToken() {
        while (next() && isBlank(curChar)) {
            nextChar();
        }

        switch (curChar) {
            case '&':
                curToken = Token.AMP;
                nextChar();
                break;
            case '*':
                curToken = Token.POINTER;
                nextChar();
                break;
            case ';':
                curToken = Token.SEMICOLON;
                nextChar();
                break;
            case ',':
                curToken = Token.COMMA;
                nextChar();
                break;
            case '$':
                curToken = Token.END;
                break;
            default:
                nameTokenString = "";
                while (next() && isNameChar(curChar)) {
                    nameTokenString += curChar;
                    nextChar();
                }
                curToken = Token.NAME;
                break;
        }
    }
}
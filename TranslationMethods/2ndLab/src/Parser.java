import java.util.Map;

class Parser {
    private LexicalAnalyzer lex;
    private final Map<Character, String> termToString = Map.of('S', "DECL",
            'C', "NEXT",
            'V', "MOD",
            'B', "VAR");

    Tree parse(String input) {
        lex = new LexicalAnalyzer(input);
        lex.nextToken();
        return S();
    }

    private Tree S() {
        switch (lex.curToken()) {
            case NAME:
                //a
                Tree a = new Tree(lex.getName());
                lex.nextToken();
                //V
                Tree v = V();
                //C
                Tree c = C();
                //S
                Tree s = S();
                return new Tree(termToString.get('S'), a, v, c, s);
            case END:
                //Epsilon
                return new Tree(termToString.get('S'), new Tree("$"));
            default:
                throw new AssertionError(lex.curToken() + " can't be first Token of " +
                                            termToString.get('S'));
        }
    }

    private Tree V() {
        switch (lex.curToken()) {
            case POINTER:
                //*
                lex.nextToken();
                //V
                Tree v = V();
                return new Tree(termToString.get('V'), new Tree("*"), v);
            case AMP:
                //&
                lex.nextToken();
                //B
                return new Tree(termToString.get('V'), new Tree("&"), B());
            case NAME:
                //B
                return new Tree(termToString.get('V'), B());
            default:
                throw new AssertionError(lex.curToken() + " can't be first Token of " +
                                            termToString.get('V'));
        }
    }

    private Tree B() {
        switch (lex.curToken()) {
            case NAME:
                //a
                String name = lex.getName();
                lex.nextToken();
                return new Tree(termToString.get('B'), new Tree(name));
            default:
                throw new AssertionError(lex.curToken() + " can't be first Token of " +
                        termToString.get('B'));
        }
    }

    private Tree C() {
        switch (lex.curToken()) {
            case COMMA:
                //,
                lex.nextToken();
                //V
                Tree v = V();
                //C
                Tree c = C();
                return new Tree(termToString.get('C'), new Tree(","), v, c);
            case SEMICOLON:
                //;
                lex.nextToken();
                return new Tree(termToString.get('C'), new Tree(";"));
            default:
                throw new AssertionError(lex.curToken() + " can't be first Token of " +
                                            termToString.get('C'));
        }
    }
}
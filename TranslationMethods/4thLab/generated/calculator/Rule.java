package calculator;
public enum Rule {
    OPEN(true),
    v(false),
    s(false),
    t(false),
    OR(true),
    EPSILON(true),
    MULTIPLY(true),
    x(false),
    w(false),
    y(false),
    PLUS(true),
    q(false),
    WHITESPACES(true),
    AND(true),
    NOT(true),
    MINUS(true),
    POW(true),
    e(false),
    f(false),
    DIVIDE(true),
    j(false),
    NUMBER(true),
    d(false),
    k(false),
    g(false),
    h(false),
    a(false),
    XOR(true),
    start(false),
    CLOSE(true),
    EOF(true),
    DUMMY(true);
                    
    private final boolean isTerminal;
    Rule(final boolean isTerminal) {
        this.isTerminal = isTerminal;
    }
    public boolean isTerminal() {
        return isTerminal;
    }
}
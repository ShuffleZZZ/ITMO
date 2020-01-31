package cdeclaration;
public enum Rule {
    name(false),
    type(false),
    EPSILON(true),
    WHITESPACE(true),
    POINTER(true),
    SEMICOLON(true),
    IDENTIFIER(true),
    COMMA(true),
    nextVar(false),
    vars(false),
    declaration(false),
    variable(false),
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
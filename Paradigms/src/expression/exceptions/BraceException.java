package expression.exceptions;

public class BraceException extends Exception {
    public BraceException(String s, int ind) {
        super("Brace balance is broken at: " + ind + "\n" + s.substring(0, ind) + "->" + s.substring(ind));
    }
}
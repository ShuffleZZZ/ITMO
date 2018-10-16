package expression.exceptions;

public class BadSymbolException extends Exception {
    public BadSymbolException(String s, int ind, String bad) {
        super("Bad symbol " + bad + " at: " + (ind - bad.length() + 1) + "\n" + s.substring(0, ind - bad.length() + 1) + "->" + s.substring(ind - bad.length() + 1));
    }
}
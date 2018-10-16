package expression.exceptions;

public class BadConstantException extends Exception {
    public BadConstantException(String reason, String s, int ind) {
        super(reason + " is bad at: " + ind + "\n" + s.substring(0, ind) + "->" + s.substring(ind));
    }
}
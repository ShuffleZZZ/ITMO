package expression.exceptions;

public class NoOperationException extends Exception {
    public NoOperationException(String s, int ind) {
        super("No abstractOper at: " + ind + "\n" + s.substring(0, ind) + "⬤" + s.substring(ind));
    }
}
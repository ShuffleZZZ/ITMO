package expression.exceptions;

public class BadOperationException extends Exception {
    public BadOperationException(final String message) {
        super("Illegar abstractOper: " + message);
    }
}
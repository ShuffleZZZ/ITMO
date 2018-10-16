package expression.exceptions;

public class NoOperandException extends Exception {
    public NoOperandException(String s, int ind) {
        super("No operand at: " + ind + "\n" + s.substring(0, ind) + "⬤" + s.substring(ind));
    }
}
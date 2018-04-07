/** Prints greeting on the console. */
public class ConsoleGreeter {
    private String format;

    public ConsoleGreeter(String format) {
        this.format = format;
    }

    public void greet(String name) {
        System.out.printf(format, name);
    }
}

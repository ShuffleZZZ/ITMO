/** Prints <tt>Hello, &lt;user&gt;!</tt> on the console. */
public class HelloWorld2 {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java HelloWorld2 <user name>");
            return;
        }
        System.out.printf("Hello, %s!", args[0]);
    }
}

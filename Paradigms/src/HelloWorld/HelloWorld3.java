/** Prints <tt>Hello, &lt;user 1&gt;, &lt;user 2&gt;, ...</tt> on the console. */
public class HelloWorld3 {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java HelloWorld3 <user 1> <user 2> ...");
        }
        System.out.printf("Hello");
        for (int i = 0; i < args.length; i++) {
            System.out.printf(", %s", args[i]);
        }
        System.out.println("!");
    }
}

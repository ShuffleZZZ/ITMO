/** Prints <tt>Hello</tt> or <tt>Hi</tt> for users. */
public class HelloWorld4 {
    private static void printUsage() {
        System.out.println("Usage: java HelloWorld4 [hello|hi] <user 1> <user 2> ...");
    }

    public static void main(String[] args) {
        if (args.length <= 1) {
            printUsage();
            return;
        }

        ConsoleGreeter greeter;
        if ("hello".equals(args[0])) {
            greeter = new ConsoleGreeter("Hello, %s!\n");
        } else if ("hi".equals(args[0])) {
            greeter = new ConsoleGreeter("Hi, %s\n");
        } else {
            printUsage();
            return;
        }

        for (int i = 1; i < args.length; i++) {
            greeter.greet(args[i]);
        }
    }
}

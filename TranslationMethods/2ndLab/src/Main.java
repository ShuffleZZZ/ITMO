import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.NoSuchElementException;

public class Main {

    public static void main(String[] args) throws IOException {
        final int TESTS_LEFT_BOARDER = 0, TESTS_RIGHT_BOARDER = 29;

        for (int i = TESTS_LEFT_BOARDER; i <= TESTS_RIGHT_BOARDER; i++) {
            String s = Files.readString(Paths.get("tests/input" + i + ".in"));
            try {
                Tree tree = new Parser().parse(s);
                tree.print(i);
                System.out.println("Test" + i + " is correct: " + s);
            } catch (AssertionError e) {
                System.out.println("Exception in test" + i + " \"" + s + "\": " + e.getMessage());
            } catch (NoSuchElementException e) {
                break;
            }
        }
    }
}
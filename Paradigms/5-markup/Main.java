import java.util.Arrays;
import java.util.Collections;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Main {
    public static void main(final String[] args) {
        final Paragraph paragraph = new Paragraph(Arrays.asList(
                new Emphasis(Collections.singletonList(new TextFragment("Hello"))),
                new TextFragment(", "),
                new Strong(Collections.singletonList(new TextFragment("World")))
        ));

        method(paragraph);
        converter(paragraph);
        visitor(paragraph);
    }

    private static void method(final Paragraph paragraph) {
        part("method-based converters");
        {
            final StringBuilder sb = new StringBuilder();
            paragraph.toText(sb);
            System.out.println(sb);
        }

        {
            final StringBuilder sb = new StringBuilder();
            paragraph.toMarkdown(sb);
            System.out.println(sb);
        }

        {
            final StringBuilder sb = new StringBuilder();
            paragraph.toHtml(sb);
            System.out.println(sb);
        }
    }

    private static void converter(final Paragraph paragraph) {
        part("instanceof-based converters");
        for (final FragmentToStringConverter converter : Arrays.asList(
                FragmentToStringConverter.TO_TEXT,
                FragmentToStringConverter.TO_MARKDOWN,
                FragmentToStringConverter.TO_HTML
        )) {
            final StringBuilder sb = new StringBuilder();
            converter.convert(paragraph, sb);
            System.out.println(sb);
        }
    }

    private static void visitor(final Paragraph paragraph) {
        part("Visitor-based converters");
        for (final FragmentToStringVisitor visitor : Arrays.asList(
                FragmentToStringVisitor.TO_TEXT,
                FragmentToStringVisitor.TO_MARKDOWN,
                FragmentToStringVisitor.TO_HTML
        )) {
            final StringBuilder sb = new StringBuilder();
            paragraph.toString(visitor, sb);
            System.out.println(sb);
        }
    }

    private static void part(final String name) {
        System.out.println("\n=== " + name);
    }
}

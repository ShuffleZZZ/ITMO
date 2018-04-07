/**
 * <code>Instanceof</code>-based fragment to string converted.
 * Never write code like this.
 * Look at {@link FragmentToStringVisitor} for correct implementation.
 *
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface FragmentToStringConverter {
    void convert(Fragment fragment, StringBuilder sb);

    default void convertChildren(final CompositeFragment fragment, final StringBuilder sb) {
        for (final Fragment child : fragment.getChildren()) {
            convert(child, sb);
        }
    }

    FragmentToStringConverter TO_TEXT = new FragmentToStringConverter() {
        @Override
        public void convert(final Fragment fragment, final StringBuilder sb) {
            if (fragment instanceof TextFragment) {
                sb.append(((TextFragment) fragment).getText());
            } else if (fragment instanceof Strong) {
                convertChildren((Strong) fragment, sb);
            } else if (fragment instanceof Emphasis) {
                convertChildren((Emphasis) fragment, sb);
            } else if (fragment instanceof Paragraph) {
                convertChildren((Paragraph) fragment, sb);
            }
        }
    };

    FragmentToStringConverter TO_MARKDOWN = new FragmentToStringConverter() {
        private void toMarkdown(final String markup, final CompositeFragment fragment, final StringBuilder sb) {
            sb.append(markup);
            convertChildren(fragment, sb);
            sb.append(markup);
        }

        @Override
        public void convert(final Fragment fragment, final StringBuilder sb) {
            if (fragment instanceof TextFragment) {
                sb.append(((TextFragment) fragment).getText());
            } else if (fragment instanceof Strong) {
                toMarkdown("**", (Strong) fragment, sb);
            } else if (fragment instanceof Emphasis) {
                toMarkdown("*", (Emphasis) fragment, sb);
            } else if (fragment instanceof Paragraph) {
                toMarkdown("", (Paragraph) fragment, sb);
                sb.append("\n");
            }
        }
    };

    FragmentToStringConverter TO_HTML = new FragmentToStringConverter() {
        private void toHtml(final String tag, final CompositeFragment fragment, final StringBuilder sb) {
            sb.append("<").append(tag).append(">");
            convertChildren(fragment, sb);
            sb.append("</").append(tag).append(">");
        }

        @Override
        public void convert(final Fragment fragment, final StringBuilder sb) {
            if (fragment instanceof TextFragment) {
                sb.append(((TextFragment) fragment).getText());
            } else if (fragment instanceof Strong) {
                toHtml("strong", (Strong) fragment, sb);
            } else if (fragment instanceof Emphasis) {
                toHtml("em", (Emphasis) fragment, sb);
            } else if (fragment instanceof Paragraph) {
                toHtml("p", (Paragraph) fragment, sb);
            }
        }
    };
}

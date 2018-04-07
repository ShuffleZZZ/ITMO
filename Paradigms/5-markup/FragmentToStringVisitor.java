/** Main {@link Fragment} visitor. */
public interface FragmentToStringVisitor {
    void visitText(TextFragment fragment, StringBuilder sb);
    void visitEmphasis(Emphasis fragment, StringBuilder sb);
    void visitBold(Strong fragment, StringBuilder sb);
    void visitParagraph(Paragraph fragment, StringBuilder sb);

    default void visitChildren(final CompositeFragment fragment, final StringBuilder sb) {
        for (final Fragment child : fragment.getChildren()) {
            child.toString(this, sb);
        }
    }

    FragmentToStringVisitor TO_TEXT = new FragmentToStringVisitor() {
        @Override
        public void visitText(final TextFragment fragment, final StringBuilder sb) {
            sb.append(fragment.getText());
        }

        @Override
        public void visitEmphasis(final Emphasis fragment, final StringBuilder sb) {
            visitChildren(fragment, sb);
        }

        @Override
        public void visitBold(final Strong fragment, final StringBuilder sb) {
            visitChildren(fragment, sb);
        }

        @Override
        public void visitParagraph(final Paragraph fragment, final StringBuilder sb) {
            visitChildren(fragment, sb);
        }
    };

    FragmentToStringVisitor TO_MARKDOWN = new FragmentToStringVisitor() {
        void toMarkdown(final String markup, final CompositeFragment fragment, final StringBuilder sb) {
            sb.append(markup);
            visitChildren(fragment, sb);
            sb.append(markup);
        }

        @Override
        public void visitText(final TextFragment fragment, final StringBuilder sb) {
            sb.append(fragment.getText());
        }

        @Override
        public void visitEmphasis(final Emphasis fragment, final StringBuilder sb) {
            toMarkdown("*", fragment, sb);
        }

        @Override
        public void visitBold(final Strong fragment, final StringBuilder sb) {
            toMarkdown("**", fragment, sb);
        }

        @Override
        public void visitParagraph(final Paragraph fragment, final StringBuilder sb) {
            toMarkdown("", fragment, sb);
            sb.append("\n");
        }
    };


    FragmentToStringVisitor TO_HTML = new FragmentToStringVisitor() {
        void toHtml(final String tag, final CompositeFragment fragment, final StringBuilder sb) {
            sb.append("<").append(tag).append(">");
            visitChildren(fragment, sb);
            sb.append("</").append(tag).append(">");
        }

        @Override
        public void visitText(final TextFragment fragment, final StringBuilder sb) {
            sb.append(fragment.getText());
        }

        @Override
        public void visitEmphasis(final Emphasis fragment, final StringBuilder sb) {
            toHtml("em", fragment, sb);
        }

        @Override
        public void visitBold(final Strong fragment, final StringBuilder sb) {
            toHtml("strong", fragment, sb);
        }

        @Override
        public void visitParagraph(final Paragraph fragment, final StringBuilder sb) {
            toHtml("p", fragment, sb);
        }
    };
}

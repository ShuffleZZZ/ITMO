/** Text node of the marked up text tree. */
public class TextFragment implements Fragment {
    private final String text;

    public TextFragment(final String text) {
        this.text = text;
    }

    public String getText() {
        return text;
    }

    @Override
    public void toText(final StringBuilder sb) {
        sb.append(text);
    }

    @Override
    public void toMarkdown(final StringBuilder sb) {
        sb.append(text);
    }

    @Override
    public void toHtml(final StringBuilder sb) {
        sb.append(text);
    }

    @Override
    public void toString(final FragmentToStringVisitor visitor, final StringBuilder sb) {
        visitor.visitText(this, sb);
    }
}

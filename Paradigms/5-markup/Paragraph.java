import java.util.List;

/** Text paragraph. */
public class Paragraph extends CompositeFragment {
    public Paragraph(final List<Fragment> children) {
        super(children);
    }

    @Override
    public void toMarkdown(final StringBuilder sb) {
        toMarkdown("", sb);
        sb.append("\n");
    }

    @Override
    public void toHtml(final StringBuilder sb) {
        toHtml("p", sb);
    }

    @Override
    public void toString(final FragmentToStringVisitor visitor, final StringBuilder sb) {
        visitor.visitParagraph(this, sb);
    }
}

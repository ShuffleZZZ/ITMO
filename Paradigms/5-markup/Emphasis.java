import java.util.List;

/** Emphasised fragment. */
public class Emphasis extends CompositeFragment {
    public Emphasis(final List<Fragment> children) {
        super(children);
    }

    @Override
    public void toMarkdown(final StringBuilder sb) {
        toMarkdown("*", sb);
    }

    @Override
    public void toHtml(final StringBuilder sb) {
        toHtml("em", sb);
    }

    @Override
    public void toString(final FragmentToStringVisitor visitor, final StringBuilder sb) {
        visitor.visitEmphasis(this, sb);
    }
}

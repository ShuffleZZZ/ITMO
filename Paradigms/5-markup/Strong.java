import java.util.List;

/** Strong emphasised fragment. */
public class Strong extends CompositeFragment {
    public Strong(final List<Fragment> children) {
        super(children);
    }


    @Override
    public void toMarkdown(final StringBuilder sb) {
        toMarkdown("**", sb);
    }

    @Override
    public void toHtml(final StringBuilder sb) {
        toHtml("strong", sb);
    }

    @Override
    public void toString(final FragmentToStringVisitor visitor, final StringBuilder sb) {
        visitor.visitBold(this, sb);
    }
}

import java.util.List;

/** Main fragment containing other fragments. */
public abstract class CompositeFragment implements Fragment {
    protected final List<Fragment> children;

    public CompositeFragment(final List<Fragment> children) {
        this.children = children;
    }

    public List<Fragment> getChildren() {
        return children;
    }

    @Override
    public void toText(final StringBuilder sb) {
        for (final Fragment child : children) {
            child.toText(sb);
        }
    }

    protected void toMarkdown(final String markup, final StringBuilder sb) {
        sb.append(markup);
        for (final Fragment child : children) {
            child.toMarkdown(sb);
        }
        sb.append(markup);
    }


    protected void toHtml(final String tag, final StringBuilder sb) {
        sb.append("<").append(tag).append(">");
        for (final Fragment child : children) {
            child.toHtml(sb);
        }
        sb.append("</").append(tag).append(">");
    }
}

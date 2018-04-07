/**
 * Node of the marked up text tree.
 */
public interface Fragment {
    void toText(StringBuilder sb);
    void toMarkdown(StringBuilder sb);
    void toHtml(StringBuilder sb);

    void toString(FragmentToStringVisitor visitor, StringBuilder sb);
}

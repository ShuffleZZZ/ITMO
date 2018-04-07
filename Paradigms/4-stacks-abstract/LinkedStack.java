public class LinkedStack extends AbstractStack implements Copiable {
    private Node head;

    protected void pushImpl(Object element) {
        head = new Node(element, head);
    }

    protected void remove() {
        head = head.next;
    }

    protected Object peekImpl() {
        return head.value;
    }

    public LinkedStack makeCopy() {
        final LinkedStack copy = new LinkedStack();
        copy.size = size;
        copy.head = head;
        return copy;
    }

    private class Node {
        private Object value;
        private Node next;

        public Node(Object value, Node next) {
            assert value != null;

            this.value = value;
            this.next = next;
        }
    }
}

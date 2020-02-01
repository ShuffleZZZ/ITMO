public class Solution implements AtomicCounter {
    private final Node root = new Node();
    private final ThreadLocal<Node> last = ThreadLocal.withInitial(() -> root);

    public int getAndAdd(int x) {
        Node node;
        int old;

        do {
            old = last.get().val;
            node = new Node(old + x);
            last.set(last.get().next.decide(node));
        } while (node != last.get());

        return old;
    }

    private static class Node {
        private final int val;
        private final Consensus<Node> next;

        private Node() {
            this(0);
        }

        private Node(int x) {
            this.val = x;
            this.next = new Consensus<>();
        }
    }
}

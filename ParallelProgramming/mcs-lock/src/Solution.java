import java.util.concurrent.atomic.*;

public class Solution implements Lock<Solution.Node> {
    private final Environment env;
    private final AtomicReference<Node> tail;

    public Solution(Environment env) {
        this.env = env;
        this.tail = new AtomicReference<>();
    }

    @Override
    public Node lock() {
        Node my = new Node();
        my.locked.set(true);
        Node pred = tail.getAndSet(my);

        if (pred != null) {
            pred.next.set(my);

            while (my.locked.get()) {
                env.park();
            }
        }

        return my;
    }

    @Override
    public void unlock(Node node) {
        if (node.next.get() == null) {

            if (tail.compareAndSet(node, null)) {
                return;
            } else {

                while (node.next.get() == null) {
                    // empty.
                }
            }
        }

        node.next.get().locked.set(false);
        env.unpark(node.next.get().thread);
    }

    static class Node {
        final Thread thread = Thread.currentThread();
        final AtomicReference<Boolean> locked = new AtomicReference<>(false);
        final AtomicReference<Node> next = new AtomicReference<>();
    }
}

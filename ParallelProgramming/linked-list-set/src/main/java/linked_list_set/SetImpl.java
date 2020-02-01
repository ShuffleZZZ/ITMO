package linked_list_set;

import kotlinx.atomicfu.AtomicRef;

public class SetImpl implements Set {
    private class Node {
        AtomicRef<Node> next;
        int x;

        Node() {
            // empty.
        }

        Node(int x, Node next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }

        Node nextNode() {
            Node curNext = next.getValue();
            if (curNext instanceof Removed) {
                return ((Removed) curNext).next;
            }
            return curNext;
        }
    }

    private class Window {
        Node cur, next;
    }

    private class Removed extends Node {
        final Node next;

        Removed(Node next) {
            this.next = next;
        }
    }

    private final Node head = new Node(Integer.MIN_VALUE, new Node(Integer.MAX_VALUE, null));

    /**
     * Returns the {@link Window}, where cur.x < x <= next.x
     */
    private Window findWindow(int x) {
        while (true) {
            Window w = new Window();
            w.cur = head;
            w.next = w.cur.nextNode();
            Node nextNext;
            while (w.next.x < x) {
                nextNext = w.next.next.getValue();
                if (nextNext instanceof Removed) {
                    if (!w.cur.next.compareAndSet(w.next, ((Removed) nextNext).next)) {
                        w.cur = head;
                        w.next = w.cur.nextNode();
                    } else {
                        w.next = ((Removed) nextNext).next;
                    }
                } else {
                    w.cur = w.next;
                    w.next = w.cur.nextNode();
                }
            }
            nextNext = w.next.next.getValue();
            if (nextNext instanceof Removed) {
                w.cur.next.compareAndSet(w.next, ((Removed) nextNext).next);
            } else {
                return w;
            }
        }
    }

    @Override
    public boolean add(int x) {
        while(true) {
            Window w = findWindow(x);
            if (w.next.x == x) {
                return false;
            }
            Node node = new Node(x, w.next);
            if (w.cur.next.compareAndSet(w.next, node)) {
                return true;
            }
        }
    }

    @Override
    public boolean remove(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.next.x != x) {
                return false;
            }
            Node nextNext = w.next.nextNode();
            Node nextRemoved = new Removed(nextNext);
            if (w.next.next.compareAndSet(nextNext, nextRemoved)) {
                w.cur.next.compareAndSet(w.next, nextNext);
                return true;
            }
        }
    }

    @Override
    public boolean contains(int x) {
        Window w = findWindow(x);
        return w.next.x == x;
    }
}
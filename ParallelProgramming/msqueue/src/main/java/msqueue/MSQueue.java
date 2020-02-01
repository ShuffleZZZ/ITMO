package msqueue;

import kotlinx.atomicfu.AtomicRef;

public class MSQueue implements Queue {
    private AtomicRef<Node> head;
    private AtomicRef<Node> tail;

    public MSQueue() {
        Node dummy = new Node(0);
        this.head = new AtomicRef<>(dummy);
        this.tail = new AtomicRef<>(dummy);
    }

    @Override
    public void enqueue(int x) {
        Node newTail = new Node(x);
        while (true) {
            Node curTail = tail.getValue();
            if (curTail.next.compareAndSet(null, newTail)) {
                //tail.compareAndSet(curTail, newTail);
                tail.setValue(newTail);
                return;
            } else {
                //tail.compareAndSet(curTail, curTail.next.getValue());
                tail.setValue(curTail.next.getValue());
            }
        }
    }

    @Override
    public int dequeue() {
        //noinspection Duplicates
        while (true) {
            Node curHead = head.getValue();
            Node next = curHead.next.getValue();
            if (head.getValue() == curHead) {
                if (next == null) {
                    return Integer.MIN_VALUE;
                } else {
                    if (curHead == tail.getValue()) {
                        tail.setValue(next);
                    }
                    if (head.compareAndSet(curHead, next)) {
                        return next.x;
                    }
                }
            }
        }
    }

    @Override
    public int peek() {
        //noinspection Duplicates
        while (true) {
            Node curHead = head.getValue();
            Node next = curHead.next.getValue();
            if (head.getValue() == curHead) {
                if (next == null) {
                    return Integer.MIN_VALUE;
                } else {
                    if (curHead == tail.getValue()) {
                        tail.setValue(next);
                    }
                    if (head.getValue() == curHead) {
                        return next.x;
                    }
                }
            }
        }
    }

    private static class Node {
        final int x;
        final AtomicRef<Node> next;

        Node(int x) {
            this.x = x;
            this.next = new AtomicRef<>(null);
        }
    }
}
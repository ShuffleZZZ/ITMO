package faaqueue;

import kotlinx.atomicfu.*;

import static faaqueue.FAAQueue.Node.NODE_SIZE;


public class FAAQueue<T> implements Queue<T> {
    private static final Object DONE = new Object();

    private AtomicRef<Node> head;
    private AtomicRef<Node> tail;

    public FAAQueue() {
        Node firstNode = new Node();
        head = new AtomicRef<>(firstNode);
        tail = new AtomicRef<>(firstNode);
    }

    @Override
    public void enqueue(T x) {
        while (true) {
            Node tail = this.tail.getValue();
            Node tailNext = tail.next.getValue();
            if (tailNext != null) {
                this.tail.compareAndSet(tail, tailNext);
                continue;
            }
            int enqIdx = tail.enqIdx.getAndIncrement();
            if (enqIdx >= NODE_SIZE) {
                if (tail == this.tail.getValue()) {
                    if (this.tail.getValue().next.compareAndSet(null, new Node(x)))
                        break;
                }
            } else {
                if (tail.data.get(enqIdx).compareAndSet(null, x))
                    return;
            }
        }
    }

    @Override
    public T dequeue() {
        while (true) {
            Node head = this.head.getValue();
            if (head.isEmpty()) {
                Node headNext = head.next.getValue();
                if (headNext == null) return null;
                this.head.compareAndSet(head, headNext);
                continue;
            }
            int deqIdx = head.deqIdx.getAndIncrement();
            if (deqIdx >= NODE_SIZE) continue;
            Object res = head.data.get(deqIdx).getAndSet(DONE);
            if (res != null) return (T) res;
        }
    }

    static class Node {
        static final int NODE_SIZE = 2;

        private AtomicRef<Node> next = new AtomicRef<>(null);
        private AtomicInt enqIdx = new AtomicInt(0);
        private AtomicInt deqIdx = new AtomicInt(0);
        private final AtomicArray<Object> data = new AtomicArray<>(NODE_SIZE);

        Node() {}

        Node(Object x) {
            this.enqIdx.incrementAndGet();
            this.data.get(0).setValue(x);
        }

        private boolean isEmpty() {
            return this.deqIdx.getValue() >= this.enqIdx.getValue();
        }
    }
}
package queue;

public class LinkedQueue extends queue.AbstractQueue {
    private Node tail = null;
    private Node head = null;

    protected void enqueueImpl(Object element) {
        Node temp = new Node(element, null);
        if (isEmpty()) {
            tail = temp;
        } else {
            head.next = temp;
        }
        head = temp;
        head.next = null;
    }

    protected void dequeueImpl() {
        if (tail.next == null) {
            head = null;
        }
        tail = tail.next;
    }

    protected Object elementImpl() { return tail.value; }

    protected void clearImpl() {
        head = null;
        tail = null;
    }
    protected Object toArrayImpl() {
        Node temp = tail;
        Object[] newElements = new Object[size];
        for (int i = 0; i < size; i++) {
            newElements[i] = temp.value;
            temp = temp.next;
        }
        return newElements;
    }
    // inv: value != null
    private class Node {
        private Object value;
        private Node next;

        protected Node(Object value, Node next) {
            assert value != null;
            this.value = value;
            this.next = next;
        }
    }
}

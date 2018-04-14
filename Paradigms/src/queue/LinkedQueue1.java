package queue;

public class LinkedQueue1 {
    //inv: size >= 0 ∧ ∀ i = 0..size - 1: a[i] ≠ null
    private int size;
    private Node tail = null;
    private Node head = null;
    // pre: element ≠ null
    // post: size = size' + 1 ∧ ∀ i = 0..size' - 1 : a[i]' = a[i] ∧ a[size'] = element
    public void enqueue(Object element) {
        assert element != null;
        Node temp = new Node(element, null);
        if (isEmpty()) {
            tail = temp;
        } else {
            head.next = temp;
        }
        head = temp;
        head.next = null;
        size++;
    }
    // pre: size > 0
    // post: ℝ = tail.value ∧ size = size' − 1 ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    public Object dequeue() {
        assert size > 0;
        size--;
        Object result = tail.value;
        if (tail.next == null) {
            head = null;
        }
        tail = tail.next;
        return result;
    }
    // pre: size > 0
    // post: ℝ = tail.value ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    public Object element() {
        assert size > 0;
        return tail.value;
    }
    // post: ℝ = size ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    public int size() {
        return size;
    }
    // post: ℝ = (size == 0) ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    public boolean isEmpty() {
        return size == 0;
    }
    // inv: value != null
    private class Node {
        private Object value;
        private Node next;
        public Node(Object value, Node next) {
            assert value != null;
            this.value = value;
            this.next = next;
        }
    }
    // pre: size > 0
    // post: size = 0
    public void clear() {
        assert size > 0;
        head = null;
        tail = null;
        size = 0;
    }
}

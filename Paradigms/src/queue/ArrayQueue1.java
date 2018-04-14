package queue;

public class ArrayQueue1 {
    //inv: size >= 0 ∧ ∀ i = 0..size - 1: elements[i] ≠ null
    private int size;
    private int head;
    private Object[] elements = new Object[5];
    // pre: element ≠ null
    // post: size = size' + 1 ∧ ∀ i = 0..size' - 1 : elements[(head + i) % module]' = elements[(head + i) % module] ∧
    // ∧ elements[(head + size) % module] = element
    public void enqueue(Object element) {
        assert element != null;
        ensureCapacity(size + 1);
        if (isEmpty()) {
            head = 0;
        }
        elements[(head + size++) % elements.length] = element;
    }
    // post: elements.length >= capacity ∧ if (capacity <= elements.length):
    // ∀ i = 0..size - 1 : elements[(head + i) % module'] = elements[(head + i) % module']'
    // else: head = 0 ∧ module = module' * 2 ∧ ∀ i = 0..size - 1 : elements[(head' + i) % module'] = queue.elements[i]'
    private void ensureCapacity(int capacity) {
        if (capacity <= elements.length) {
            return;
        }
        elements = copy(2 * capacity);
        head = 0;
    }
    // pre: size > 0
    // post: ℝ = elements[head] ∧ head = (head' + 1) % module ∧ size = size' − 1 ∧
    // ∧ ∀ i = 0..size - 1 : elements[(head + i) % module]' = elements[(head + i) % module]
    public Object dequeue() {
        assert size > 0;
        Object value = element();
        elements[head++] = 0;
        head %= elements.length;
        size--;
        return value;
    }
    // pre: size > 0
    // post: ℝ = elements[head] ∧ size = size' ∧ ∀ i = 0..size - 1 : elements[(head + i) % module]' = elements[(head + i) % module]
    public Object element() {
        assert size > 0;
        return elements[head];
    }
    // post: ℝ = size ∧ size = size' ∧ ∀ i = 0..size - 1 : elements[(head + i) % module]' = elements[(head + i) % module]
    public int size() {
        return size;
    }
    // post: ℝ = (size == 0) ∧ size = size' ∧ ∀ i = 0..size - 1 : elements[(head + i) % module]' = elements[(head + i) % module]
    public boolean isEmpty() {
        return size == 0;
    }
    // post: size = 0
    public void clear() {
        assert size > 0;
        elements = new Object[5];
        size = 0;
    }
    /*public ArrayQueue makeCopy() {
        final ArrayQueue copy = new ArrayQueue();
        copy.size = size;
        copy.elements = elements;
        copy.head = head;
        return copy;
    }*/
    // pre: size > 0
    // post: ∀ i = 0..size - 1 : newArray[i] = elements[(i + head) % module]
    public Object toArray() {
        assert size > 0;
        return copy(size);
    }
    //pre: size >0
    private Object[] copy(int length) {
        assert size > 0;
        Object[] newElements = new Object[length];
        for (int i = head; i < size + head; i++) {
            newElements[i - head] = elements[i % elements.length];
        }
        return newElements;
    }
}

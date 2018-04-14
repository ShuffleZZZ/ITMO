package queue;

public class ArrayQueueModule {
    //inv: size >= 0 ∧ ∀ i = 0..size - 1: elements[i] ≠ null
    private static int size;
    private static int head;
    private static Object[] elements = new Object[5];
    // pre: element ≠ null
    // post: size = size' + 1 ∧ ∀ i = 0..size' - 1 : elements[(head + i) % MODULE]' = elements[(head + i) % MODULE] ∧
    // ∧ elements[(head + size) % MODULE] = element
    public static void enqueue(Object element) {
        assert element != null;
        ensureCapacity(size + 1);
        if (isEmpty()) {
            head = 0;
        }
        elements[(head + size++) % elements.length] = element;
    }
    // post: elements.length >= capacity ∧ if (capacity <= elements.length):
    // ∀ i = 0..size - 1 : elements[(head + i) % MODULE'] = elements[(head + i) % MODULE']'
    // else: head = 0 ∧ MODULE = MODULE' * 2 ∧ ∀ i = 0..size - 1 : elements[(head' + i) % MODULE'] = queue.elements[i]'
    private static void ensureCapacity(int capacity) {
        if (capacity <= elements.length) {
            return;
        }
        elements = copy(capacity * 2);
        head = 0;
    }
    // pre: size > 0
    // post: ℝ = elements[head] ∧ head = (head' + 1) % MODULE ∧ size = size' − 1 ∧
    // ∧ ∀ i = 0..size - 1 : elements[(head + i) % MODULE]' = elements[(head + i) % MODULE]
    public static Object dequeue() {
        assert size > 0;
        Object value = element();
        elements[head++] = null;
        head %= elements.length;
        size--;
        return value;
    }
    // pre: size > 0
    // post: ℝ = elements[head] ∧ size = size' ∧ ∀ i = 0..size - 1 : elements[(head + i) % MODULE]' = elements[(head + i) % MODULE]
    public static Object element() {
        assert size > 0;
        return elements[head];
    }
    // post: ℝ = size ∧ size = size' ∧ ∀ i = 0..size - 1 : elements[(head + i) % MODULE]' = elements[(head + i) % MODULE]
    public static int size() {
        return size;
    }
    // post: ℝ = (size == 0) ∧ size = size' ∧ ∀ i = 0..size - 1 : elements[(head + i) % MODULE]' = elements[(head + i) % MODULE]
    public static boolean isEmpty() {
        return size == 0;
    }
    // post: size = 0
    public static void clear() {
        assert size > 0;
        elements = new Object[5];
        size = 0;
    }
    // pre: size > 0
    // post: ∀ i = 0..size - 1 : newArray[i] = elements[(i + head) % MODULE]
    public static Object toArray() {
        assert size > 0;
        return copy(size);
    }
    // pre: size > 0
    private static Object[] copy(int length) {
        assert size > 0;
        Object[] newElements = new Object[length];
        for (int i = head; i < size + head; i++) {
            newElements[i - head] = elements[i % elements.length];
        }
        return newElements;
    }
}

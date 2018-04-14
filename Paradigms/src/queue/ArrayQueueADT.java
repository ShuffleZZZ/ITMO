package queue;

public class ArrayQueueADT {
    //inv: queue.size >= 0 ∧ ∀ i = 0..queue.size - 1: queue.elements[i] ≠ null
    private int size;
    private int head;
    private Object[] elements = new Object[5];
    // pre: element ≠ null
    // post: queue.size = queue.size' + 1 ∧ ∀ i = 1..queue.size' - 1 : ∧
    // queue.elements[(queue.head + i) % queue.module]' = queue.elements[(queue.head + i) % queue.module]
    // ∧ queue.elements[(queue.head + queue.size) % queue.module] = element
    public static void enqueue(ArrayQueueADT queue, Object element) {
        assert element != null;
        ensureCapacity(queue, queue.size + 1);
        if (isEmpty(queue)) {
            queue.head = 0;
        }
        queue.elements[(queue.head + queue.size++) % queue.elements.length] = element;
    }
    // post: queue.elements.length >= capacity ∧ if (capacity <= queue.elements.length):
    // ∀ i = 0..queue.size - 1 : queue.elements[(queue.head + i) % queue.module'] = queue.elements[(queue.head + i) % queue.module']'
    // else: queue.head = 0 ∧ queue.module = queue.module' * 2 ∧ ∀ i = 0..queue.size - 1 :
    // queue.elements[(queue.head' + i) % queue.module'] = queue.elements[i]'
    private static void ensureCapacity(ArrayQueueADT queue, int capacity) {
        if (capacity <= queue.elements.length) {
            return;
        }
        queue.elements = copy(queue, capacity * 2);
        queue.head = 0;
    }
    // pre: queue.size > 0
    // post: ℝ = queue.elements[queue.head] ∧ queue.head = (queue.head' + 1) % queue.module ∧ queue.size = queue.size' − 1 ∧
    // ∧ ∀ i = 0..queue.size - 1 : queue.elements[(queue.head + i) % queue.module]' = queue.elements[(queue.head + i) % queue.module]
    public static Object dequeue(ArrayQueueADT queue) {
        assert queue.size > 0;
        Object value = element(queue);
        queue.elements[queue.head++] = 0;
        queue.head %= queue.elements.length;
        queue.size--;
        return value;
    }
    // pre: queue.size > 0
    // post: ℝ = queue.elements[queue.head] ∧ queue.size = queue.size' ∧
    // ∧ ∀ i = 0..queue.size - 1 : queue.elements[(queue.head + i) % queue.module]' = queue.elements[(queue.head + i) % queue.module]
    public static Object element(ArrayQueueADT queue) {
        assert queue.size > 0;
        return queue.elements[queue.head];
    }
    // post: ℝ = queue.size ∧ queue.size = queue.size' ∧ ∀ i = 0..queue.size - 1 :
    // queue.elements[(queue.head + i) % queue.module]' = queue.elements[(queue.head + i) % queue.module]
    public static int size(ArrayQueueADT queue) {
        return queue.size;
    }
    // post: ℝ = (queue.size == 0) ∧ queue.size = queue.size' ∧ ∀ i = 0..size - 1 :
    // elements[(queue.head + i) % queue.module]' = elements[(queue.head + i) % queue.module]
    public static boolean isEmpty(ArrayQueueADT queue) {
        return queue.size == 0;
    }
    // post: queue.size = 0
    public static void clear(ArrayQueueADT queue) {
        assert queue.size > 0;
        queue.elements = new Object[5];
        queue.size = 0;
    }
    // pre: size > 0
    // post: ∀ i = 0..size - 1 : newArray[i] = queue.elements[(i + queue.head) % queue.module]
    public static Object toArray(ArrayQueueADT queue) {
        assert queue.size > 0;
        return copy(queue, queue.size);
    }
    // pre: size > 0
    private static Object[] copy(ArrayQueueADT queue, int length) {
        assert queue.size > 0;
        Object[] newElements = new Object[length];
        for (int i = queue.head; i < queue.size + queue.head; i++) {
            newElements[i - queue.head] = queue.elements[i % queue.elements.length];
        }
        return newElements;
    }
}

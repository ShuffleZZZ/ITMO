package queue;

public class ArrayQueue extends queue.AbstractQueue {
    private Object[] elements = new Object[5];
    private int head;
    protected void enqueueImpl(Object element) {
        ensureCapacity(size + 1);
        if (isEmpty()) {
            head = 0;
        }
        elements[(head + size) % elements.length] = element;
    }
    private void ensureCapacity(int capacity) {
        if (capacity <= elements.length) {
            return;
        }
        elements = copy(2 * capacity);
        head = 0;
    }
    // pre: size > 0
    private Object[] copy(int length) {
        assert size > 0;
        Object[] newElements = new Object[length];
        for (int i = head; i < size + head; i++) {
            newElements[i - head] = elements[i % elements.length];
        }
        return newElements;
    }
    protected Object elementImpl() {
        return elements[head];
    }
    protected void dequeueImpl() {
        elements[head++] = 0;
        head %= elements.length;
    }
    protected void clearImpl() {
        elements = new Object[5];
    }
    protected Object toArrayImpl() {
        return copy(size);
    }
}

package queue;

import java.lang.reflect.Array;

public abstract class AbstractQueue implements queue.Queue {
    //inv: size >= 0 ∧ ∀ i = 0..size - 1: a[i] ≠ null
    protected int size;

    // pre: element ≠ null
    // post: size = size' + 1 ∧ ∀ i = 0..size' - 1 : a[i]' = a[i] ∧ a[size'] = element
    public void enqueue(Object element) {
        assert element != null;
        enqueueImpl(element);
        size++;
    }

    protected abstract void enqueueImpl(Object element);

    // pre: size > 0
    // post: ℝ = elementImpl() ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    public Object element() {
        assert size > 0;
        return elementImpl();
    }

    protected abstract Object elementImpl();

    // pre: size > 0
    // post: ℝ = element() ∧ size = size' − 1 ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    public Object dequeue() {
        assert size > 0;
        Object result = element();
        dequeueImpl();
        size--;
        return result;
    }

    protected abstract void dequeueImpl();

    // post: ℝ = size ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    public int size() {
        return size;
    }

    // post: ℝ = (size == 0) ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    public boolean isEmpty() {
        return size == 0;
    }

    // pre: size > 0
    // post: size = 0
    public void clear() {
        assert size > 0;
        clearImpl();
        size = 0;
    }

    protected abstract void clearImpl();

    // pre: size > 0
    // post: ∀ i = 0..size - 1 : newArray[i] = elements[(i + head) % module]
    public Object toArray() {
        assert size > 0;
        Object[] result = new Object[size];
        for (int i = 0; i < size; i++) {
            result[i] = dequeue();
            enqueue(result[i]);
        }
        return result;
    }
    /*public Object toArray() {
        assert size > 0;
        Object result = toArrayImpl();
        return result;
    }
    protected abstract Object toArrayImpl();*/
}

public abstract class AbstractStack implements Stack {
    protected int size;

    public void push(Object element) {
        assert element != null;

        pushImpl(element);
        size++;
    }

    protected abstract void pushImpl(Object element);

    public Object peek() {
        assert size > 0;

        return peekImpl();
    }

    protected abstract Object peekImpl();

    public Object pop() {
        assert size > 0;

        Object result = peek();
        size--;
        remove();
        return result;
    }

    protected abstract void remove();

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }
}

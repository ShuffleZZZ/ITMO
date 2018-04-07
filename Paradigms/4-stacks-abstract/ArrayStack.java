import java.util.Arrays;

public class ArrayStack extends AbstractStack implements Copiable {
    private Object[] elements = new Object[2];

    protected void pushImpl(Object element) {
        ensureCapacity(size + 1);
        elements[size] = element;
    }

    private void ensureCapacity(int capacity) {
        if (capacity > elements.length) {
            elements = Arrays.copyOf(elements, capacity);
        }
    }

    protected void remove() {
        elements[size] = null;
    }

    protected Object peekImpl() {
        return elements[size - 1];
    }

    public ArrayStack makeCopy() {
        final ArrayStack copy = new ArrayStack();
        copy.size = size;
        copy.elements = Arrays.copyOf(elements, size);
        return copy;
    }
}

package queue;
//inv: size >= 0 ∧ ∀ i = 0..size - 1: a[i] ≠ null
public interface Queue {
    // pre: element ≠ null
    // post: size = size' + 1 ∧ ∀ i = 0..size' - 1 : a[i]' = a[i] ∧ a[size'] = element
    void enqueue(Object element);
    // pre: size > 0
    // post: ℝ = a[size - 1] ∧ size = size' − 1 ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    Object dequeue();
    // pre: size > 0
    // post: ℝ = a[size - 1] ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    Object element();
    // post: ℝ = size ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    int size();
    // post: ℝ = (size == 0) ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    boolean isEmpty();
    // pre: size > 0
    // post: size = 0
    void clear();
    // pre: size > 0
    // post: size = size' ∧ ∀ i = 0..size - 1 : newArray[i] = a[i]
    Object toArray();
}

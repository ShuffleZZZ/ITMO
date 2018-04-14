package queue;

public interface Copiable {
    // post: ℝ = size ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    /*public*/ int size();
    // post: ℝ = (size == 0) ∧ size = size' ∧ ∀ i = 0..size - 1 : a[i]' = a[i]
    /*public*/ boolean isEmpty();
}

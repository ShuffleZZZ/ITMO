package ru.ifmo.rain.glagolev.arrayset;

import java.util.*;

public class ArraySet<E> extends AbstractSet<E> implements SortedSet<E> {
    private final List<E> elements;
    private final Comparator<? super E> comparator;

    public ArraySet() {
        this((Comparator<E>) null);
    }

    public ArraySet(Comparator<? super E> comparator) {
        elements = Collections.emptyList();
        this.comparator = comparator;
    }

    public ArraySet(Collection<? extends E> elements) {
        this(elements, null);
    }

    public ArraySet(Collection<? extends E> elements, Comparator<? super E> comparator) {
        this.comparator = comparator;
        TreeSet<E> tree = new TreeSet<>(comparator);
        tree.addAll(Objects.requireNonNull(elements));
        this.elements = new ArrayList<>(tree);
    }

    @Override
    @SuppressWarnings("unchecked")
    public boolean contains(Object object) {
        return Collections.binarySearch(elements, (E) Objects.requireNonNull(object), comparator) >= 0;
    }


    @Override
    public Iterator<E> iterator() {
        return Collections.unmodifiableList(elements).iterator();
    }

    @Override
    public int size() {
        return elements.size();
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public Comparator<? super E> comparator() {
        return comparator;
    }

    @Override
    public SortedSet<E> subSet(E fromElement, E toElement) {
        return subSet(fromElement, toElement, false);
    }

    private SortedSet<E> subSet(E fromElement, E toElement, boolean include) {
        if (isEmpty()) {
            return new ArraySet<>(comparator);
        }
        int from = findInd(fromElement);
        int to = findInd(toElement);
        if (include) {
            ++to;
        }
        if (from > to) {
            throw new IllegalArgumentException();
        }
        return new ArraySet<>(elements.subList(from, to), comparator);
    }

    private int findInd(E element) {
        int ind = Collections.binarySearch(elements, Objects.requireNonNull(element), comparator);
        return ind < 0 ? -ind - 1 : ind;
    }

    @Override
    public SortedSet<E> headSet(E toElement) {
        try {
            return subSet(first(), toElement);
        } catch (NoSuchElementException e) {
            return new ArraySet<>(comparator);
        }
    }

    @Override
    public SortedSet<E> tailSet(E fromElement) {
        try {
            return subSet(fromElement, last(), true);
        } catch (NoSuchElementException e) {
            return new ArraySet<>(comparator);
        }
    }

    @Override
    public E first() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        return elements.get(0);
    }

    @Override
    public E last() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        return elements.get(elements.size() - 1);
    }
}

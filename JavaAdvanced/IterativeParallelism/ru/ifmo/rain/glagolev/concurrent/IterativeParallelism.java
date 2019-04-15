package ru.ifmo.rain.glagolev.concurrent;

import info.kgeorgiy.java.advanced.concurrent.ScalarIP;

import java.util.*;
import java.util.function.Function;
import java.util.function.Predicate;

/**
 * Scalar iterative parallelism support.
 */
public class IterativeParallelism implements ScalarIP {

    /**
     * Default constructor.
     */
    public IterativeParallelism() {}
    /**
     * Function returns first maximum of given {@link List} by using given {@link Comparator}.
     * It uses the given amount of {@link Thread threads}.
     * @param i                     amount of {@link Thread threads} available to use
     * @param list                  {@link List} of arguments to apply function on
     * @param comparator            {@link Comparator} for type T to use in function
     * @param <T>                   the return type which defines elements of given {@link List}
     *                              aswell as type of given {@link Predicate}
     * @return                      returns the first maximum element of given {@link List}
     * @throws InterruptedException throwed if executing thread was interrupted.
     * @throws java.util.NoSuchElementException if not values are given.
     */
    @Override
    public <T> T maximum(int i, List<? extends T> list, Comparator<? super T> comparator) throws InterruptedException {
        if (list.isEmpty()) {
            throw new NoSuchElementException("Empty list given");
        }
        Function<List<? extends T>, ? extends T> getMax = (args) -> Collections.max(args, comparator);
        return getMax.apply(compute(i, list, getMax));
    }

    /**
     * Function returns first minimum of given {@link List} by using given {@link Comparator}.
     * It uses the given amount of {@link Thread threads}.
     * @param i                     amount of {@link Thread threads} available to use
     * @param list                  {@link List} of arguments to apply function on
     * @param comparator            {@link Comparator} for type T to use in function
     * @param <T>                   the return type which defines elements of given {@link List}
     *                              aswell as type of given {@link Predicate}
     * @return                      returns the first minimum element of given {@link List}
     * @throws InterruptedException throwed if executing thread was interrupted.
     * @throws java.util.NoSuchElementException if not values are given.
     */
    @Override
    public <T> T minimum(int i, List<? extends T> list, Comparator<? super T> comparator) throws InterruptedException {
        return maximum(i, list, comparator.reversed());
    }

    /**
     * Function shows if all elements of given {@link List} satisfy condition of given {@link Predicate}.
     * It uses the given amount of {@link Thread threads}.
     * @param i                     amount of {@link Thread threads} available to use
     * @param list                  {@link List} of arguments to apply function on
     * @param predicate             {@link Predicate} which is used to filter needed arguments
     * @param <T>                   type which defines elements of given {@link List}
     *                              aswell as type of given {@link Predicate}
     * @return                      returns {@link Boolean} value which shows if all elements
     *                              satisfy {@link Predicate predicate's} condition
     * @throws InterruptedException throwed if executing thread was interrupted.
     */
    @Override
    public <T> boolean all(int i, List<? extends T> list, Predicate<? super T> predicate) throws InterruptedException {
        Function<List<? extends T>, Boolean> allMatch = (l) -> list.stream().allMatch(predicate);
        return compute(i, list, allMatch).stream().allMatch(Boolean::booleanValue);
    }

    /**
     * Function shows if any elements of given {@link List} satisfy condition of given {@link Predicate}.
     * It uses the given amount of {@link Thread threads}.
     * @param i                     amount of {@link Thread threads} available to use
     * @param list                  {@link List} of arguments to apply function on
     * @param predicate             {@link Predicate} which is used to filter needed arguments
     * @param <T>                   type which defines elements of given {@link List}
     *                              aswell as type of given {@link Predicate}
     * @return                      returns @link Boolean} value which shows if any elements
     *                              satisfy {@link Predicate predicate's} condition
     * @throws InterruptedException throwed if executing thread was interrupted.
     */
    @Override
    public <T> boolean any(int i, List<? extends T> list, Predicate<? super T> predicate) throws InterruptedException {
        return !all(i, list, Predicate.not(predicate));
    }

    private <T, R> List<R> compute(int i, List<? extends T> list, Function<List<? extends T>, R> function)
                                                                    throws InterruptedException, IllegalArgumentException {
        if (i <= 0) {
            throw new IllegalArgumentException("Operation cannot be computed on 0 or less threads");
        }
        final int usedThreads = Math.min(i, list.size());
        final int sublistsSize = list.size() / usedThreads;
        final int mod = list.size() - sublistsSize * usedThreads;
        int shift = 0;
        List<Thread> threads = new ArrayList<>(usedThreads);
        List<R> result = new ArrayList<>(Collections.nCopies(usedThreads, null));
        for (int j = 0; j < usedThreads; ++j) {
            final int ind = j;
            final int leftBoard = shift + j * sublistsSize;
            int tempRightBoard = shift + (j + 1) * sublistsSize;
            if (j < mod) {
                ++tempRightBoard;
                ++shift;
            }
            final int rightBoard = tempRightBoard;
            threads.add(new Thread(() -> result.set(ind, function.apply(list.subList(leftBoard, rightBoard)))));
        }
        for (Thread thread : threads) {
            thread.start();
        }
        for (Thread thread : threads) {
            thread.join();
        }
        return result;
    }
}

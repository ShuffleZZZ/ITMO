package ru.ifmo.rain.glagolev.mapper;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;

/**
 * {@link Class} implementing multithread apply of the given {@link Function} on the given {@link List}
 */
public class ParallelMapperImpl implements ParallelMapper {
    private final Queue<Runnable> tasks;
    private final List<Thread> pool;

    /**
     * Default constructor
     */
    public ParallelMapperImpl() {
        tasks = new ArrayDeque<>();
        pool = new ArrayList<>();
    }

    /**
     * Constructor with given amount of {@link Thread threads}
     * @param threads amount of available {@link Thread threads}
     */
    public ParallelMapperImpl(int threads) {
        if (threads <= 0) {
            throw new IllegalArgumentException("Operations cannot be computed on 0 or less threads");
        }
        tasks = new ArrayDeque<>();
        pool = new ArrayList<>(threads);
        for (int i = 0; i < threads; ++i) {
            final Thread thread = new Thread(() -> {
                while (!Thread.interrupted()) {
                    try {
                        polltask();
                    } catch (InterruptedException e) {
                        break;
                    }
                }
            });
            pool.add(thread);
            thread.start();
        }
    }

    private void polltask() throws InterruptedException {
        Runnable task;
        synchronized (tasks) {
            while (tasks.isEmpty()) {
                tasks.wait();
            }
            task = tasks.poll();
            tasks.notifyAll();
        }
        task.run();
    }

    private void addTask(final Runnable task) {
        synchronized (tasks) {
            tasks.add(task);
            tasks.notifyAll();
        }
    }

    /**
     * {@inheritDoc}
     * @param function              {@link Function} given to apply on the arguments
     * @param list                  {@link List} of arguments
     * @param <T>                   type of given arguments
     * @param <R>                   type of arguments in returned {@link List}
     * @return                      {@link List} of arguments returned after application of {@link Function}
     * @throws InterruptedException {@inheritDoc}
     */
    @Override
    public <T, R> List<R> map(Function<? super T, ? extends R> function, List<? extends T> list) throws InterruptedException {
        final int size = list.size();
        Results<R> results = new Results<>(size);
        for (int i = 0; i < size; ++i) {
            final int ind = i;
            addTask(() -> results.set(ind, function.apply(list.get(ind))));
        }
        return results.get();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void close() {
        for (Thread thread : pool) {
            thread.interrupt();
        }
        try {
            for (Thread thread : pool) {
                thread.join();
            }
        } catch (InterruptedException ignored) {
            //
        }
    }

    private class Results<R> {
        private final List<R> list;
        private int count;

        private Results(final int size) {
            list = new LinkedList<>(Collections.nCopies(size, null));
            count = 0;
        }

        private void set(final int ind, R res) {
            list.set(ind, res);
            synchronized (this) {
                if (++count == list.size()) {
                    notify();
                }
            }
        }

        private List<R> get() throws InterruptedException {
            synchronized (this) {
                while (count < list.size()) {
                    wait();
                }
            }
            return list;
        }
    }
}

package stack;

import kotlinx.atomicfu.AtomicArray;
import kotlinx.atomicfu.AtomicRef;

public class StackImpl implements Stack {

    private static final int ELIMINATION_ARRAY_SIZE = 32, CHECK_CONST = 2, LOOP_TIME = 30;

    // head pointer
    private AtomicRef<Node> head = new AtomicRef<>(null);
    // elimination array
    private AtomicArray<Integer> eliminationArray = new AtomicArray<>(ELIMINATION_ARRAY_SIZE);

    @Override
    public void push(int x) {
        final int eliminationIndex = (int) (Math.random() * (ELIMINATION_ARRAY_SIZE - 1 - 2 * CHECK_CONST));
        for (int i = eliminationIndex; i < eliminationIndex + 2 * CHECK_CONST; i++) {
            final Integer newValue = x;
            if (eliminationArray.get(i).compareAndSet(null, newValue)) {
                for (int j = 0; j < LOOP_TIME; j++) {
                    final Integer curValue = eliminationArray.get(i).getValue();
                    if (curValue == null || curValue != x) {
                        return;
                    }
                }
                if (eliminationArray.get(i).compareAndSet(newValue, null)) {
                    break;
                }
                return;
            }
        }
        while (true) {
            Node curHead = head.getValue();
            Node newHead = new Node(x, curHead);
            if (head.compareAndSet(curHead, newHead)) {
                return;
            }
        }
    }

    @Override
    public int pop() {
        final int eliminationIndex = (int) (Math.random() * (ELIMINATION_ARRAY_SIZE - 1 - 2 * CHECK_CONST));
        for (int i = eliminationIndex; i < eliminationIndex + 2 * CHECK_CONST; i++) {
            final Integer x = eliminationArray.get(i).getValue();
            if (x != null && eliminationArray.get(i).compareAndSet(x, null)) {
                return x;
            }
        }
        while (true) {
            Node curHead = head.getValue();
            if (curHead == null) {
                return Integer.MIN_VALUE;
            }
            if (head.compareAndSet(curHead, curHead.next.getValue())) {
                return curHead.x;
            }
        }
    }

    private static class Node {
        final AtomicRef<Node> next;
        final int x;

        Node(int x, Node next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }
    }
}
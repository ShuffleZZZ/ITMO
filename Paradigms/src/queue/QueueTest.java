package queue;

import queue.ArrayQueue;
import queue.LinkedQueue;

public class QueueTest {
    public static void fill(queue.Queue structure) {
        for (int i = 0; i < 3; i++) {
            structure.enqueue(i);
        }
    }

    public static void dump(queue.Queue structure) {
        while (!structure.isEmpty()) {
            System.out.println(structure.size() + " " +
                structure.element() + " " + structure.dequeue());
        }
    }

    public static void test(queue.Queue structure) {
        fill(structure);
        dump(structure);
        System.out.println();
        System.out.println("-------");
    }

    public static void main(String[] args) {
        test(new ArrayQueue());
        test(new LinkedQueue());
    }
}

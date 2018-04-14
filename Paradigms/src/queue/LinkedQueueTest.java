public class LinkedQueueTest {
    public static void fill(queue.LinkedQueue1 structure) {
        for (int i = 0; i < 10; i++) {
            structure.enqueue(i);
        }
    }

    public static void dump(queue.LinkedQueue1 structure) {
        while (!structure.isEmpty()) {
            System.out.println(structure.size() + " " +
                structure.element() + " " + structure.dequeue());
        }
    }

    public static void main(String[] args) {
        queue.LinkedQueue1 structure = new queue.LinkedQueue1();
        fill(structure);
        dump(structure);
    }
}

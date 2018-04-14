public class ArrayQueueTest {
    public static void fill(queue.ArrayQueue structure) {
        for (int i = 0; i < 10; i++) {
            structure.enqueue(i);
        }
    }

    public static void dump(queue.ArrayQueue structure) {
        while (!structure.isEmpty()) {
            System.out.println(structure.size() + " " +
                structure.element() + " " + structure.dequeue());
        }
    }

    public static void main(String[] args) {
        queue.ArrayQueue structure = new queue.ArrayQueue();
        fill(structure);
        dump(structure);
    }
}

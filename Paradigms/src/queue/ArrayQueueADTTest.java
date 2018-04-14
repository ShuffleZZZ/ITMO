public class ArrayQueueADTTest {
    public static void fill(queue.ArrayQueueADT structure) {
        for (int i = 0; i < 10; i++) {
            queue.ArrayQueueADT.enqueue(structure, i);
        }
    }

    public static void dump(queue.ArrayQueueADT structure) {
        while (!queue.ArrayQueueADT.isEmpty(structure)) {
            System.out.println(
                queue.ArrayQueueADT.size(structure) + " " +
                queue.ArrayQueueADT.element(structure) + " " +
                queue.ArrayQueueADT.dequeue(structure)
            );
        }
    }

    public static void main(String[] args) {
        queue.ArrayQueueADT structure = new queue.ArrayQueueADT();
        fill(structure);
        dump(structure);
    }
}

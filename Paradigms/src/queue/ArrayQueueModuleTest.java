public class ArrayQueueModuleTest {
    public static void fill() {
        for (int i = 0; i < 10; i++) {
            queue.ArrayQueueModule.enqueue(i);
        }
    }

    public static void dump() {
        while (!queue.ArrayQueueModule.isEmpty()) {
            System.out.println(
                queue.ArrayQueueModule.size() + " " +
                queue.ArrayQueueModule.element() + " " +
                queue.ArrayQueueModule.dequeue()
            );
        }
    }

    public static void main(String[] args) {
        fill();
        dump();
    }
}

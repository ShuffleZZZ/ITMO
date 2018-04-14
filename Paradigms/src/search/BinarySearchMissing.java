package search;

public class BinarySearchMissing {
    // pre: key, array of Z; forall i = 0..array.length - 2: array[i] >= array[i+1]
    // inv: forall i=0..array.length-1: a[i] == array[i] == constant
    private static int binSearch2(int[] a, int key) {
        int l = -1, r = a.length;
        while (l < r - 1) {
            int m = (l + r) / 2;
            if (a[m] <= key) {
                //(a[m] <= key): a[l] >= key >= a[m == l + (r - l) / 2]
                r = m;
            } else {
                //(a[m] > key): a[r] <= key <= a[m == l + (r - l) / 2]
                l = m;
            }
        }
        // r - l <= 1
        return r;
    }

    // pre: key, array of Z; array[i] >= array[i + 1]
    public static void main(String[] args) {
        int[] array = new int[args.length - 1];
        int key = Integer.parseInt(args[0]);
        for (int i = 1; i < args.length; i++) {
            array[i - 1] = Integer.parseInt(args[i]);
        }
        int RES = binSearch2(array, key);
        if (array.length == 0 || RES == array.length || array[RES] != key) {
            RES = -(RES + 1);
        }
        System.out.println(RES);
        // post: print i: (min(0..array.length-1): array[i] <= key) || (key > array[0]: i = -1) ||
        // || (key < array[array.length - 1]: i = -array.length) || (array[0] >= key >= array[array.length - 1] && key not in array: i = -index)
    }
}
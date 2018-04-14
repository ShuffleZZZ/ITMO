package search;

public class BinarySearch {
    // pre: key, array of Z; forall i = 0..array.length - 2: array[i] >= array[i + 1]; -1 <= l <= r <= array.length - 1;
    // (a[l..r] > key && r == a.length - 1) || (a[l] >= key >= a[r])
    // inv: forall i = 0..array.length - 1: a[i] == array[i] == constant
    private static int binSearch ( int[] a, int key, int l, int r){
        if (l <= r) {
            int m = l + (r - l) / 2;
            if (m == -1) {
                // key > a[l..r]
                return 0;
            }
            if (a[m] > key) {
                //(a[m] > key): a[r] <= key <= a[m + 1 == l + (r - l) / 2 + 1]
                return binSearch(a, key,m+1, r);
            } else {
                //(a[m] <= key): a[l] >= key >= a[m - 1 == l + (r - l) / 2 - 1]
                return binSearch(a, key, l,m-1);
            }
        }
        // r - l <= 1
        return r + 1;
    }
    // pre: key, array of Z; forall i = 0..array.length - 2: array[i] >= array[i+1]
    // inv: forall i=0..array.length-1: a[i] == array[i] == constant
    private static int binSearch2 ( int[] a, int key){
        int l = 0, r = a.length-1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (m == -1) {
                // key > array[l..r]
                return 0;
            }
            if (a[m] > key) {
                //(a[m] > key): a[r] <= key <= a[m == l + (r - l) / 2]
                l = m + 1;
            } else {
                //(a[m] <= key): a[l] >= key >= a[m == l + (r - l) / 2]
                r = m - 1;
            }
        }
        // r - l <= 1
        return r + 1;
    }
    // pre: key, array of Z; array[i] >= array[i + 1]
    public static void main (String[] args) {
        int[] array= new int[args.length - 1];
        int key = Integer.parseInt(args[0]);
        for (int i = 1 ; i < args.length ; i++) {
            array[i - 1] = Integer.parseInt(args[i]);
        }
        int RES = binSearch(array, key, 0, array.length - 1);
        //int RES = binSearch2(array, key);
        System.out.println(RES);
        // post: print i: (min(0..array.length-1): array[i] <= key) || (key > array[0]: i = 0) ||
        // || (key < array[array.length - 1]: i = array.length - 1)
    }
}
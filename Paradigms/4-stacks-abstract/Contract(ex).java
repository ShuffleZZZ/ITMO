public class Contract {

    // n >= 0
    static int power(int a, int n) {
        // n >= 0
        int r = 1;
        // n >= 0 && r == 1 && a == a' && n = n'

        // r * a ^ n == a' ^ n' && n >= 0
        while (n != 0) {
            // r * a ^ n == a' ^ n' && n > 0
            if (n % 2 == 1) {
                // r * a ^ n == a' ^ n' && n > 0 && n % 2 == 1
                // r * a ^ n == a' ^ n' && n >= 1 && n % 2 == 1
                // r * a ^ n == a' ^ n' && (n - 1) >= 0 && n % 2 == 1
                // (r * a) * a ^ (n - 1) == a' ^ n' && (n - 1) >= 0 && n % 2 == 1
                r = r * a;
                n = n - 1;
                // r * a ^ n == a' ^ n' && n >= 0 && n % 2 == 0
            }
            // r * a ^ n == a' ^ n' && n >= 0 && n % 2 == 0
            // r * (a * a) ^ (n / 2) == a' ^ n' && n / 2 >= 0
            n = n / 2;
            a = a * a;
            // r * a ^ n == a' ^ n' && n >= 0
        }
        // r * a ^ n == a' ^ n' && n == 0

        // r = a' ^ n'
        return r;
    }

    private static int v = 0;

    // Pre: x >= 0 && P(v)
    public static int add(int x) {
        return v += x;
    }

    public static void loopExample() {
        while (true) {
            // x >= 0
            add(10);
            // R >= 0
        }
    }


    // x >= 0
    double sqrt(double x) {
        return Math.sqrt(x);
    }
    // abs(R*R - x) < eps && R >= 0

    // a != null
    int[] abs(int[] a) {
        int[] result = new int[a.length];
        for (int i = 0; i < a.length; i++) {
            result[i] = Math.abs(i);
        }
        return result;
    }
    // forall i=0..a.length - 1:
    // R[i] >= 0 && (R[i] == a[i] || R[i] == -a[i])
}

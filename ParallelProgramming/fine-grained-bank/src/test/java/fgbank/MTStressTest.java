package fgbank;

import junit.framework.TestCase;

import java.util.Locale;
import java.util.concurrent.Phaser;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Multi-threaded stress test for bank implementation -- many threads and operations of various accounts.
 *
 * <p>This test test correctness of concurrent deposit, withdraw, transfer, and getTotalAmount operations.
 * It does not check getAmount operations concurrently with the above.
 */
public class MTStressTest extends TestCase {
    private static final int N = 100;
    private static final long MEAN = 1_000_000_000;
    private static final int AMT = 1_000; // AMT << MEAN, so that probability of over/under flow is negligible
    private static final int MOD = 100; // all deposits / withdrawals are divisible by MOD
    private static final int THREADS = 16;
    private static final int TOTAL_PHASES = 20;
    private static final int INIT_PHASES = 10;
    private static final long PHASE_DURATION_MILLIS = 1000;

    private final Phaser phaser = new Phaser(1 + THREADS);
    private final Bank bank = new BankImpl(N);
    private final AtomicLong[] expected = new AtomicLong[N];
    private final AtomicLong totalOps = new AtomicLong(); // only non-init phases are counted
    private volatile boolean failed;
    private long dummy; // will prevent code elimination

    public void testStress() throws InterruptedException {
        assertEquals(N, bank.getNumberOfAccounts());
        for (int i = 0; i < N; i++)
            bank.deposit(i, MEAN);
        for (int i = 0; i < N; i++)
            assertEquals(MEAN, bank.getAmount(i));
        for (int i = 0; i < N; i++)
            expected[i] = new AtomicLong(MEAN);
        TestThread[] ts = new TestThread[N];
        for (int threadNo = 0; threadNo < THREADS; threadNo++) {
            TestThread t = new TestThread(threadNo);
            ts[threadNo] = t;
            t.start();
        }
        Stats stats = new Stats();
        for (int phase = 1; !failed && phase <= TOTAL_PHASES; phase++) {
            System.out.printf("Phase #%2d - ", phase);
            totalOps.set(0);
            if (phaser.arriveAndAwaitAdvance() < 0)
                break;
            if (phaser.arriveAndAwaitAdvance() < 0)
                break;
            long ops = totalOps.get();
            if (phase > INIT_PHASES) {
                stats.add(ops);
                System.out.printf(Locale.US, "done %,10d ops (measure)%n", ops);
            } else
                System.out.printf(Locale.US, "done %,10d ops (warm up)%n", ops);
        }
        for (int threadNo = 0; threadNo < THREADS; threadNo++)
            ts[threadNo].join();
        assertFalse(failed);
        System.out.println("Average ops per phase: " + stats);
    }

    private class TestThread extends Thread {
        private final int threadNo;
        private ThreadLocalRandom rnd;

        public TestThread(int threadNo) {
            super("TestThread-" + threadNo);
            this.threadNo = threadNo;
        }

        @Override
        public void run() {
            rnd = ThreadLocalRandom.current();
            try {
                for (int phase = 1; !failed && phase <= TOTAL_PHASES; phase++) {
                    runPhase(phase);
                }
            } catch (Throwable t) {
                t.printStackTrace();
                failed = true;
                phaser.forceTermination();
            }
        }

        private void runPhase(int phase) {
            verifyState();
            if (phaser.arriveAndAwaitAdvance() < 0)
                return;
            int ops = 0;
            long tillTimeMillis = System.currentTimeMillis() + PHASE_DURATION_MILLIS;
            do {
                runOperation();
                ops++;
            } while (System.currentTimeMillis() < tillTimeMillis);
            totalOps.addAndGet(ops);
            phaser.arriveAndAwaitAdvance();
        }

        private void verifyState() {
            long expectedTotal = 0;
            for (int i = 0; i < N; i++) {
                long ei = expected[i].get();
                assertEquals(ei, bank.getAmount(i));
                expectedTotal += ei;
            }
            assertEquals(expectedTotal, bank.getTotalAmount());
        }

        private void runOperation() {
            int op = rnd.nextInt(100);
            if (op == 0) {
                // every 100th operation on average is getTotalAmount
                long totalAmount = bank.getTotalAmount();
                assertEquals(0, totalAmount % MOD); // the result must be divisible to MOD
                return;
            }
            int i = rnd.nextInt(N);
            long amount;
            switch (op & 3) {
                case 0:
                    amount = nextRoundAmount();
                    bank.deposit(i, amount);
                    expected[i].addAndGet(amount);
                    break;
                case 1:
                    amount = nextRoundAmount();
                    bank.withdraw(i, amount);
                    expected[i].addAndGet(-amount);
                    break;
                case 2:
                    int j = rnd.nextInt(N - 1);
                    if (j >= i)
                        j++;
                    // arbitrary amount is transferred between accounts
                    amount = nextAmount();
                    bank.transfer(i, j, amount);
                    expected[i].addAndGet(-amount);
                    expected[j].addAndGet(amount);
                    break;
                case 3:
                    // NOTE: the result does not have to be equal to expected.
                    dummy = bank.getAmount(i);
                    break;
            }
        }

        private long nextRoundAmount() {
            return ((long) nextAmount() + MOD - 1) / MOD * MOD;
        }

        private int nextAmount() {
            return rnd.nextInt(AMT) + 1;
        }
    }
}
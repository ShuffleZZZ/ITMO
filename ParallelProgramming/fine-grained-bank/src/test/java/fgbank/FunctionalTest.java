package fgbank;

import junit.framework.TestCase;

/**
 * Functional single-threaded test-suite for bank implementation.
 *
 * @author Roman Elizarov
 */
public class FunctionalTest extends TestCase {
    private static final int N = 10;

    private final Bank bank = new BankImpl(N);

    public void testEmptyBank() {
        assertEquals(N, bank.getNumberOfAccounts());
        assertEquals(0, bank.getTotalAmount());
        for (int i = 0; i < N; i++)
            assertEquals(0, bank.getAmount(i));
    }

    public void testDeposit() {
        long amount = 1234;
        long result = bank.deposit(1, amount);
        assertEquals(amount, result);
        assertEquals(amount, bank.getAmount(1));
        assertEquals(amount, bank.getTotalAmount());
    }

    public void testWithdraw() {
        int depositAmount = 2345;
        long depositResult = bank.deposit(1, depositAmount);
        assertEquals(depositAmount, depositResult);
        assertEquals(depositAmount, bank.getAmount(1));
        assertEquals(depositAmount, bank.getTotalAmount());
        long withdrawAmount = 1234;
        long withdrawResult = bank.withdraw(1, withdrawAmount);
        assertEquals(depositAmount - withdrawAmount, withdrawResult);
        assertEquals(depositAmount - withdrawAmount, bank.getAmount(1));
        assertEquals(depositAmount - withdrawAmount, bank.getTotalAmount());
    }

    public void testTotalAmount() {
        long deposit1 = 4567;
        long depositResult1 = bank.deposit(1, deposit1);
        assertEquals(deposit1, depositResult1);
        assertEquals(deposit1, bank.getTotalAmount());
        long deposit2 = 6789;
        long depositResult2 = bank.deposit(2, deposit2);
        assertEquals(deposit2, depositResult2);
        assertEquals(deposit2, bank.getAmount(2));
        assertEquals(deposit1 + deposit2, bank.getTotalAmount());
    }

    public void testTransfer() {
        int depositAmount = 9876;
        long depositResult = bank.deposit(1, depositAmount);
        assertEquals(depositAmount, depositResult);
        assertEquals(depositAmount, bank.getAmount(1));
        assertEquals(depositAmount, bank.getTotalAmount());
        long transferAmount = 5432;
        bank.transfer(1, 2, transferAmount);
        assertEquals(depositAmount - transferAmount, bank.getAmount(1));
        assertEquals(transferAmount, bank.getAmount(2));
        assertEquals(depositAmount, bank.getTotalAmount());
    }
}
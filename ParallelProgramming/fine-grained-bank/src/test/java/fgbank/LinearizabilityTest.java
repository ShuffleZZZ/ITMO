package fgbank;


import org.jetbrains.annotations.NotNull;
import org.jetbrains.kotlinx.lincheck.LinChecker;
import org.jetbrains.kotlinx.lincheck.annotations.Operation;
import org.jetbrains.kotlinx.lincheck.annotations.Param;
import org.jetbrains.kotlinx.lincheck.paramgen.*;
import org.jetbrains.kotlinx.lincheck.strategy.stress.StressCTest;
import org.jetbrains.kotlinx.lincheck.verifier.VerifierState;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

/**
 * This test checks bank implementation for linearizability
 */
@Param(name = "id", gen = IntGen.class, conf = "0:4")
@Param(name = "amount", gen = LongGen.class, conf = "1:100")
@StressCTest
public class LinearizabilityTest extends VerifierState {
    private Bank bank = new BankImpl(5);

    @Operation(params = {"id"})
    public long getAmount(int id) {
        return bank.getAmount(id);
    }

    @Operation
    public long getTotalAmount() {
        return bank.getTotalAmount();
    }

    @Operation(params = {"id", "amount"}, handleExceptionsAsResult = {IllegalStateException.class})
    public long deposit(int id, long amount) {
        return bank.deposit(id, amount);
    }

    @Operation(params = {"id", "amount"}, handleExceptionsAsResult = {IllegalStateException.class})
    public long withdraw(int id, long amount) {
        return bank.withdraw(id, amount);
    }

    @Operation(params = {"id", "id", "amount"}, handleExceptionsAsResult = {IllegalStateException.class})
    public void transfer(int idFrom, int idTo, long amount) {
        if (idFrom != idTo)
            bank.transfer(idFrom, idTo, amount);
    }

    @NotNull
    @Override
    protected Object extractState() {
        List<Long> amounts = new ArrayList<>();
        for (int i = 0; i < bank.getNumberOfAccounts(); i++)
            amounts.add(bank.getAmount(i));
        return amounts;
    }

    @Test
    public void test() {
        LinChecker.check(LinearizabilityTest.class);
    }
}
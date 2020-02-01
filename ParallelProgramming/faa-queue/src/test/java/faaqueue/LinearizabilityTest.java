package faaqueue;


import org.jetbrains.annotations.*;
import org.jetbrains.kotlinx.lincheck.*;
import org.jetbrains.kotlinx.lincheck.annotations.*;
import org.jetbrains.kotlinx.lincheck.annotations.Operation;
import org.jetbrains.kotlinx.lincheck.strategy.stress.*;
import org.jetbrains.kotlinx.lincheck.verifier.*;
import org.junit.Test;

import java.util.*;


@StressCTest
public class LinearizabilityTest extends VerifierState {
    private Queue<Integer> queue = new FAAQueue<>();

    @Operation
    public void enqueue(Integer x) {
        queue.enqueue(x);
    }

    @Operation
    public Integer dequeue() {
        return queue.dequeue();
    }

    @NotNull
    @Override
    protected Object extractState() {
        List<Integer> values = new ArrayList<>();
        while (true) {
            Integer x = queue.dequeue();
            if (x == null) break;
            values.add(x);
        }
        return values;
    }

    @Test
    public void test() {
        LinChecker.check(LinearizabilityTest.class);
    }
}
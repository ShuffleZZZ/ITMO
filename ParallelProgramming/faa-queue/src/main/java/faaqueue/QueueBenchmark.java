package faaqueue;

import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.infra.Blackhole;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.RunnerException;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;

import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;

@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Warmup(iterations = 5, time = 1, timeUnit = TimeUnit.SECONDS)
@Measurement(iterations = 10, time = 1, timeUnit = TimeUnit.SECONDS)
@BenchmarkMode(Mode.AverageTime)
@Fork(1)
@State(Scope.Benchmark)
public class QueueBenchmark {
    @Param({"50", "100"})
    public int work = 0;

    private final Queue<Integer> c = new FAAQueue<>();

    @Group("queue")
    @Benchmark
    public void enqueue() {
        Random r = ThreadLocalRandom.current();
        Blackhole.consumeCPU(r.nextInt(work));
        c.enqueue(r.nextInt());
    }

    @Group("queue")
    @Benchmark
    public Integer dequeue() {
        Random r = ThreadLocalRandom.current();
        Blackhole.consumeCPU(r.nextInt(work));
        return c.dequeue();
    }

    public static void main(String[] args) throws RunnerException {
        Options opt = new OptionsBuilder()
                .include(QueueBenchmark.class.getSimpleName())
                .forks(1)
                .threads(4) // CHANGE ME!
                .build();
        new Runner(opt).run();
    }
}

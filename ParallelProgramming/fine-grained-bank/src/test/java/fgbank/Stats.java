package fgbank;

import java.util.Locale;

/**
 * @author Roman Elizarov
 */
class Stats {
    private int n;
    private double mean;
    private double nvar;

    public void add(long x) {
        n++;
        double prev = mean;
        mean += (x - prev) / n;
        nvar += (x - prev) * (x - mean);
    }

    public int n() {
        return n;
    }

    public double mean() {
        return mean;
    }

    public double dev() {
        return Math.sqrt(nvar / (n - 1));
    }

    @Override
    public String toString() {
        return String.format(Locale.US, "%,.0f +- %,.0f", mean(), dev());
    }
}

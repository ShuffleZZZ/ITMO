import org.jetbrains.annotations.NotNull;

/**
 * В теле класса решения разрешено использовать только финальные переменные типа RegularInt.
 * Нельзя volatile, нельзя другие типы, нельзя блокировки, нельзя лазить в глобальные переменные.
 */
public class Solution implements MonotonicClock {
    private final RegularInt d1 = new RegularInt(0);
    private final RegularInt d2 = new RegularInt(0);
    private final RegularInt d3 = new RegularInt(0);

    private final RegularInt c1 = new RegularInt(0);
    private final RegularInt c2 = new RegularInt(0);

    @Override
    public void write(@NotNull Time time) {
        // write left-to-right
        d1.setValue(time.getD1());
        d2.setValue(time.getD2());
        d3.setValue(time.getD3());

        // write right-to-left
        c2.setValue(time.getD2());
        c1.setValue(time.getD1());
    }

    @NotNull
    @Override
    public Time read() {
        // read left-to-right
        int c1Value = c1.getValue();
        int c2Value = c2.getValue();

        // read right-to-left
        int d3Value = d3.getValue();
        int d2Value = d2.getValue();
        int d1Value = d1.getValue();

        return new Time(d1Value, c1Value == d1Value ? d2Value : 0, c1Value == d1Value && c2Value == d2Value ? d3Value : 0);
    }
}

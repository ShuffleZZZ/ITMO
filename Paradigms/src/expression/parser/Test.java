package expression.parser;

public class Test {
    public static void main(String args[]) throws Exception {
        ExpressionParser res = new ExpressionParser();
        System.out.print(res.parse("(- - - x^1883669513)|(- x^1681810605)").evaluate(0, 0, 0));
    }
}
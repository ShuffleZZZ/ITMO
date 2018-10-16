package expression.parser;

import expression.exceptions.*;

public interface Parser {
    TripleExpression parse(String expression) throws Exception;
}
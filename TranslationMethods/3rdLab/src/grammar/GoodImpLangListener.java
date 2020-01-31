// Generated from C:/Users/User/ITMO/TranslationMethods/3rdLab/src/grammar\GoodImpLang.g4 by ANTLR 4.7.2
package grammar;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link GoodImpLangParser}.
 */
public interface GoodImpLangListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(GoodImpLangParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(GoodImpLangParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#expressions}.
	 * @param ctx the parse tree
	 */
	void enterExpressions(GoodImpLangParser.ExpressionsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#expressions}.
	 * @param ctx the parse tree
	 */
	void exitExpressions(GoodImpLangParser.ExpressionsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(GoodImpLangParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(GoodImpLangParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDeclaration(GoodImpLangParser.FunctionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDeclaration(GoodImpLangParser.FunctionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#line}.
	 * @param ctx the parse tree
	 */
	void enterLine(GoodImpLangParser.LineContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#line}.
	 * @param ctx the parse tree
	 */
	void exitLine(GoodImpLangParser.LineContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#functionName}.
	 * @param ctx the parse tree
	 */
	void enterFunctionName(GoodImpLangParser.FunctionNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#functionName}.
	 * @param ctx the parse tree
	 */
	void exitFunctionName(GoodImpLangParser.FunctionNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(GoodImpLangParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(GoodImpLangParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#scope}.
	 * @param ctx the parse tree
	 */
	void enterScope(GoodImpLangParser.ScopeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#scope}.
	 * @param ctx the parse tree
	 */
	void exitScope(GoodImpLangParser.ScopeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void enterReturnStatement(GoodImpLangParser.ReturnStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void exitReturnStatement(GoodImpLangParser.ReturnStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#args}.
	 * @param ctx the parse tree
	 */
	void enterArgs(GoodImpLangParser.ArgsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#args}.
	 * @param ctx the parse tree
	 */
	void exitArgs(GoodImpLangParser.ArgsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#multiArgs}.
	 * @param ctx the parse tree
	 */
	void enterMultiArgs(GoodImpLangParser.MultiArgsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#multiArgs}.
	 * @param ctx the parse tree
	 */
	void exitMultiArgs(GoodImpLangParser.MultiArgsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#multiArg}.
	 * @param ctx the parse tree
	 */
	void enterMultiArg(GoodImpLangParser.MultiArgContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#multiArg}.
	 * @param ctx the parse tree
	 */
	void exitMultiArg(GoodImpLangParser.MultiArgContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#arg}.
	 * @param ctx the parse tree
	 */
	void enterArg(GoodImpLangParser.ArgContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#arg}.
	 * @param ctx the parse tree
	 */
	void exitArg(GoodImpLangParser.ArgContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#flow}.
	 * @param ctx the parse tree
	 */
	void enterFlow(GoodImpLangParser.FlowContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#flow}.
	 * @param ctx the parse tree
	 */
	void exitFlow(GoodImpLangParser.FlowContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(GoodImpLangParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(GoodImpLangParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#assignment}.
	 * @param ctx the parse tree
	 */
	void enterAssignment(GoodImpLangParser.AssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#assignment}.
	 * @param ctx the parse tree
	 */
	void exitAssignment(GoodImpLangParser.AssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#function}.
	 * @param ctx the parse tree
	 */
	void enterFunction(GoodImpLangParser.FunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#function}.
	 * @param ctx the parse tree
	 */
	void exitFunction(GoodImpLangParser.FunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#fargs}.
	 * @param ctx the parse tree
	 */
	void enterFargs(GoodImpLangParser.FargsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#fargs}.
	 * @param ctx the parse tree
	 */
	void exitFargs(GoodImpLangParser.FargsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#farg}.
	 * @param ctx the parse tree
	 */
	void enterFarg(GoodImpLangParser.FargContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#farg}.
	 * @param ctx the parse tree
	 */
	void exitFarg(GoodImpLangParser.FargContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#multifargs}.
	 * @param ctx the parse tree
	 */
	void enterMultifargs(GoodImpLangParser.MultifargsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#multifargs}.
	 * @param ctx the parse tree
	 */
	void exitMultifargs(GoodImpLangParser.MultifargsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#multifarg}.
	 * @param ctx the parse tree
	 */
	void enterMultifarg(GoodImpLangParser.MultifargContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#multifarg}.
	 * @param ctx the parse tree
	 */
	void exitMultifarg(GoodImpLangParser.MultifargContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#operation}.
	 * @param ctx the parse tree
	 */
	void enterOperation(GoodImpLangParser.OperationContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#operation}.
	 * @param ctx the parse tree
	 */
	void exitOperation(GoodImpLangParser.OperationContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#value}.
	 * @param ctx the parse tree
	 */
	void enterValue(GoodImpLangParser.ValueContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#value}.
	 * @param ctx the parse tree
	 */
	void exitValue(GoodImpLangParser.ValueContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteral(GoodImpLangParser.LiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteral(GoodImpLangParser.LiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#numberLiteral}.
	 * @param ctx the parse tree
	 */
	void enterNumberLiteral(GoodImpLangParser.NumberLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#numberLiteral}.
	 * @param ctx the parse tree
	 */
	void exitNumberLiteral(GoodImpLangParser.NumberLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#doubleLiteral}.
	 * @param ctx the parse tree
	 */
	void enterDoubleLiteral(GoodImpLangParser.DoubleLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#doubleLiteral}.
	 * @param ctx the parse tree
	 */
	void exitDoubleLiteral(GoodImpLangParser.DoubleLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#boolLiteral}.
	 * @param ctx the parse tree
	 */
	void enterBoolLiteral(GoodImpLangParser.BoolLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#boolLiteral}.
	 * @param ctx the parse tree
	 */
	void exitBoolLiteral(GoodImpLangParser.BoolLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#stringLiteral}.
	 * @param ctx the parse tree
	 */
	void enterStringLiteral(GoodImpLangParser.StringLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#stringLiteral}.
	 * @param ctx the parse tree
	 */
	void exitStringLiteral(GoodImpLangParser.StringLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#name}.
	 * @param ctx the parse tree
	 */
	void enterName(GoodImpLangParser.NameContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#name}.
	 * @param ctx the parse tree
	 */
	void exitName(GoodImpLangParser.NameContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(GoodImpLangParser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(GoodImpLangParser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#whileLoop}.
	 * @param ctx the parse tree
	 */
	void enterWhileLoop(GoodImpLangParser.WhileLoopContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#whileLoop}.
	 * @param ctx the parse tree
	 */
	void exitWhileLoop(GoodImpLangParser.WhileLoopContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#forLoop}.
	 * @param ctx the parse tree
	 */
	void enterForLoop(GoodImpLangParser.ForLoopContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#forLoop}.
	 * @param ctx the parse tree
	 */
	void exitForLoop(GoodImpLangParser.ForLoopContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(GoodImpLangParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(GoodImpLangParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link GoodImpLangParser#predicate}.
	 * @param ctx the parse tree
	 */
	void enterPredicate(GoodImpLangParser.PredicateContext ctx);
	/**
	 * Exit a parse tree produced by {@link GoodImpLangParser#predicate}.
	 * @param ctx the parse tree
	 */
	void exitPredicate(GoodImpLangParser.PredicateContext ctx);
}
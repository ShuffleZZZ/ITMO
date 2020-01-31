// Generated from C:/Users/User/ITMO/TranslationMethods/3rdLab/src/grammar\GoodImpLang.g4 by ANTLR 4.7.2
package grammar;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link GoodImpLangParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface GoodImpLangVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(GoodImpLangParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#expressions}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpressions(GoodImpLangParser.ExpressionsContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression(GoodImpLangParser.ExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#functionDeclaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionDeclaration(GoodImpLangParser.FunctionDeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#line}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLine(GoodImpLangParser.LineContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#functionName}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionName(GoodImpLangParser.FunctionNameContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType(GoodImpLangParser.TypeContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#scope}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitScope(GoodImpLangParser.ScopeContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#returnStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReturnStatement(GoodImpLangParser.ReturnStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#args}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgs(GoodImpLangParser.ArgsContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#multiArgs}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiArgs(GoodImpLangParser.MultiArgsContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#multiArg}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiArg(GoodImpLangParser.MultiArgContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#arg}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArg(GoodImpLangParser.ArgContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#flow}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFlow(GoodImpLangParser.FlowContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDeclaration(GoodImpLangParser.DeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#assignment}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignment(GoodImpLangParser.AssignmentContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#function}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction(GoodImpLangParser.FunctionContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#fargs}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFargs(GoodImpLangParser.FargsContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#farg}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFarg(GoodImpLangParser.FargContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#multifargs}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultifargs(GoodImpLangParser.MultifargsContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#multifarg}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultifarg(GoodImpLangParser.MultifargContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#operation}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOperation(GoodImpLangParser.OperationContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#value}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitValue(GoodImpLangParser.ValueContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#literal}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral(GoodImpLangParser.LiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#numberLiteral}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNumberLiteral(GoodImpLangParser.NumberLiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#doubleLiteral}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDoubleLiteral(GoodImpLangParser.DoubleLiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#boolLiteral}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBoolLiteral(GoodImpLangParser.BoolLiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#stringLiteral}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStringLiteral(GoodImpLangParser.StringLiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#name}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitName(GoodImpLangParser.NameContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#ifStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIfStatement(GoodImpLangParser.IfStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#whileLoop}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWhileLoop(GoodImpLangParser.WhileLoopContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#forLoop}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitForLoop(GoodImpLangParser.ForLoopContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(GoodImpLangParser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link GoodImpLangParser#predicate}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPredicate(GoodImpLangParser.PredicateContext ctx);
}
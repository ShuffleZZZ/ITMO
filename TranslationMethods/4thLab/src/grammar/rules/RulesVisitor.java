// Generated from C:/Users/User/ITMO/TranslationMethods/4thLab/src/grammar/rules\Rules.g4 by ANTLR 4.7.2
package grammar.rules;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link RulesParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface RulesVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link RulesParser#metaGrammar}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetaGrammar(RulesParser.MetaGrammarContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#grammarName}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGrammarName(RulesParser.GrammarNameContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#header}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitHeader(RulesParser.HeaderContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#fields}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFields(RulesParser.FieldsContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#field}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitField(RulesParser.FieldContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#rules}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRules(RulesParser.RulesContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#grammarRule}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGrammarRule(RulesParser.GrammarRuleContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#tokenRule}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTokenRule(RulesParser.TokenRuleContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#syntaxRule}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSyntaxRule(RulesParser.SyntaxRuleContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#name}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitName(RulesParser.NameContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#names}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNames(RulesParser.NamesContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#moreNames}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMoreNames(RulesParser.MoreNamesContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#code}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCode(RulesParser.CodeContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#argument}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgument(RulesParser.ArgumentContext ctx);
	/**
	 * Visit a parse tree produced by {@link RulesParser#argumentWithType}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgumentWithType(RulesParser.ArgumentWithTypeContext ctx);
}
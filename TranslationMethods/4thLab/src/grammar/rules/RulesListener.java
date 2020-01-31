// Generated from C:/Users/User/ITMO/TranslationMethods/4thLab/src/grammar/rules\Rules.g4 by ANTLR 4.7.2
package grammar.rules;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link RulesParser}.
 */
public interface RulesListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link RulesParser#metaGrammar}.
	 * @param ctx the parse tree
	 */
	void enterMetaGrammar(RulesParser.MetaGrammarContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#metaGrammar}.
	 * @param ctx the parse tree
	 */
	void exitMetaGrammar(RulesParser.MetaGrammarContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#grammarName}.
	 * @param ctx the parse tree
	 */
	void enterGrammarName(RulesParser.GrammarNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#grammarName}.
	 * @param ctx the parse tree
	 */
	void exitGrammarName(RulesParser.GrammarNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#header}.
	 * @param ctx the parse tree
	 */
	void enterHeader(RulesParser.HeaderContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#header}.
	 * @param ctx the parse tree
	 */
	void exitHeader(RulesParser.HeaderContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#fields}.
	 * @param ctx the parse tree
	 */
	void enterFields(RulesParser.FieldsContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#fields}.
	 * @param ctx the parse tree
	 */
	void exitFields(RulesParser.FieldsContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#field}.
	 * @param ctx the parse tree
	 */
	void enterField(RulesParser.FieldContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#field}.
	 * @param ctx the parse tree
	 */
	void exitField(RulesParser.FieldContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#rules}.
	 * @param ctx the parse tree
	 */
	void enterRules(RulesParser.RulesContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#rules}.
	 * @param ctx the parse tree
	 */
	void exitRules(RulesParser.RulesContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#grammarRule}.
	 * @param ctx the parse tree
	 */
	void enterGrammarRule(RulesParser.GrammarRuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#grammarRule}.
	 * @param ctx the parse tree
	 */
	void exitGrammarRule(RulesParser.GrammarRuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#tokenRule}.
	 * @param ctx the parse tree
	 */
	void enterTokenRule(RulesParser.TokenRuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#tokenRule}.
	 * @param ctx the parse tree
	 */
	void exitTokenRule(RulesParser.TokenRuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#syntaxRule}.
	 * @param ctx the parse tree
	 */
	void enterSyntaxRule(RulesParser.SyntaxRuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#syntaxRule}.
	 * @param ctx the parse tree
	 */
	void exitSyntaxRule(RulesParser.SyntaxRuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#name}.
	 * @param ctx the parse tree
	 */
	void enterName(RulesParser.NameContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#name}.
	 * @param ctx the parse tree
	 */
	void exitName(RulesParser.NameContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#names}.
	 * @param ctx the parse tree
	 */
	void enterNames(RulesParser.NamesContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#names}.
	 * @param ctx the parse tree
	 */
	void exitNames(RulesParser.NamesContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#moreNames}.
	 * @param ctx the parse tree
	 */
	void enterMoreNames(RulesParser.MoreNamesContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#moreNames}.
	 * @param ctx the parse tree
	 */
	void exitMoreNames(RulesParser.MoreNamesContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#code}.
	 * @param ctx the parse tree
	 */
	void enterCode(RulesParser.CodeContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#code}.
	 * @param ctx the parse tree
	 */
	void exitCode(RulesParser.CodeContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#argument}.
	 * @param ctx the parse tree
	 */
	void enterArgument(RulesParser.ArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#argument}.
	 * @param ctx the parse tree
	 */
	void exitArgument(RulesParser.ArgumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link RulesParser#argumentWithType}.
	 * @param ctx the parse tree
	 */
	void enterArgumentWithType(RulesParser.ArgumentWithTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link RulesParser#argumentWithType}.
	 * @param ctx the parse tree
	 */
	void exitArgumentWithType(RulesParser.ArgumentWithTypeContext ctx);
}
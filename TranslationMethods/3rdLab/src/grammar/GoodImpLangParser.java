// Generated from C:/Users/User/ITMO/TranslationMethods/3rdLab/src/grammar\GoodImpLang.g4 by ANTLR 4.7.2
package grammar;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class GoodImpLangParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		COLON=1, DOT=2, COMMA=3, OPEN_BRACKET=4, CLOSE_BRACKET=5, OPEN_SCOPE=6, 
		CLOSE_SCOPE=7, LINE_SEPARATOR=8, NUMBER=9, DOUBLE=10, STRING=11, BOOL=12, 
		IF=13, WHILE=14, FOR=15, IN=16, FUN=17, RETURN=18, MULTIPLY=19, DIVIDE=20, 
		PLUS=21, MINUS=22, MODULE=23, ASSIGN=24, AND=25, OR=26, XOR=27, NOT=28, 
		LESS_OP=29, MORE_OP=30, LESS_OR_EQUAL=31, MORE_OR_EQUAL=32, EQUALS=33, 
		NOT_EQUALS=34, INT_TYPE=35, LONG_TYPE=36, BOOL_TYPE=37, STRING_TYPE=38, 
		DOUBLE_TYPE=39, NEXT_INT=40, NEXT_LONG=41, NEXT_BOOL=42, NEXT_DOUBLE=43, 
		NEXT_LINE=44, PRINT=45, IDENTIFIER=46, WHITESPACE=47;
	public static final int
		RULE_program = 0, RULE_expressions = 1, RULE_expression = 2, RULE_functionDeclaration = 3, 
		RULE_line = 4, RULE_functionName = 5, RULE_type = 6, RULE_scope = 7, RULE_returnStatement = 8, 
		RULE_args = 9, RULE_multiArgs = 10, RULE_multiArg = 11, RULE_arg = 12, 
		RULE_flow = 13, RULE_declaration = 14, RULE_assignment = 15, RULE_function = 16, 
		RULE_fargs = 17, RULE_farg = 18, RULE_multifargs = 19, RULE_multifarg = 20, 
		RULE_operation = 21, RULE_value = 22, RULE_literal = 23, RULE_numberLiteral = 24, 
		RULE_doubleLiteral = 25, RULE_boolLiteral = 26, RULE_stringLiteral = 27, 
		RULE_name = 28, RULE_ifStatement = 29, RULE_whileLoop = 30, RULE_forLoop = 31, 
		RULE_statement = 32, RULE_predicate = 33;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "expressions", "expression", "functionDeclaration", "line", 
			"functionName", "type", "scope", "returnStatement", "args", "multiArgs", 
			"multiArg", "arg", "flow", "declaration", "assignment", "function", "fargs", 
			"farg", "multifargs", "multifarg", "operation", "value", "literal", "numberLiteral", 
			"doubleLiteral", "boolLiteral", "stringLiteral", "name", "ifStatement", 
			"whileLoop", "forLoop", "statement", "predicate"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "':'", "'.'", "','", "'('", "')'", "'{'", "'}'", "'\n'", null, 
			null, null, null, "'if'", "'while'", "'for'", "'in'", "'fun'", "'return'", 
			"'*'", "'/'", "'+'", "'-'", "'%'", null, null, null, null, null, null, 
			null, null, null, null, null, "'Int'", "'Long'", "'Bool'", "'String'", 
			"'Double'", "'nextInt'", "'nextLong'", "'nextBool'", "'nextDouble'", 
			"'nextLine'", "'print'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "COLON", "DOT", "COMMA", "OPEN_BRACKET", "CLOSE_BRACKET", "OPEN_SCOPE", 
			"CLOSE_SCOPE", "LINE_SEPARATOR", "NUMBER", "DOUBLE", "STRING", "BOOL", 
			"IF", "WHILE", "FOR", "IN", "FUN", "RETURN", "MULTIPLY", "DIVIDE", "PLUS", 
			"MINUS", "MODULE", "ASSIGN", "AND", "OR", "XOR", "NOT", "LESS_OP", "MORE_OP", 
			"LESS_OR_EQUAL", "MORE_OR_EQUAL", "EQUALS", "NOT_EQUALS", "INT_TYPE", 
			"LONG_TYPE", "BOOL_TYPE", "STRING_TYPE", "DOUBLE_TYPE", "NEXT_INT", "NEXT_LONG", 
			"NEXT_BOOL", "NEXT_DOUBLE", "NEXT_LINE", "PRINT", "IDENTIFIER", "WHITESPACE"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "GoodImpLang.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public GoodImpLangParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class ProgramContext extends ParserRuleContext {
		public ExpressionsContext expressions() {
			return getRuleContext(ExpressionsContext.class,0);
		}
		public TerminalNode EOF() { return getToken(GoodImpLangParser.EOF, 0); }
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitProgram(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitProgram(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(68);
			expressions();
			setState(69);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionsContext extends ParserRuleContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public ExpressionsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expressions; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterExpressions(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitExpressions(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitExpressions(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionsContext expressions() throws RecognitionException {
		ExpressionsContext _localctx = new ExpressionsContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_expressions);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(72); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(71);
				expression();
				}
				}
				setState(74); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LINE_SEPARATOR) | (1L << IF) | (1L << WHILE) | (1L << FOR) | (1L << FUN) | (1L << NEXT_INT) | (1L << NEXT_LONG) | (1L << NEXT_BOOL) | (1L << NEXT_DOUBLE) | (1L << NEXT_LINE) | (1L << PRINT) | (1L << IDENTIFIER))) != 0) );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionContext extends ParserRuleContext {
		public FunctionDeclarationContext functionDeclaration() {
			return getRuleContext(FunctionDeclarationContext.class,0);
		}
		public LineContext line() {
			return getRuleContext(LineContext.class,0);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitExpression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitExpression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_expression);
		try {
			setState(78);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case FUN:
				enterOuterAlt(_localctx, 1);
				{
				setState(76);
				functionDeclaration();
				}
				break;
			case LINE_SEPARATOR:
			case IF:
			case WHILE:
			case FOR:
			case NEXT_INT:
			case NEXT_LONG:
			case NEXT_BOOL:
			case NEXT_DOUBLE:
			case NEXT_LINE:
			case PRINT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				setState(77);
				line();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionDeclarationContext extends ParserRuleContext {
		public TerminalNode FUN() { return getToken(GoodImpLangParser.FUN, 0); }
		public FunctionNameContext functionName() {
			return getRuleContext(FunctionNameContext.class,0);
		}
		public TerminalNode OPEN_BRACKET() { return getToken(GoodImpLangParser.OPEN_BRACKET, 0); }
		public ArgsContext args() {
			return getRuleContext(ArgsContext.class,0);
		}
		public TerminalNode CLOSE_BRACKET() { return getToken(GoodImpLangParser.CLOSE_BRACKET, 0); }
		public ScopeContext scope() {
			return getRuleContext(ScopeContext.class,0);
		}
		public TerminalNode COLON() { return getToken(GoodImpLangParser.COLON, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public FunctionDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionDeclaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterFunctionDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitFunctionDeclaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitFunctionDeclaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionDeclarationContext functionDeclaration() throws RecognitionException {
		FunctionDeclarationContext _localctx = new FunctionDeclarationContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_functionDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(80);
			match(FUN);
			setState(81);
			functionName();
			setState(82);
			match(OPEN_BRACKET);
			setState(83);
			args();
			setState(84);
			match(CLOSE_BRACKET);
			setState(87);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COLON) {
				{
				setState(85);
				match(COLON);
				setState(86);
				type();
				}
			}

			setState(89);
			scope();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LineContext extends ParserRuleContext {
		public FlowContext flow() {
			return getRuleContext(FlowContext.class,0);
		}
		public TerminalNode LINE_SEPARATOR() { return getToken(GoodImpLangParser.LINE_SEPARATOR, 0); }
		public DeclarationContext declaration() {
			return getRuleContext(DeclarationContext.class,0);
		}
		public AssignmentContext assignment() {
			return getRuleContext(AssignmentContext.class,0);
		}
		public FunctionContext function() {
			return getRuleContext(FunctionContext.class,0);
		}
		public LineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_line; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterLine(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitLine(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitLine(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LineContext line() throws RecognitionException {
		LineContext _localctx = new LineContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_line);
		try {
			setState(99);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IF:
			case WHILE:
			case FOR:
				enterOuterAlt(_localctx, 1);
				{
				setState(91);
				flow();
				}
				break;
			case LINE_SEPARATOR:
			case NEXT_INT:
			case NEXT_LONG:
			case NEXT_BOOL:
			case NEXT_DOUBLE:
			case NEXT_LINE:
			case PRINT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(96);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
				case 1:
					{
					}
					break;
				case 2:
					{
					setState(93);
					declaration();
					}
					break;
				case 3:
					{
					setState(94);
					assignment();
					}
					break;
				case 4:
					{
					setState(95);
					function();
					}
					break;
				}
				setState(98);
				match(LINE_SEPARATOR);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionNameContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(GoodImpLangParser.IDENTIFIER, 0); }
		public TerminalNode NEXT_INT() { return getToken(GoodImpLangParser.NEXT_INT, 0); }
		public TerminalNode NEXT_BOOL() { return getToken(GoodImpLangParser.NEXT_BOOL, 0); }
		public TerminalNode NEXT_LONG() { return getToken(GoodImpLangParser.NEXT_LONG, 0); }
		public TerminalNode NEXT_DOUBLE() { return getToken(GoodImpLangParser.NEXT_DOUBLE, 0); }
		public TerminalNode NEXT_LINE() { return getToken(GoodImpLangParser.NEXT_LINE, 0); }
		public TerminalNode PRINT() { return getToken(GoodImpLangParser.PRINT, 0); }
		public FunctionNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionName; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterFunctionName(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitFunctionName(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitFunctionName(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionNameContext functionName() throws RecognitionException {
		FunctionNameContext _localctx = new FunctionNameContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_functionName);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(101);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << NEXT_INT) | (1L << NEXT_LONG) | (1L << NEXT_BOOL) | (1L << NEXT_DOUBLE) | (1L << NEXT_LINE) | (1L << PRINT) | (1L << IDENTIFIER))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TypeContext extends ParserRuleContext {
		public TerminalNode INT_TYPE() { return getToken(GoodImpLangParser.INT_TYPE, 0); }
		public TerminalNode LONG_TYPE() { return getToken(GoodImpLangParser.LONG_TYPE, 0); }
		public TerminalNode DOUBLE_TYPE() { return getToken(GoodImpLangParser.DOUBLE_TYPE, 0); }
		public TerminalNode BOOL_TYPE() { return getToken(GoodImpLangParser.BOOL_TYPE, 0); }
		public TerminalNode STRING_TYPE() { return getToken(GoodImpLangParser.STRING_TYPE, 0); }
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitType(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitType(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(103);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << INT_TYPE) | (1L << LONG_TYPE) | (1L << BOOL_TYPE) | (1L << STRING_TYPE) | (1L << DOUBLE_TYPE))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ScopeContext extends ParserRuleContext {
		public TerminalNode OPEN_SCOPE() { return getToken(GoodImpLangParser.OPEN_SCOPE, 0); }
		public TerminalNode CLOSE_SCOPE() { return getToken(GoodImpLangParser.CLOSE_SCOPE, 0); }
		public List<LineContext> line() {
			return getRuleContexts(LineContext.class);
		}
		public LineContext line(int i) {
			return getRuleContext(LineContext.class,i);
		}
		public List<ReturnStatementContext> returnStatement() {
			return getRuleContexts(ReturnStatementContext.class);
		}
		public ReturnStatementContext returnStatement(int i) {
			return getRuleContext(ReturnStatementContext.class,i);
		}
		public List<TerminalNode> LINE_SEPARATOR() { return getTokens(GoodImpLangParser.LINE_SEPARATOR); }
		public TerminalNode LINE_SEPARATOR(int i) {
			return getToken(GoodImpLangParser.LINE_SEPARATOR, i);
		}
		public ScopeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_scope; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterScope(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitScope(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitScope(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ScopeContext scope() throws RecognitionException {
		ScopeContext _localctx = new ScopeContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_scope);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(105);
			match(OPEN_SCOPE);
			setState(112);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LINE_SEPARATOR) | (1L << IF) | (1L << WHILE) | (1L << FOR) | (1L << RETURN) | (1L << NEXT_INT) | (1L << NEXT_LONG) | (1L << NEXT_BOOL) | (1L << NEXT_DOUBLE) | (1L << NEXT_LINE) | (1L << PRINT) | (1L << IDENTIFIER))) != 0)) {
				{
				setState(110);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case LINE_SEPARATOR:
				case IF:
				case WHILE:
				case FOR:
				case NEXT_INT:
				case NEXT_LONG:
				case NEXT_BOOL:
				case NEXT_DOUBLE:
				case NEXT_LINE:
				case PRINT:
				case IDENTIFIER:
					{
					setState(106);
					line();
					}
					break;
				case RETURN:
					{
					{
					setState(107);
					returnStatement();
					setState(108);
					match(LINE_SEPARATOR);
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(114);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(115);
			match(CLOSE_SCOPE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ReturnStatementContext extends ParserRuleContext {
		public TerminalNode RETURN() { return getToken(GoodImpLangParser.RETURN, 0); }
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public ReturnStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_returnStatement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterReturnStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitReturnStatement(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitReturnStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ReturnStatementContext returnStatement() throws RecognitionException {
		ReturnStatementContext _localctx = new ReturnStatementContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_returnStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(117);
			match(RETURN);
			setState(118);
			value();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArgsContext extends ParserRuleContext {
		public ArgContext arg() {
			return getRuleContext(ArgContext.class,0);
		}
		public MultiArgsContext multiArgs() {
			return getRuleContext(MultiArgsContext.class,0);
		}
		public ArgsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_args; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterArgs(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitArgs(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitArgs(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArgsContext args() throws RecognitionException {
		ArgsContext _localctx = new ArgsContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_args);
		try {
			setState(123);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(121);
				arg();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(122);
				multiArgs();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MultiArgsContext extends ParserRuleContext {
		public ArgContext arg() {
			return getRuleContext(ArgContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(GoodImpLangParser.COMMA, 0); }
		public MultiArgContext multiArg() {
			return getRuleContext(MultiArgContext.class,0);
		}
		public MultiArgsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiArgs; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterMultiArgs(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitMultiArgs(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitMultiArgs(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MultiArgsContext multiArgs() throws RecognitionException {
		MultiArgsContext _localctx = new MultiArgsContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_multiArgs);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(125);
			arg();
			setState(126);
			match(COMMA);
			setState(127);
			multiArg();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MultiArgContext extends ParserRuleContext {
		public ArgContext arg() {
			return getRuleContext(ArgContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(GoodImpLangParser.COMMA, 0); }
		public MultiArgContext multiArg() {
			return getRuleContext(MultiArgContext.class,0);
		}
		public MultiArgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiArg; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterMultiArg(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitMultiArg(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitMultiArg(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MultiArgContext multiArg() throws RecognitionException {
		MultiArgContext _localctx = new MultiArgContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_multiArg);
		try {
			setState(134);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(129);
				arg();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(130);
				arg();
				setState(131);
				match(COMMA);
				setState(132);
				multiArg();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArgContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public TerminalNode COLON() { return getToken(GoodImpLangParser.COLON, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ArgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arg; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterArg(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitArg(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitArg(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArgContext arg() throws RecognitionException {
		ArgContext _localctx = new ArgContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_arg);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(136);
			name();
			setState(137);
			match(COLON);
			setState(138);
			type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FlowContext extends ParserRuleContext {
		public ForLoopContext forLoop() {
			return getRuleContext(ForLoopContext.class,0);
		}
		public WhileLoopContext whileLoop() {
			return getRuleContext(WhileLoopContext.class,0);
		}
		public IfStatementContext ifStatement() {
			return getRuleContext(IfStatementContext.class,0);
		}
		public FlowContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_flow; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterFlow(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitFlow(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitFlow(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FlowContext flow() throws RecognitionException {
		FlowContext _localctx = new FlowContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_flow);
		try {
			setState(143);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case FOR:
				enterOuterAlt(_localctx, 1);
				{
				setState(140);
				forLoop();
				}
				break;
			case WHILE:
				enterOuterAlt(_localctx, 2);
				{
				setState(141);
				whileLoop();
				}
				break;
			case IF:
				enterOuterAlt(_localctx, 3);
				{
				setState(142);
				ifStatement();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclarationContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public TerminalNode COLON() { return getToken(GoodImpLangParser.COLON, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public DeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitDeclaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitDeclaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DeclarationContext declaration() throws RecognitionException {
		DeclarationContext _localctx = new DeclarationContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_declaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(145);
			name();
			setState(146);
			match(COLON);
			setState(147);
			type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AssignmentContext extends ParserRuleContext {
		public List<NameContext> name() {
			return getRuleContexts(NameContext.class);
		}
		public NameContext name(int i) {
			return getRuleContext(NameContext.class,i);
		}
		public TerminalNode ASSIGN() { return getToken(GoodImpLangParser.ASSIGN, 0); }
		public List<ValueContext> value() {
			return getRuleContexts(ValueContext.class);
		}
		public ValueContext value(int i) {
			return getRuleContext(ValueContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(GoodImpLangParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(GoodImpLangParser.COMMA, i);
		}
		public AssignmentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterAssignment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitAssignment(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitAssignment(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssignmentContext assignment() throws RecognitionException {
		AssignmentContext _localctx = new AssignmentContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_assignment);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(149);
			name();
			setState(154);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(150);
				match(COMMA);
				setState(151);
				name();
				}
				}
				setState(156);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(157);
			match(ASSIGN);
			setState(158);
			value();
			setState(163);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(159);
				match(COMMA);
				setState(160);
				value();
				}
				}
				setState(165);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionContext extends ParserRuleContext {
		public FunctionNameContext functionName() {
			return getRuleContext(FunctionNameContext.class,0);
		}
		public TerminalNode OPEN_BRACKET() { return getToken(GoodImpLangParser.OPEN_BRACKET, 0); }
		public FargsContext fargs() {
			return getRuleContext(FargsContext.class,0);
		}
		public TerminalNode CLOSE_BRACKET() { return getToken(GoodImpLangParser.CLOSE_BRACKET, 0); }
		public FunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterFunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitFunction(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitFunction(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionContext function() throws RecognitionException {
		FunctionContext _localctx = new FunctionContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_function);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(166);
			functionName();
			setState(167);
			match(OPEN_BRACKET);
			setState(168);
			fargs();
			setState(169);
			match(CLOSE_BRACKET);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FargsContext extends ParserRuleContext {
		public FargContext farg() {
			return getRuleContext(FargContext.class,0);
		}
		public MultifargsContext multifargs() {
			return getRuleContext(MultifargsContext.class,0);
		}
		public FargsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fargs; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterFargs(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitFargs(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitFargs(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FargsContext fargs() throws RecognitionException {
		FargsContext _localctx = new FargsContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_fargs);
		try {
			setState(174);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(172);
				farg();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(173);
				multifargs();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FargContext extends ParserRuleContext {
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public FargContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_farg; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterFarg(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitFarg(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitFarg(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FargContext farg() throws RecognitionException {
		FargContext _localctx = new FargContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_farg);
		try {
			setState(178);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(176);
				name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(177);
				value();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MultifargsContext extends ParserRuleContext {
		public FargContext farg() {
			return getRuleContext(FargContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(GoodImpLangParser.COMMA, 0); }
		public MultifargContext multifarg() {
			return getRuleContext(MultifargContext.class,0);
		}
		public MultifargsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multifargs; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterMultifargs(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitMultifargs(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitMultifargs(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MultifargsContext multifargs() throws RecognitionException {
		MultifargsContext _localctx = new MultifargsContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_multifargs);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(180);
			farg();
			setState(181);
			match(COMMA);
			setState(182);
			multifarg();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MultifargContext extends ParserRuleContext {
		public FargContext farg() {
			return getRuleContext(FargContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(GoodImpLangParser.COMMA, 0); }
		public MultifargContext multifarg() {
			return getRuleContext(MultifargContext.class,0);
		}
		public MultifargContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multifarg; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterMultifarg(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitMultifarg(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitMultifarg(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MultifargContext multifarg() throws RecognitionException {
		MultifargContext _localctx = new MultifargContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_multifarg);
		try {
			setState(189);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(184);
				farg();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(185);
				farg();
				setState(186);
				match(COMMA);
				setState(187);
				multifarg();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class OperationContext extends ParserRuleContext {
		public TerminalNode PLUS() { return getToken(GoodImpLangParser.PLUS, 0); }
		public TerminalNode MINUS() { return getToken(GoodImpLangParser.MINUS, 0); }
		public TerminalNode MULTIPLY() { return getToken(GoodImpLangParser.MULTIPLY, 0); }
		public TerminalNode DIVIDE() { return getToken(GoodImpLangParser.DIVIDE, 0); }
		public TerminalNode MODULE() { return getToken(GoodImpLangParser.MODULE, 0); }
		public TerminalNode AND() { return getToken(GoodImpLangParser.AND, 0); }
		public TerminalNode XOR() { return getToken(GoodImpLangParser.XOR, 0); }
		public TerminalNode OR() { return getToken(GoodImpLangParser.OR, 0); }
		public OperationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_operation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterOperation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitOperation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitOperation(this);
			else return visitor.visitChildren(this);
		}
	}

	public final OperationContext operation() throws RecognitionException {
		OperationContext _localctx = new OperationContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_operation);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(191);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << MULTIPLY) | (1L << DIVIDE) | (1L << PLUS) | (1L << MINUS) | (1L << MODULE) | (1L << AND) | (1L << OR) | (1L << XOR))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ValueContext extends ParserRuleContext {
		public List<NameContext> name() {
			return getRuleContexts(NameContext.class);
		}
		public NameContext name(int i) {
			return getRuleContext(NameContext.class,i);
		}
		public List<FunctionContext> function() {
			return getRuleContexts(FunctionContext.class);
		}
		public FunctionContext function(int i) {
			return getRuleContext(FunctionContext.class,i);
		}
		public List<LiteralContext> literal() {
			return getRuleContexts(LiteralContext.class);
		}
		public LiteralContext literal(int i) {
			return getRuleContext(LiteralContext.class,i);
		}
		public List<OperationContext> operation() {
			return getRuleContexts(OperationContext.class);
		}
		public OperationContext operation(int i) {
			return getRuleContext(OperationContext.class,i);
		}
		public ValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterValue(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitValue(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitValue(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ValueContext value() throws RecognitionException {
		ValueContext _localctx = new ValueContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(196);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
			case 1:
				{
				setState(193);
				name();
				}
				break;
			case 2:
				{
				setState(194);
				function();
				}
				break;
			case 3:
				{
				setState(195);
				literal();
				}
				break;
			}
			setState(206);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << MULTIPLY) | (1L << DIVIDE) | (1L << PLUS) | (1L << MINUS) | (1L << MODULE) | (1L << AND) | (1L << OR) | (1L << XOR))) != 0)) {
				{
				{
				setState(198);
				operation();
				setState(202);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
				case 1:
					{
					setState(199);
					name();
					}
					break;
				case 2:
					{
					setState(200);
					function();
					}
					break;
				case 3:
					{
					setState(201);
					literal();
					}
					break;
				}
				}
				}
				setState(208);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LiteralContext extends ParserRuleContext {
		public NumberLiteralContext numberLiteral() {
			return getRuleContext(NumberLiteralContext.class,0);
		}
		public DoubleLiteralContext doubleLiteral() {
			return getRuleContext(DoubleLiteralContext.class,0);
		}
		public BoolLiteralContext boolLiteral() {
			return getRuleContext(BoolLiteralContext.class,0);
		}
		public StringLiteralContext stringLiteral() {
			return getRuleContext(StringLiteralContext.class,0);
		}
		public LiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LiteralContext literal() throws RecognitionException {
		LiteralContext _localctx = new LiteralContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_literal);
		try {
			setState(213);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case NUMBER:
				enterOuterAlt(_localctx, 1);
				{
				setState(209);
				numberLiteral();
				}
				break;
			case DOUBLE:
				enterOuterAlt(_localctx, 2);
				{
				setState(210);
				doubleLiteral();
				}
				break;
			case BOOL:
				enterOuterAlt(_localctx, 3);
				{
				setState(211);
				boolLiteral();
				}
				break;
			case STRING:
				enterOuterAlt(_localctx, 4);
				{
				setState(212);
				stringLiteral();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NumberLiteralContext extends ParserRuleContext {
		public List<TerminalNode> NUMBER() { return getTokens(GoodImpLangParser.NUMBER); }
		public TerminalNode NUMBER(int i) {
			return getToken(GoodImpLangParser.NUMBER, i);
		}
		public List<OperationContext> operation() {
			return getRuleContexts(OperationContext.class);
		}
		public OperationContext operation(int i) {
			return getRuleContext(OperationContext.class,i);
		}
		public NumberLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_numberLiteral; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterNumberLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitNumberLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitNumberLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final NumberLiteralContext numberLiteral() throws RecognitionException {
		NumberLiteralContext _localctx = new NumberLiteralContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_numberLiteral);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(215);
			match(NUMBER);
			setState(221);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,19,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(216);
					operation();
					setState(217);
					match(NUMBER);
					}
					} 
				}
				setState(223);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,19,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DoubleLiteralContext extends ParserRuleContext {
		public List<TerminalNode> DOUBLE() { return getTokens(GoodImpLangParser.DOUBLE); }
		public TerminalNode DOUBLE(int i) {
			return getToken(GoodImpLangParser.DOUBLE, i);
		}
		public List<OperationContext> operation() {
			return getRuleContexts(OperationContext.class);
		}
		public OperationContext operation(int i) {
			return getRuleContext(OperationContext.class,i);
		}
		public DoubleLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_doubleLiteral; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterDoubleLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitDoubleLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitDoubleLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DoubleLiteralContext doubleLiteral() throws RecognitionException {
		DoubleLiteralContext _localctx = new DoubleLiteralContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_doubleLiteral);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(224);
			match(DOUBLE);
			setState(230);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,20,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(225);
					operation();
					setState(226);
					match(DOUBLE);
					}
					} 
				}
				setState(232);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,20,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BoolLiteralContext extends ParserRuleContext {
		public List<TerminalNode> BOOL() { return getTokens(GoodImpLangParser.BOOL); }
		public TerminalNode BOOL(int i) {
			return getToken(GoodImpLangParser.BOOL, i);
		}
		public List<TerminalNode> AND() { return getTokens(GoodImpLangParser.AND); }
		public TerminalNode AND(int i) {
			return getToken(GoodImpLangParser.AND, i);
		}
		public List<TerminalNode> XOR() { return getTokens(GoodImpLangParser.XOR); }
		public TerminalNode XOR(int i) {
			return getToken(GoodImpLangParser.XOR, i);
		}
		public List<TerminalNode> OR() { return getTokens(GoodImpLangParser.OR); }
		public TerminalNode OR(int i) {
			return getToken(GoodImpLangParser.OR, i);
		}
		public BoolLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_boolLiteral; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterBoolLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitBoolLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitBoolLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BoolLiteralContext boolLiteral() throws RecognitionException {
		BoolLiteralContext _localctx = new BoolLiteralContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_boolLiteral);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(233);
			match(BOOL);
			setState(238);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,21,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(234);
					_la = _input.LA(1);
					if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << AND) | (1L << OR) | (1L << XOR))) != 0)) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(235);
					match(BOOL);
					}
					} 
				}
				setState(240);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,21,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StringLiteralContext extends ParserRuleContext {
		public List<TerminalNode> STRING() { return getTokens(GoodImpLangParser.STRING); }
		public TerminalNode STRING(int i) {
			return getToken(GoodImpLangParser.STRING, i);
		}
		public List<TerminalNode> PLUS() { return getTokens(GoodImpLangParser.PLUS); }
		public TerminalNode PLUS(int i) {
			return getToken(GoodImpLangParser.PLUS, i);
		}
		public StringLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stringLiteral; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterStringLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitStringLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitStringLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StringLiteralContext stringLiteral() throws RecognitionException {
		StringLiteralContext _localctx = new StringLiteralContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_stringLiteral);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(241);
			match(STRING);
			setState(246);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,22,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(242);
					match(PLUS);
					setState(243);
					match(STRING);
					}
					} 
				}
				setState(248);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,22,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NameContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(GoodImpLangParser.IDENTIFIER, 0); }
		public NameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_name; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterName(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitName(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitName(this);
			else return visitor.visitChildren(this);
		}
	}

	public final NameContext name() throws RecognitionException {
		NameContext _localctx = new NameContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(249);
			match(IDENTIFIER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IfStatementContext extends ParserRuleContext {
		public TerminalNode IF() { return getToken(GoodImpLangParser.IF, 0); }
		public TerminalNode OPEN_BRACKET() { return getToken(GoodImpLangParser.OPEN_BRACKET, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public TerminalNode CLOSE_BRACKET() { return getToken(GoodImpLangParser.CLOSE_BRACKET, 0); }
		public ScopeContext scope() {
			return getRuleContext(ScopeContext.class,0);
		}
		public IfStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifStatement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterIfStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitIfStatement(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitIfStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IfStatementContext ifStatement() throws RecognitionException {
		IfStatementContext _localctx = new IfStatementContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_ifStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(251);
			match(IF);
			setState(252);
			match(OPEN_BRACKET);
			setState(253);
			statement();
			setState(254);
			match(CLOSE_BRACKET);
			setState(255);
			scope();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class WhileLoopContext extends ParserRuleContext {
		public TerminalNode WHILE() { return getToken(GoodImpLangParser.WHILE, 0); }
		public TerminalNode OPEN_BRACKET() { return getToken(GoodImpLangParser.OPEN_BRACKET, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public TerminalNode CLOSE_BRACKET() { return getToken(GoodImpLangParser.CLOSE_BRACKET, 0); }
		public ScopeContext scope() {
			return getRuleContext(ScopeContext.class,0);
		}
		public WhileLoopContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_whileLoop; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterWhileLoop(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitWhileLoop(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitWhileLoop(this);
			else return visitor.visitChildren(this);
		}
	}

	public final WhileLoopContext whileLoop() throws RecognitionException {
		WhileLoopContext _localctx = new WhileLoopContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_whileLoop);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(257);
			match(WHILE);
			setState(258);
			match(OPEN_BRACKET);
			setState(259);
			statement();
			setState(260);
			match(CLOSE_BRACKET);
			setState(261);
			scope();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ForLoopContext extends ParserRuleContext {
		public TerminalNode FOR() { return getToken(GoodImpLangParser.FOR, 0); }
		public TerminalNode OPEN_BRACKET() { return getToken(GoodImpLangParser.OPEN_BRACKET, 0); }
		public List<NameContext> name() {
			return getRuleContexts(NameContext.class);
		}
		public NameContext name(int i) {
			return getRuleContext(NameContext.class,i);
		}
		public TerminalNode IN() { return getToken(GoodImpLangParser.IN, 0); }
		public TerminalNode CLOSE_BRACKET() { return getToken(GoodImpLangParser.CLOSE_BRACKET, 0); }
		public ScopeContext scope() {
			return getRuleContext(ScopeContext.class,0);
		}
		public List<TerminalNode> NUMBER() { return getTokens(GoodImpLangParser.NUMBER); }
		public TerminalNode NUMBER(int i) {
			return getToken(GoodImpLangParser.NUMBER, i);
		}
		public List<TerminalNode> DOT() { return getTokens(GoodImpLangParser.DOT); }
		public TerminalNode DOT(int i) {
			return getToken(GoodImpLangParser.DOT, i);
		}
		public ForLoopContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forLoop; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterForLoop(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitForLoop(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitForLoop(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ForLoopContext forLoop() throws RecognitionException {
		ForLoopContext _localctx = new ForLoopContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_forLoop);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(263);
			match(FOR);
			setState(264);
			match(OPEN_BRACKET);
			setState(265);
			name();
			setState(266);
			match(IN);
			setState(273);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,24,_ctx) ) {
			case 1:
				{
				setState(269);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case NUMBER:
					{
					setState(267);
					match(NUMBER);
					}
					break;
				case IDENTIFIER:
					{
					setState(268);
					name();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(271);
				match(DOT);
				setState(272);
				match(DOT);
				}
				break;
			}
			setState(277);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case NUMBER:
				{
				setState(275);
				match(NUMBER);
				}
				break;
			case IDENTIFIER:
				{
				setState(276);
				name();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(279);
			match(CLOSE_BRACKET);
			setState(280);
			scope();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatementContext extends ParserRuleContext {
		public TerminalNode NOT() { return getToken(GoodImpLangParser.NOT, 0); }
		public TerminalNode OPEN_BRACKET() { return getToken(GoodImpLangParser.OPEN_BRACKET, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public TerminalNode CLOSE_BRACKET() { return getToken(GoodImpLangParser.CLOSE_BRACKET, 0); }
		public NameContext name() {
			return getRuleContext(NameContext.class,0);
		}
		public FunctionContext function() {
			return getRuleContext(FunctionContext.class,0);
		}
		public PredicateContext predicate() {
			return getRuleContext(PredicateContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitStatement(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_statement);
		try {
			setState(290);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,26,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(282);
				match(NOT);
				setState(283);
				match(OPEN_BRACKET);
				setState(284);
				statement();
				setState(285);
				match(CLOSE_BRACKET);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(287);
				name();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(288);
				function();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(289);
				predicate();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PredicateContext extends ParserRuleContext {
		public TerminalNode LESS_OP() { return getToken(GoodImpLangParser.LESS_OP, 0); }
		public TerminalNode MORE_OP() { return getToken(GoodImpLangParser.MORE_OP, 0); }
		public TerminalNode LESS_OR_EQUAL() { return getToken(GoodImpLangParser.LESS_OR_EQUAL, 0); }
		public TerminalNode MORE_OR_EQUAL() { return getToken(GoodImpLangParser.MORE_OR_EQUAL, 0); }
		public TerminalNode EQUALS() { return getToken(GoodImpLangParser.EQUALS, 0); }
		public TerminalNode NOT_EQUALS() { return getToken(GoodImpLangParser.NOT_EQUALS, 0); }
		public List<NameContext> name() {
			return getRuleContexts(NameContext.class);
		}
		public NameContext name(int i) {
			return getRuleContext(NameContext.class,i);
		}
		public List<FunctionContext> function() {
			return getRuleContexts(FunctionContext.class);
		}
		public FunctionContext function(int i) {
			return getRuleContext(FunctionContext.class,i);
		}
		public List<LiteralContext> literal() {
			return getRuleContexts(LiteralContext.class);
		}
		public LiteralContext literal(int i) {
			return getRuleContext(LiteralContext.class,i);
		}
		public PredicateContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_predicate; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).enterPredicate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GoodImpLangListener ) ((GoodImpLangListener)listener).exitPredicate(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GoodImpLangVisitor ) return ((GoodImpLangVisitor<? extends T>)visitor).visitPredicate(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PredicateContext predicate() throws RecognitionException {
		PredicateContext _localctx = new PredicateContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_predicate);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(295);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,27,_ctx) ) {
			case 1:
				{
				setState(292);
				name();
				}
				break;
			case 2:
				{
				setState(293);
				function();
				}
				break;
			case 3:
				{
				setState(294);
				literal();
				}
				break;
			}
			setState(297);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LESS_OP) | (1L << MORE_OP) | (1L << LESS_OR_EQUAL) | (1L << MORE_OR_EQUAL) | (1L << EQUALS) | (1L << NOT_EQUALS))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(301);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,28,_ctx) ) {
			case 1:
				{
				setState(298);
				name();
				}
				break;
			case 2:
				{
				setState(299);
				function();
				}
				break;
			case 3:
				{
				setState(300);
				literal();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\61\u0132\4\2\t\2"+
		"\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\3\2\3\2\3\2\3\3\6\3K\n\3\r\3\16\3L\3\4\3\4\5\4Q\n\4"+
		"\3\5\3\5\3\5\3\5\3\5\3\5\3\5\5\5Z\n\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\5\6"+
		"c\n\6\3\6\5\6f\n\6\3\7\3\7\3\b\3\b\3\t\3\t\3\t\3\t\3\t\7\tq\n\t\f\t\16"+
		"\tt\13\t\3\t\3\t\3\n\3\n\3\n\3\13\3\13\3\13\5\13~\n\13\3\f\3\f\3\f\3\f"+
		"\3\r\3\r\3\r\3\r\3\r\5\r\u0089\n\r\3\16\3\16\3\16\3\16\3\17\3\17\3\17"+
		"\5\17\u0092\n\17\3\20\3\20\3\20\3\20\3\21\3\21\3\21\7\21\u009b\n\21\f"+
		"\21\16\21\u009e\13\21\3\21\3\21\3\21\3\21\7\21\u00a4\n\21\f\21\16\21\u00a7"+
		"\13\21\3\22\3\22\3\22\3\22\3\22\3\23\3\23\3\23\5\23\u00b1\n\23\3\24\3"+
		"\24\5\24\u00b5\n\24\3\25\3\25\3\25\3\25\3\26\3\26\3\26\3\26\3\26\5\26"+
		"\u00c0\n\26\3\27\3\27\3\30\3\30\3\30\5\30\u00c7\n\30\3\30\3\30\3\30\3"+
		"\30\5\30\u00cd\n\30\7\30\u00cf\n\30\f\30\16\30\u00d2\13\30\3\31\3\31\3"+
		"\31\3\31\5\31\u00d8\n\31\3\32\3\32\3\32\3\32\7\32\u00de\n\32\f\32\16\32"+
		"\u00e1\13\32\3\33\3\33\3\33\3\33\7\33\u00e7\n\33\f\33\16\33\u00ea\13\33"+
		"\3\34\3\34\3\34\7\34\u00ef\n\34\f\34\16\34\u00f2\13\34\3\35\3\35\3\35"+
		"\7\35\u00f7\n\35\f\35\16\35\u00fa\13\35\3\36\3\36\3\37\3\37\3\37\3\37"+
		"\3\37\3\37\3 \3 \3 \3 \3 \3 \3!\3!\3!\3!\3!\3!\5!\u0110\n!\3!\3!\5!\u0114"+
		"\n!\3!\3!\5!\u0118\n!\3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\5\"\u0125"+
		"\n\"\3#\3#\3#\5#\u012a\n#\3#\3#\3#\3#\5#\u0130\n#\3#\2\2$\2\4\6\b\n\f"+
		"\16\20\22\24\26\30\32\34\36 \"$&(*,.\60\62\64\668:<>@BD\2\7\3\2*\60\3"+
		"\2%)\4\2\25\31\33\35\3\2\33\35\3\2\37$\2\u0139\2F\3\2\2\2\4J\3\2\2\2\6"+
		"P\3\2\2\2\bR\3\2\2\2\ne\3\2\2\2\fg\3\2\2\2\16i\3\2\2\2\20k\3\2\2\2\22"+
		"w\3\2\2\2\24}\3\2\2\2\26\177\3\2\2\2\30\u0088\3\2\2\2\32\u008a\3\2\2\2"+
		"\34\u0091\3\2\2\2\36\u0093\3\2\2\2 \u0097\3\2\2\2\"\u00a8\3\2\2\2$\u00b0"+
		"\3\2\2\2&\u00b4\3\2\2\2(\u00b6\3\2\2\2*\u00bf\3\2\2\2,\u00c1\3\2\2\2."+
		"\u00c6\3\2\2\2\60\u00d7\3\2\2\2\62\u00d9\3\2\2\2\64\u00e2\3\2\2\2\66\u00eb"+
		"\3\2\2\28\u00f3\3\2\2\2:\u00fb\3\2\2\2<\u00fd\3\2\2\2>\u0103\3\2\2\2@"+
		"\u0109\3\2\2\2B\u0124\3\2\2\2D\u0129\3\2\2\2FG\5\4\3\2GH\7\2\2\3H\3\3"+
		"\2\2\2IK\5\6\4\2JI\3\2\2\2KL\3\2\2\2LJ\3\2\2\2LM\3\2\2\2M\5\3\2\2\2NQ"+
		"\5\b\5\2OQ\5\n\6\2PN\3\2\2\2PO\3\2\2\2Q\7\3\2\2\2RS\7\23\2\2ST\5\f\7\2"+
		"TU\7\6\2\2UV\5\24\13\2VY\7\7\2\2WX\7\3\2\2XZ\5\16\b\2YW\3\2\2\2YZ\3\2"+
		"\2\2Z[\3\2\2\2[\\\5\20\t\2\\\t\3\2\2\2]f\5\34\17\2^c\3\2\2\2_c\5\36\20"+
		"\2`c\5 \21\2ac\5\"\22\2b^\3\2\2\2b_\3\2\2\2b`\3\2\2\2ba\3\2\2\2cd\3\2"+
		"\2\2df\7\n\2\2e]\3\2\2\2eb\3\2\2\2f\13\3\2\2\2gh\t\2\2\2h\r\3\2\2\2ij"+
		"\t\3\2\2j\17\3\2\2\2kr\7\b\2\2lq\5\n\6\2mn\5\22\n\2no\7\n\2\2oq\3\2\2"+
		"\2pl\3\2\2\2pm\3\2\2\2qt\3\2\2\2rp\3\2\2\2rs\3\2\2\2su\3\2\2\2tr\3\2\2"+
		"\2uv\7\t\2\2v\21\3\2\2\2wx\7\24\2\2xy\5.\30\2y\23\3\2\2\2z~\3\2\2\2{~"+
		"\5\32\16\2|~\5\26\f\2}z\3\2\2\2}{\3\2\2\2}|\3\2\2\2~\25\3\2\2\2\177\u0080"+
		"\5\32\16\2\u0080\u0081\7\5\2\2\u0081\u0082\5\30\r\2\u0082\27\3\2\2\2\u0083"+
		"\u0089\5\32\16\2\u0084\u0085\5\32\16\2\u0085\u0086\7\5\2\2\u0086\u0087"+
		"\5\30\r\2\u0087\u0089\3\2\2\2\u0088\u0083\3\2\2\2\u0088\u0084\3\2\2\2"+
		"\u0089\31\3\2\2\2\u008a\u008b\5:\36\2\u008b\u008c\7\3\2\2\u008c\u008d"+
		"\5\16\b\2\u008d\33\3\2\2\2\u008e\u0092\5@!\2\u008f\u0092\5> \2\u0090\u0092"+
		"\5<\37\2\u0091\u008e\3\2\2\2\u0091\u008f\3\2\2\2\u0091\u0090\3\2\2\2\u0092"+
		"\35\3\2\2\2\u0093\u0094\5:\36\2\u0094\u0095\7\3\2\2\u0095\u0096\5\16\b"+
		"\2\u0096\37\3\2\2\2\u0097\u009c\5:\36\2\u0098\u0099\7\5\2\2\u0099\u009b"+
		"\5:\36\2\u009a\u0098\3\2\2\2\u009b\u009e\3\2\2\2\u009c\u009a\3\2\2\2\u009c"+
		"\u009d\3\2\2\2\u009d\u009f\3\2\2\2\u009e\u009c\3\2\2\2\u009f\u00a0\7\32"+
		"\2\2\u00a0\u00a5\5.\30\2\u00a1\u00a2\7\5\2\2\u00a2\u00a4\5.\30\2\u00a3"+
		"\u00a1\3\2\2\2\u00a4\u00a7\3\2\2\2\u00a5\u00a3\3\2\2\2\u00a5\u00a6\3\2"+
		"\2\2\u00a6!\3\2\2\2\u00a7\u00a5\3\2\2\2\u00a8\u00a9\5\f\7\2\u00a9\u00aa"+
		"\7\6\2\2\u00aa\u00ab\5$\23\2\u00ab\u00ac\7\7\2\2\u00ac#\3\2\2\2\u00ad"+
		"\u00b1\3\2\2\2\u00ae\u00b1\5&\24\2\u00af\u00b1\5(\25\2\u00b0\u00ad\3\2"+
		"\2\2\u00b0\u00ae\3\2\2\2\u00b0\u00af\3\2\2\2\u00b1%\3\2\2\2\u00b2\u00b5"+
		"\5:\36\2\u00b3\u00b5\5.\30\2\u00b4\u00b2\3\2\2\2\u00b4\u00b3\3\2\2\2\u00b5"+
		"\'\3\2\2\2\u00b6\u00b7\5&\24\2\u00b7\u00b8\7\5\2\2\u00b8\u00b9\5*\26\2"+
		"\u00b9)\3\2\2\2\u00ba\u00c0\5&\24\2\u00bb\u00bc\5&\24\2\u00bc\u00bd\7"+
		"\5\2\2\u00bd\u00be\5*\26\2\u00be\u00c0\3\2\2\2\u00bf\u00ba\3\2\2\2\u00bf"+
		"\u00bb\3\2\2\2\u00c0+\3\2\2\2\u00c1\u00c2\t\4\2\2\u00c2-\3\2\2\2\u00c3"+
		"\u00c7\5:\36\2\u00c4\u00c7\5\"\22\2\u00c5\u00c7\5\60\31\2\u00c6\u00c3"+
		"\3\2\2\2\u00c6\u00c4\3\2\2\2\u00c6\u00c5\3\2\2\2\u00c7\u00d0\3\2\2\2\u00c8"+
		"\u00cc\5,\27\2\u00c9\u00cd\5:\36\2\u00ca\u00cd\5\"\22\2\u00cb\u00cd\5"+
		"\60\31\2\u00cc\u00c9\3\2\2\2\u00cc\u00ca\3\2\2\2\u00cc\u00cb\3\2\2\2\u00cd"+
		"\u00cf\3\2\2\2\u00ce\u00c8\3\2\2\2\u00cf\u00d2\3\2\2\2\u00d0\u00ce\3\2"+
		"\2\2\u00d0\u00d1\3\2\2\2\u00d1/\3\2\2\2\u00d2\u00d0\3\2\2\2\u00d3\u00d8"+
		"\5\62\32\2\u00d4\u00d8\5\64\33\2\u00d5\u00d8\5\66\34\2\u00d6\u00d8\58"+
		"\35\2\u00d7\u00d3\3\2\2\2\u00d7\u00d4\3\2\2\2\u00d7\u00d5\3\2\2\2\u00d7"+
		"\u00d6\3\2\2\2\u00d8\61\3\2\2\2\u00d9\u00df\7\13\2\2\u00da\u00db\5,\27"+
		"\2\u00db\u00dc\7\13\2\2\u00dc\u00de\3\2\2\2\u00dd\u00da\3\2\2\2\u00de"+
		"\u00e1\3\2\2\2\u00df\u00dd\3\2\2\2\u00df\u00e0\3\2\2\2\u00e0\63\3\2\2"+
		"\2\u00e1\u00df\3\2\2\2\u00e2\u00e8\7\f\2\2\u00e3\u00e4\5,\27\2\u00e4\u00e5"+
		"\7\f\2\2\u00e5\u00e7\3\2\2\2\u00e6\u00e3\3\2\2\2\u00e7\u00ea\3\2\2\2\u00e8"+
		"\u00e6\3\2\2\2\u00e8\u00e9\3\2\2\2\u00e9\65\3\2\2\2\u00ea\u00e8\3\2\2"+
		"\2\u00eb\u00f0\7\16\2\2\u00ec\u00ed\t\5\2\2\u00ed\u00ef\7\16\2\2\u00ee"+
		"\u00ec\3\2\2\2\u00ef\u00f2\3\2\2\2\u00f0\u00ee\3\2\2\2\u00f0\u00f1\3\2"+
		"\2\2\u00f1\67\3\2\2\2\u00f2\u00f0\3\2\2\2\u00f3\u00f8\7\r\2\2\u00f4\u00f5"+
		"\7\27\2\2\u00f5\u00f7\7\r\2\2\u00f6\u00f4\3\2\2\2\u00f7\u00fa\3\2\2\2"+
		"\u00f8\u00f6\3\2\2\2\u00f8\u00f9\3\2\2\2\u00f99\3\2\2\2\u00fa\u00f8\3"+
		"\2\2\2\u00fb\u00fc\7\60\2\2\u00fc;\3\2\2\2\u00fd\u00fe\7\17\2\2\u00fe"+
		"\u00ff\7\6\2\2\u00ff\u0100\5B\"\2\u0100\u0101\7\7\2\2\u0101\u0102\5\20"+
		"\t\2\u0102=\3\2\2\2\u0103\u0104\7\20\2\2\u0104\u0105\7\6\2\2\u0105\u0106"+
		"\5B\"\2\u0106\u0107\7\7\2\2\u0107\u0108\5\20\t\2\u0108?\3\2\2\2\u0109"+
		"\u010a\7\21\2\2\u010a\u010b\7\6\2\2\u010b\u010c\5:\36\2\u010c\u0113\7"+
		"\22\2\2\u010d\u0110\7\13\2\2\u010e\u0110\5:\36\2\u010f\u010d\3\2\2\2\u010f"+
		"\u010e\3\2\2\2\u0110\u0111\3\2\2\2\u0111\u0112\7\4\2\2\u0112\u0114\7\4"+
		"\2\2\u0113\u010f\3\2\2\2\u0113\u0114\3\2\2\2\u0114\u0117\3\2\2\2\u0115"+
		"\u0118\7\13\2\2\u0116\u0118\5:\36\2\u0117\u0115\3\2\2\2\u0117\u0116\3"+
		"\2\2\2\u0118\u0119\3\2\2\2\u0119\u011a\7\7\2\2\u011a\u011b\5\20\t\2\u011b"+
		"A\3\2\2\2\u011c\u011d\7\36\2\2\u011d\u011e\7\6\2\2\u011e\u011f\5B\"\2"+
		"\u011f\u0120\7\7\2\2\u0120\u0125\3\2\2\2\u0121\u0125\5:\36\2\u0122\u0125"+
		"\5\"\22\2\u0123\u0125\5D#\2\u0124\u011c\3\2\2\2\u0124\u0121\3\2\2\2\u0124"+
		"\u0122\3\2\2\2\u0124\u0123\3\2\2\2\u0125C\3\2\2\2\u0126\u012a\5:\36\2"+
		"\u0127\u012a\5\"\22\2\u0128\u012a\5\60\31\2\u0129\u0126\3\2\2\2\u0129"+
		"\u0127\3\2\2\2\u0129\u0128\3\2\2\2\u012a\u012b\3\2\2\2\u012b\u012f\t\6"+
		"\2\2\u012c\u0130\5:\36\2\u012d\u0130\5\"\22\2\u012e\u0130\5\60\31\2\u012f"+
		"\u012c\3\2\2\2\u012f\u012d\3\2\2\2\u012f\u012e\3\2\2\2\u0130E\3\2\2\2"+
		"\37LPYbepr}\u0088\u0091\u009c\u00a5\u00b0\u00b4\u00bf\u00c6\u00cc\u00d0"+
		"\u00d7\u00df\u00e8\u00f0\u00f8\u010f\u0113\u0117\u0124\u0129\u012f";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}
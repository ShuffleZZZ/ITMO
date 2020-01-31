// Generated from C:/Users/User/ITMO/TranslationMethods/3rdLab/src/grammar\GoodImpLang.g4 by ANTLR 4.7.2
package grammar;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class GoodImpLangLexer extends Lexer {
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
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"EQUALS_SIGN", "AND_SIGN", "OR_SIGN", "XOR_SIGN", "NOT_SIGN", "LESS_SIGN", 
			"MORE_SIGN", "DIGITS", "COLON", "DOT", "COMMA", "OPEN_BRACKET", "CLOSE_BRACKET", 
			"OPEN_SCOPE", "CLOSE_SCOPE", "LINE_SEPARATOR", "NUMBER", "DOUBLE", "STRING", 
			"BOOL", "IF", "WHILE", "FOR", "IN", "FUN", "RETURN", "MULTIPLY", "DIVIDE", 
			"PLUS", "MINUS", "MODULE", "ASSIGN", "AND", "OR", "XOR", "NOT", "LESS_OP", 
			"MORE_OP", "LESS_OR_EQUAL", "MORE_OR_EQUAL", "EQUALS", "NOT_EQUALS", 
			"INT_TYPE", "LONG_TYPE", "BOOL_TYPE", "STRING_TYPE", "DOUBLE_TYPE", "NEXT_INT", 
			"NEXT_LONG", "NEXT_BOOL", "NEXT_DOUBLE", "NEXT_LINE", "PRINT", "IDENTIFIER", 
			"WHITESPACE"
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


	public GoodImpLangLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "GoodImpLang.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\61\u0156\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t"+
		" \4!\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t"+
		"+\4,\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64"+
		"\t\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\3\2\3\2\3\3\3\3\3\4\3\4\3\5"+
		"\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\6\t\u0081\n\t\r\t\16\t\u0082\3\n\3\n"+
		"\3\13\3\13\3\f\3\f\3\r\3\r\3\16\3\16\3\17\3\17\3\20\3\20\3\21\3\21\3\22"+
		"\5\22\u0096\n\22\3\22\3\22\3\23\3\23\3\23\3\23\3\24\3\24\7\24\u00a0\n"+
		"\24\f\24\16\24\u00a3\13\24\3\24\3\24\3\24\7\24\u00a8\n\24\f\24\16\24\u00ab"+
		"\13\24\3\24\5\24\u00ae\n\24\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3"+
		"\25\5\25\u00b9\n\25\3\26\3\26\3\26\3\27\3\27\3\27\3\27\3\27\3\27\3\30"+
		"\3\30\3\30\3\30\3\31\3\31\3\31\3\32\3\32\3\32\3\32\3\33\3\33\3\33\3\33"+
		"\3\33\3\33\3\33\3\34\3\34\3\35\3\35\3\36\3\36\3\37\3\37\3 \3 \3!\3!\3"+
		"\"\3\"\3\"\3#\3#\3#\3$\3$\3%\3%\3&\3&\3\'\3\'\3(\3(\3(\3)\3)\3)\3*\3*"+
		"\3*\3+\3+\3+\3,\3,\3,\3,\3-\3-\3-\3-\3-\3.\3.\3.\3.\3.\3/\3/\3/\3/\3/"+
		"\3/\3/\3\60\3\60\3\60\3\60\3\60\3\60\3\60\3\61\3\61\3\61\3\61\3\61\3\61"+
		"\3\61\3\61\3\62\3\62\3\62\3\62\3\62\3\62\3\62\3\62\3\62\3\63\3\63\3\63"+
		"\3\63\3\63\3\63\3\63\3\63\3\63\3\64\3\64\3\64\3\64\3\64\3\64\3\64\3\64"+
		"\3\64\3\64\3\64\3\65\3\65\3\65\3\65\3\65\3\65\3\65\3\65\3\65\3\66\3\66"+
		"\3\66\3\66\3\66\3\66\3\67\3\67\7\67\u014e\n\67\f\67\16\67\u0151\13\67"+
		"\38\38\38\38\4\u00a1\u00a9\29\3\2\5\2\7\2\t\2\13\2\r\2\17\2\21\2\23\3"+
		"\25\4\27\5\31\6\33\7\35\b\37\t!\n#\13%\f\'\r)\16+\17-\20/\21\61\22\63"+
		"\23\65\24\67\259\26;\27=\30?\31A\32C\33E\34G\35I\36K\37M O!Q\"S#U$W%Y"+
		"&[\'](_)a*c+e,g-i.k/m\60o\61\3\2\6\3\2\62;\4\2C\\c|\5\2\62;C\\c|\5\2\13"+
		"\f\17\17\"\"\2\u0154\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2"+
		"\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2"+
		"\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2"+
		"\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3"+
		"\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3\2\2"+
		"\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2S\3\2\2\2\2U\3\2\2\2\2"+
		"W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\2a\3\2\2\2\2c\3"+
		"\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2\2\2\2k\3\2\2\2\2m\3\2\2\2\2o\3\2\2"+
		"\2\3q\3\2\2\2\5s\3\2\2\2\7u\3\2\2\2\tw\3\2\2\2\13y\3\2\2\2\r{\3\2\2\2"+
		"\17}\3\2\2\2\21\u0080\3\2\2\2\23\u0084\3\2\2\2\25\u0086\3\2\2\2\27\u0088"+
		"\3\2\2\2\31\u008a\3\2\2\2\33\u008c\3\2\2\2\35\u008e\3\2\2\2\37\u0090\3"+
		"\2\2\2!\u0092\3\2\2\2#\u0095\3\2\2\2%\u0099\3\2\2\2\'\u00ad\3\2\2\2)\u00b8"+
		"\3\2\2\2+\u00ba\3\2\2\2-\u00bd\3\2\2\2/\u00c3\3\2\2\2\61\u00c7\3\2\2\2"+
		"\63\u00ca\3\2\2\2\65\u00ce\3\2\2\2\67\u00d5\3\2\2\29\u00d7\3\2\2\2;\u00d9"+
		"\3\2\2\2=\u00db\3\2\2\2?\u00dd\3\2\2\2A\u00df\3\2\2\2C\u00e1\3\2\2\2E"+
		"\u00e4\3\2\2\2G\u00e7\3\2\2\2I\u00e9\3\2\2\2K\u00eb\3\2\2\2M\u00ed\3\2"+
		"\2\2O\u00ef\3\2\2\2Q\u00f2\3\2\2\2S\u00f5\3\2\2\2U\u00f8\3\2\2\2W\u00fb"+
		"\3\2\2\2Y\u00ff\3\2\2\2[\u0104\3\2\2\2]\u0109\3\2\2\2_\u0110\3\2\2\2a"+
		"\u0117\3\2\2\2c\u011f\3\2\2\2e\u0128\3\2\2\2g\u0131\3\2\2\2i\u013c\3\2"+
		"\2\2k\u0145\3\2\2\2m\u014b\3\2\2\2o\u0152\3\2\2\2qr\7?\2\2r\4\3\2\2\2"+
		"st\7(\2\2t\6\3\2\2\2uv\7~\2\2v\b\3\2\2\2wx\7`\2\2x\n\3\2\2\2yz\7#\2\2"+
		"z\f\3\2\2\2{|\7>\2\2|\16\3\2\2\2}~\7@\2\2~\20\3\2\2\2\177\u0081\t\2\2"+
		"\2\u0080\177\3\2\2\2\u0081\u0082\3\2\2\2\u0082\u0080\3\2\2\2\u0082\u0083"+
		"\3\2\2\2\u0083\22\3\2\2\2\u0084\u0085\7<\2\2\u0085\24\3\2\2\2\u0086\u0087"+
		"\7\60\2\2\u0087\26\3\2\2\2\u0088\u0089\7.\2\2\u0089\30\3\2\2\2\u008a\u008b"+
		"\7*\2\2\u008b\32\3\2\2\2\u008c\u008d\7+\2\2\u008d\34\3\2\2\2\u008e\u008f"+
		"\7}\2\2\u008f\36\3\2\2\2\u0090\u0091\7\177\2\2\u0091 \3\2\2\2\u0092\u0093"+
		"\7\f\2\2\u0093\"\3\2\2\2\u0094\u0096\5=\37\2\u0095\u0094\3\2\2\2\u0095"+
		"\u0096\3\2\2\2\u0096\u0097\3\2\2\2\u0097\u0098\5\21\t\2\u0098$\3\2\2\2"+
		"\u0099\u009a\5#\22\2\u009a\u009b\5\25\13\2\u009b\u009c\5\21\t\2\u009c"+
		"&\3\2\2\2\u009d\u00a1\7$\2\2\u009e\u00a0\13\2\2\2\u009f\u009e\3\2\2\2"+
		"\u00a0\u00a3\3\2\2\2\u00a1\u00a2\3\2\2\2\u00a1\u009f\3\2\2\2\u00a2\u00a4"+
		"\3\2\2\2\u00a3\u00a1\3\2\2\2\u00a4\u00ae\7$\2\2\u00a5\u00a9\7)\2\2\u00a6"+
		"\u00a8\13\2\2\2\u00a7\u00a6\3\2\2\2\u00a8\u00ab\3\2\2\2\u00a9\u00aa\3"+
		"\2\2\2\u00a9\u00a7\3\2\2\2\u00aa\u00ac\3\2\2\2\u00ab\u00a9\3\2\2\2\u00ac"+
		"\u00ae\7)\2\2\u00ad\u009d\3\2\2\2\u00ad\u00a5\3\2\2\2\u00ae(\3\2\2\2\u00af"+
		"\u00b0\7v\2\2\u00b0\u00b1\7t\2\2\u00b1\u00b2\7w\2\2\u00b2\u00b9\7g\2\2"+
		"\u00b3\u00b4\7h\2\2\u00b4\u00b5\7c\2\2\u00b5\u00b6\7n\2\2\u00b6\u00b7"+
		"\7u\2\2\u00b7\u00b9\7g\2\2\u00b8\u00af\3\2\2\2\u00b8\u00b3\3\2\2\2\u00b9"+
		"*\3\2\2\2\u00ba\u00bb\7k\2\2\u00bb\u00bc\7h\2\2\u00bc,\3\2\2\2\u00bd\u00be"+
		"\7y\2\2\u00be\u00bf\7j\2\2\u00bf\u00c0\7k\2\2\u00c0\u00c1\7n\2\2\u00c1"+
		"\u00c2\7g\2\2\u00c2.\3\2\2\2\u00c3\u00c4\7h\2\2\u00c4\u00c5\7q\2\2\u00c5"+
		"\u00c6\7t\2\2\u00c6\60\3\2\2\2\u00c7\u00c8\7k\2\2\u00c8\u00c9\7p\2\2\u00c9"+
		"\62\3\2\2\2\u00ca\u00cb\7h\2\2\u00cb\u00cc\7w\2\2\u00cc\u00cd\7p\2\2\u00cd"+
		"\64\3\2\2\2\u00ce\u00cf\7t\2\2\u00cf\u00d0\7g\2\2\u00d0\u00d1\7v\2\2\u00d1"+
		"\u00d2\7w\2\2\u00d2\u00d3\7t\2\2\u00d3\u00d4\7p\2\2\u00d4\66\3\2\2\2\u00d5"+
		"\u00d6\7,\2\2\u00d68\3\2\2\2\u00d7\u00d8\7\61\2\2\u00d8:\3\2\2\2\u00d9"+
		"\u00da\7-\2\2\u00da<\3\2\2\2\u00db\u00dc\7/\2\2\u00dc>\3\2\2\2\u00dd\u00de"+
		"\7\'\2\2\u00de@\3\2\2\2\u00df\u00e0\5\3\2\2\u00e0B\3\2\2\2\u00e1\u00e2"+
		"\5\5\3\2\u00e2\u00e3\5\5\3\2\u00e3D\3\2\2\2\u00e4\u00e5\5\7\4\2\u00e5"+
		"\u00e6\5\7\4\2\u00e6F\3\2\2\2\u00e7\u00e8\5\t\5\2\u00e8H\3\2\2\2\u00e9"+
		"\u00ea\5\13\6\2\u00eaJ\3\2\2\2\u00eb\u00ec\5\r\7\2\u00ecL\3\2\2\2\u00ed"+
		"\u00ee\5\17\b\2\u00eeN\3\2\2\2\u00ef\u00f0\5\r\7\2\u00f0\u00f1\5\3\2\2"+
		"\u00f1P\3\2\2\2\u00f2\u00f3\5\17\b\2\u00f3\u00f4\5\3\2\2\u00f4R\3\2\2"+
		"\2\u00f5\u00f6\5\3\2\2\u00f6\u00f7\5\3\2\2\u00f7T\3\2\2\2\u00f8\u00f9"+
		"\5I%\2\u00f9\u00fa\5\3\2\2\u00faV\3\2\2\2\u00fb\u00fc\7K\2\2\u00fc\u00fd"+
		"\7p\2\2\u00fd\u00fe\7v\2\2\u00feX\3\2\2\2\u00ff\u0100\7N\2\2\u0100\u0101"+
		"\7q\2\2\u0101\u0102\7p\2\2\u0102\u0103\7i\2\2\u0103Z\3\2\2\2\u0104\u0105"+
		"\7D\2\2\u0105\u0106\7q\2\2\u0106\u0107\7q\2\2\u0107\u0108\7n\2\2\u0108"+
		"\\\3\2\2\2\u0109\u010a\7U\2\2\u010a\u010b\7v\2\2\u010b\u010c\7t\2\2\u010c"+
		"\u010d\7k\2\2\u010d\u010e\7p\2\2\u010e\u010f\7i\2\2\u010f^\3\2\2\2\u0110"+
		"\u0111\7F\2\2\u0111\u0112\7q\2\2\u0112\u0113\7w\2\2\u0113\u0114\7d\2\2"+
		"\u0114\u0115\7n\2\2\u0115\u0116\7g\2\2\u0116`\3\2\2\2\u0117\u0118\7p\2"+
		"\2\u0118\u0119\7g\2\2\u0119\u011a\7z\2\2\u011a\u011b\7v\2\2\u011b\u011c"+
		"\7K\2\2\u011c\u011d\7p\2\2\u011d\u011e\7v\2\2\u011eb\3\2\2\2\u011f\u0120"+
		"\7p\2\2\u0120\u0121\7g\2\2\u0121\u0122\7z\2\2\u0122\u0123\7v\2\2\u0123"+
		"\u0124\7N\2\2\u0124\u0125\7q\2\2\u0125\u0126\7p\2\2\u0126\u0127\7i\2\2"+
		"\u0127d\3\2\2\2\u0128\u0129\7p\2\2\u0129\u012a\7g\2\2\u012a\u012b\7z\2"+
		"\2\u012b\u012c\7v\2\2\u012c\u012d\7D\2\2\u012d\u012e\7q\2\2\u012e\u012f"+
		"\7q\2\2\u012f\u0130\7n\2\2\u0130f\3\2\2\2\u0131\u0132\7p\2\2\u0132\u0133"+
		"\7g\2\2\u0133\u0134\7z\2\2\u0134\u0135\7v\2\2\u0135\u0136\7F\2\2\u0136"+
		"\u0137\7q\2\2\u0137\u0138\7w\2\2\u0138\u0139\7d\2\2\u0139\u013a\7n\2\2"+
		"\u013a\u013b\7g\2\2\u013bh\3\2\2\2\u013c\u013d\7p\2\2\u013d\u013e\7g\2"+
		"\2\u013e\u013f\7z\2\2\u013f\u0140\7v\2\2\u0140\u0141\7N\2\2\u0141\u0142"+
		"\7k\2\2\u0142\u0143\7p\2\2\u0143\u0144\7g\2\2\u0144j\3\2\2\2\u0145\u0146"+
		"\7r\2\2\u0146\u0147\7t\2\2\u0147\u0148\7k\2\2\u0148\u0149\7p\2\2\u0149"+
		"\u014a\7v\2\2\u014al\3\2\2\2\u014b\u014f\t\3\2\2\u014c\u014e\t\4\2\2\u014d"+
		"\u014c\3\2\2\2\u014e\u0151\3\2\2\2\u014f\u014d\3\2\2\2\u014f\u0150\3\2"+
		"\2\2\u0150n\3\2\2\2\u0151\u014f\3\2\2\2\u0152\u0153\t\5\2\2\u0153\u0154"+
		"\3\2\2\2\u0154\u0155\b8\2\2\u0155p\3\2\2\2\n\2\u0082\u0095\u00a1\u00a9"+
		"\u00ad\u00b8\u014f\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}
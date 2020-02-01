# Makefile
Compilator := ghc
Flags := -i.
Sources := Main.hs Grammar.hs
Libs := Lexer.x Parser.y
Compiled := Lexer.hs Parser.hs
Object := parser

all: $(Object)

run:
		./$(Object)

$(Object): $(Compiled) $(Sources)
		$(Compilator) $(Flags) Main.hs -O2 -o $(Object)

$(Compiled): $(Libs)
		alex Lexer.x -o Lexer.hs
		happy Parser.y -o Parser.hs

clean:
		rm -rf *.o *.hi
		rm -rf $(Compiled)
		rm -f parser

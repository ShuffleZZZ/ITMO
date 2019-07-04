#Makefile
Compilator := g++
Flags := -std=c++11
Source := Find.cpp
Executable := find

all: $(Executable)

run: $(Executable)
	./$(Executable)

$(Executable):
	$(Compilator) $(Flags) $(Source) -o $(Executable)

clean:
	rm $(Executable)

#Makefile
Compilator := g++
Flags := -std=c++11
Source := Jit.cpp
Executable := jit

all: $(Executable)

run: $(Executable)
	./$(Executable)

$(Executable):
	$(Compilator) $(Flags) $(Source) -o $(Executable)

clean:
	rm $(Executable)

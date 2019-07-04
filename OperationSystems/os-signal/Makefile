#Makefile
Compilator := g++
Flags := -std=c++11
Source := Signal.cpp
Executable := signal

all: $(Executable)

run: $(Executable)
	./$(Executable)

$(Executable):
	$(Compilator) $(Flags) $(Source) -o $(Executable)

clean:
	rm $(Executable)

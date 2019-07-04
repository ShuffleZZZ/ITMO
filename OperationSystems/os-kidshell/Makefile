#Makefile
Compilator := g++
Flags := -std=c++11
Source := KidShell.cpp
Executable := kidshell

all: $(Executable)

run: $(Executable)
	./$(Executable)

$(Executable):
	$(Compilator) $(Flags) $(Source) -o $(Executable)

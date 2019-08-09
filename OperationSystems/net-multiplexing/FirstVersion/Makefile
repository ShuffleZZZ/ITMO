#Makefile
Compilator := g++
Flags := -std=c++11
Client := Client
ClientEx := client
Server := Server
ServerEx := server

all: $(Server) $(Client)

$(Server)Run: $(Server)
	./$(ServerEx)

$(Client)Run: $(Client)
	./$(ClientEx)

$(Server): $(Server).cpp
	$(Compilator) $(Flags) $(Server).cpp -o $(ServerEx)

$(Client): $(Client).cpp
	$(Compilator) $(Flags) $(Client).cpp -o $(ClientEx)

clean:
	rm $(ServerEx) $(ClientEx)

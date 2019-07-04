#Makefile
Compilator := g++ -std=c++11
StaticFlags := -c
DynamicFlags := -fPIC -c
DynamicLibFlags := -shared
Static := Swedishinator
Dynamic := Estonianator
DynamicLinked := Norwegianator
Libs := lib$(Static).a lib$(Dynamic).so lib$(DynamicLinked).so
Executable := main

all: $(Executable)

run: $(Executable)
	./$(Executable)

#Executable
$(Executable): $(Executable).o $(Libs)
	$(Compilator) $(Executable).o -L. -l$(Static) -L. -l$(Dynamic) -Wl,-rpath,. -ldl -o $(Executable)

$(Executable).o : $(Executable).cpp
	$(Compilator) $(StaticFlags) $(Executable).cpp -o $(Executable).o

#Static
lib$(Static).a: $(Static).o
	ar rcs lib$(Static).a $(Static).o

$(Static).o: $(Static).h $(Static).cpp
	$(Compilator) $(StaticFlags) $(Static).cpp -o $(Static).o

#Dynamic
lib$(Dynamic).so: $(Dynamic).o
	$(Compilator) $(DynamicLibFlags) -o lib$(Dynamic).so $(Dynamic).o

$(Dynamic).o: $(Dynamic).h $(Dynamic).cpp
	$(Compilator) $(DynamicFlags) $(Dynamic).cpp -o $(Dynamic).o

#Dynamic linked
lib$(DynamicLinked).so: $(DynamicLinked).o
	$(Compilator) $(DynamicLibFlags) -o lib$(DynamicLinked).so $(DynamicLinked).o

$(DynamicLinked).o: $(DynamicLinked).h $(DynamicLinked).cpp
	$(Compilator) $(DynamicFlags) $(DynamicLinked).cpp -o $(DynamicLinked).o

clean:
	rm -rf $(Executable) *.a *.o *.so

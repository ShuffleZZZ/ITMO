#include <iostream>
using namespace std;

class Animal  {

public:
	int age;
	Animal() {	}
	Animal (int a) {
		age=a;
	}
	virtual void showVoice (){
		cout << "buaaa";
	}
	void show() {
		cout << "sa";
	}
	
};

class Cat:public Animal {
public:	
    Cat():Animal() {};
	Cat(int a) {
		age=a;
	}
	void showVoice() {
			cout<<"meow";
		}
	};


class Horse:public Animal  {
	int age;
public:	Horse():Animal() {
	};
	Horse(int a) {
		age=a;
	};
    void showVoice() {
		
			cout<<"igogo";
	}
};

void write(Animal* a){
	a->showVoice();
}

int main() {
	Horse m;
	Cat c;
	Animal a;
	Cat c = <dynamic_cast> a;
	write(&c);
}


#include <iostream>

int a[5] = {1, 3, 5, 7, 9};

int &f(int i) { return a[i];}
	

int main() {
	for (int i = 0; i < 5; ++i) {
		std::cout << a[i] << ' ';
		f(i) = 2 * i + 2;
	}
	std::cout << '\n';
	for (int i = 0; i < 5; ++i) 
		std::cout << a[i] << ' ';
}
	

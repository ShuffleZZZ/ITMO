#include <iostream>

void f(int x, int y) {
	x *= 2;
	y *= 2;
}

void f2(int &x, int &y) {
	x *= 2;
	y *= 2;
}

int main() {
	int a = 3, b = 5;
	f(a, b);
	std::cout << "By value: a = " << a << " b = " << b << '\n';
	f2(a, b);
	std::cout << "By reference: a = " << a << " b = " << b << '\n';
	f(a, b);
	std::cout << "By value: a = " << a << " b = " << b << '\n';
}

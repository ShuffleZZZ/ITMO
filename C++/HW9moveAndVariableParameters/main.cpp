#include <iostream>

#include "Array.h"

template <typename T>
void print(const Array<T>& array)
{
	for (int i = 0; i < array.size(); ++i)
	{
		std::cout << array[i] << ' ';
	}
	std::cout << '\n';
}

int main()
{
	Array<int> a(5);
	Array<int> b(Array <int>(3));
	b[2] = -21;
	a[0] = 1;
	a[1] = b[2];
	Array<int> c = a;
	a[4] = 321;
	std::cout << "a is: ";
	print(a);
	std::cout << "b is: ";
	print(b);
	std::cout << "c is: ";
	print(c);
	Array<int> d = std::move(a);
	std::cout << "a is: ";
	print(a);
	std::cout << "d is: ";
	print(d);
	Array<int> e = b;
	std::cout << "b is: ";
	print(b);
	std::cout << "e is: ";
	print(e);
	Array<int> f(std::move(d));
	std::cout << "d is: ";
	print(d);
	std::cout << "f is: ";
	print(f);
	Array<double> g = Array<double> (7);
	Array<double> h(g);
	g[6] = -7.2;
	std::cout << "g is: ";
	print(g);
	std::cout << "h is: ";
	print(h);
}

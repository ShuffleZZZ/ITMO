#include "String.cpp"

int main()
{
	String a("hello0");
	String b(5, ' ');
	String c("this0");
	std::cout << a << '\n';
	String d("world0");
	String e(5, 'c');
	a = d;
	std::cout << d << '\n';
	d.reverse();
	std::cout << d << '\n';
	std::cout << c << '\n';
	a.append(e);
	c = a;
	std::cout << c << '\n';
	std::cout << a << '\n';
	std::cout << e << '\n';
	std::cout << a.strcmp(e) << ' ' << d.strcmp(c) << ' ' << d.strcmp(d) << '\n';
	d.copy(1, 4, a);
	std::cout << a << ' ';
	a.append(a);
	std::cout << a;
}

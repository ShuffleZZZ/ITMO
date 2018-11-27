#include <iostream>
#include <typeinfo>

void print_values() {}

template<typename T, typename... Args>
void print_values(const T& value, const Args... args)
{
	std::cout << typeid(value).name() << ": " << value << '\n';
	print_values(args...);
}

int main()
{
	int A[2] = {2, 1};
	print_values(0, 3.5, "Hello", 322, A);
}
	

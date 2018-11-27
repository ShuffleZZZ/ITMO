#include <iostream>

template<typename T, typename F>
bool compare(const T& a, const T& b, F (T::*func)() const)
{
	return (a.*func)() < (b.*func)();
}

int main()
{
	std::string s1("Elf");
    std::string s2("Archer");

    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false
    
    std::cout << "r1 is: " << r1 << '\n';
    std::cout << "r2 is: " << r2 << '\n';
}

#include <iostream>
#include <tuple>

template<int F, int S, typename... Args>
auto to_pair(const std::tuple& <Args...> t)
 -> decltype(std::make_pair(std::get<F> (t), std::get<S> (t)))
{
	return {std::get<F> (t), std::get<S> (t)};
}


int main()
{
	auto t = std::make_tuple(0, 3.5, "Hello");
	
	std::pair <double, const char*> p1 = to_pair <1, 2>(t);
	std::cout << p1.first << ' ' << p1.second << '\n';
	
	std::pair<int, double> p2 = to_pair <0, 1>(t);
	std::cout << p2.first << ' ' << p2.second;
}

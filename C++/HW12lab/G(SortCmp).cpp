#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <tuple>

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector <std::tuple <int, int, int>> a(n);
	for (int i = 0; i < n; ++i)
	{
		int b, c;
		std::cin >> b >> c;
		a[i] = std::make_tuple(b, c, i + 1);
	}
	std::sort(a.begin(), a.end(), [](std::tuple<int, int, int>& b,
									 std::tuple<int, int, int>& c)
	{
		int fi = std::get<0>(b);
		int se = std::get<0>(c);
		if (fi == se)
		{
			fi = std::get<1>(b);
			se = std::get<1>(c);
			if (fi == se)
			{
				return std::get<2>(b) < std::get<2>(c);
			} else
			{
				return fi < se;
			}
		} else
		{
			return fi > se;
		}
	});
	std::stringstream stream;
	for (auto& i : a)
	{
		stream << std::get<2>(i) << ' ';
	}
	std::cout << stream.str();
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector <int> a(n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> a[i];
	}
	int m;
	std::cin >> m;
	std::stringstream stream;
	for (int i = 0; i < m; ++i)
	{
		int b;
		std::cin >> b;
		auto it = std::lower_bound(a.begin(), a.end(), b);
		if (it != a.end())
		{
			int it1 = it - a.begin() + 1;
			int it2 = std::upper_bound(it, a.end(), b) - a.begin();
			if (it1 <= it2)
			{
				stream << it1 << ' ' << it2 << '\n';
			} else
			{
				stream << "-1 -1\n";
			}
		} else
		{
			stream << "-1 -1\n";
		}
	}
	std::cout << stream.str();
}

#include <iostream>
#include <list>
#include <sstream>

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	const int size = n;
	std::list <int> a;
	for (int i = 0; i < n; ++i)
	{
		a.push_back(i + 1);
	}
	for (int i = 0; i < m; ++i)
	{
		int l, r;
		std::cin >> l >> r;
		if (l != 1)
		{
			std::list <int>::iterator left;
			if (2 * l < size)
			{
				left = a.begin();
				std::advance(left, l - 1);
			} else
			{
				left = a.end();
				std::advance(left, l - size - 1);
				//std::cout << *left << " l\n";
			}
			std::list <int>::iterator right;
			if (2 * r < size + l)
			{
				right = left;
				std::advance(right, r - l + 1);
			} else
			{
				right = a.end();
				std::advance(right, r - size);
				//std::cout << *right << " r\n";
			}
			if (r + 2 > (l << 1))
			{
				a.splice(right, a, a.begin(), left);
			} else
			{
				a.splice(a.begin(), a, left, right);
			}
			/*for (auto i : a)
			{
				std::cout << i << ' ';
			}*/
		}
	}
	std::stringstream stream;
	for (auto i : a)
	{
		stream << i << ' ';
	}
	std::cout << stream.str();
}

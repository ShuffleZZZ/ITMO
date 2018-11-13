#include <iostream>
#include <vector>
#include <algorithm>

std::vector <int> a;

void binS(int i)
{
	int l = 0, r = a.size() - 1, m;
	std::string s;
	while (l < r + 1)
	{
		m = (l + r) >> 1;
		std::cout << "1 " << i << ' ' << a[m] << '\n';
		std::cout.flush();
		std::cin >> s;
		if (s == "YES")
		{
			r = m - 1;
		} else
		{
			l = m + 1;
		}
	}
	a.insert(a.begin() + m, i);
	if (s == "NO")
	{
		std::swap(a[m], a[m + 1]);
	}
}

int main()
{
	int n;
	std::cin >> n;
	a.push_back(1);
	for (int i = 1; i < n; ++i)
	{
		binS(i + 1);
	}
	std::cout << "0 ";
	for (auto c : a)
	{
		std::cout << c << ' ';
	}
	std::cout << '\n';
	std::cout.flush();
}

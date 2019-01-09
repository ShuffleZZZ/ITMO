#include <iostream>
#include <vector>
#include <algorithm>

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
		a[i] = i + 1;
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';
	while (std::next_permutation(a.begin(), a.end()))
	{
		for (int& i : a)
		{
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}
}


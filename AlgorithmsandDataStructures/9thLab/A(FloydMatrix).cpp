#include <iostream>
#include <algorithm>

int main()
{
	unsigned short n;
	std::cin >> n;
	int a[n][n];
	for (unsigned short i = 0; i < n; ++i)
	{
		for (unsigned short j = 0; j < n; ++j)
		{
			std::cin >> a[i][j];
		}
	}
	for (unsigned short i = 0; i < n; ++i)
	{
		for (unsigned short j = 0; j < n; ++j)
		{
			for (unsigned short k = 0; k < n; ++k)
			{
				a[j][k] = std::min(a[j][k], a[j][i] + a[i][k]);
			}
		}
	}
	for (unsigned short i = 0; i < n; ++i)
	{
		for (unsigned short j = 0; j < n; ++j)
		{
			std::cout << a[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

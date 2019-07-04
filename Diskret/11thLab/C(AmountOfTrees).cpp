#include <iostream>

const unsigned int INF = 1e9 + 7;

int main()
{
	unsigned short k, m;
	std::cin >> k >> m;
	bool c[m] = {};
	for (unsigned short i = 0; i < k; ++i)
	{
		unsigned short ind;
		std::cin >> ind;
		c[ind - 1] = 1;
	}
	long long trees[m + 1] = {}, pref[m + 1] = {};
	trees[0] = pref[0] = 1;
	for (unsigned short i = 1; i <= m; ++i)
	{
		for (unsigned short j = 0; j < i; ++j)
		{
			if (c[j])
			{
				trees[i] += pref[i - j - 1] % INF;
				trees[i] %= INF;
			}
		}
		for (unsigned short j = 0; j <= i; ++j)
		{
			pref[i] += trees[j] * trees[i - j];
			pref[i] %= INF;
		}
	}
	for (unsigned short i = 1; i <= m; ++i)
	{
		std::cout << trees[i] << ' ';
	}
}

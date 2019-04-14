#include <iostream>

const unsigned int INF = 998244353;

int main()
{
	unsigned short n, m;
	std::cin >> n >> m;
	unsigned int p[n + 1];
	for (unsigned short i = 0; i <= n; ++i)
	{
		std::cin >> p[i];
	}
	unsigned int q[m + 1];
	for (unsigned short i = 0; i <= m; ++i)
	{
		std::cin >> q[i];
	}
	unsigned short max = n > m ? n : m;
	std::cout << max << '\n';
	for (unsigned short i = 0; i <= max; ++i)
	{
		if (i > m)
		{
			std::cout << p[i];
		} else if (i > n) {
			std::cout << q[i];
		} else {
			std::cout << (p[i] + q[i]) % INF;
		}
		std::cout << ' ';
	}
	std::cout << '\n';
	max = n + m;
	unsigned int res[max + 1] = {};
	for (unsigned short i = 0; i <= n; ++i)
	{
		for (unsigned short j = 0; j <= m; ++j)
		{
			long long koef = res[i + j];
			koef += 1ll * p[i] * q[j] % INF;
			koef %= INF;
			if (koef < 0)
			{
				koef += INF;
			}
			res[i + j] = koef;
		}
	}
	/*for (unsigned short i = 0; i <= max; ++i)
	{
		long long koef = 0;
		for (unsigned short j = 0; j <= i; ++j)
		{
			if (j <= n && i <= j + m)
			{
				koef += 1ll * p[j] * q[i - j] % INF;
			}
		}
		koef %= INF;
		if (koef < 0)
		{
			koef += INF;
		}
		res[i] = koef;
	}*/
	while ((max + 1) && !res[max])
	{
		--max;
	}
	std::cout << max << '\n';
	for (unsigned short i = 0; i <= max; ++i)
	{
		std::cout << res[i] << ' ';
	}
	std::cout << '\n';
	max = 1010;
	long long div[max] = {};
	div[0] = 1;
	for (unsigned short i = 1; i < max; ++i)
	{
		long long koef = 0;
		for (unsigned short j = 0; j < i; ++j)
		{
			if (i <= m + j)
			{
				koef += 1ll * div[j] * q[i - j] % INF;
			}
		}
		koef %= INF;
		if (koef < 0)
		{
			koef += INF;
		}
		div[i] = -koef;
	}
	for (unsigned short i = 0; i < max - 10; ++i)
	{
		long long koef = 0;
		for (unsigned short j = 0; j <= i; ++j)
		{
			if (j <= n && i < j + max)
			{
				koef += 1ll * p[j] * div[i - j] % INF;
			}
			koef %= INF;
		}
		koef %= INF;
		if (koef < 0)
		{
			koef += INF;
		}
		std::cout << koef << ' ';
	}
	std::cout << '\n';
}

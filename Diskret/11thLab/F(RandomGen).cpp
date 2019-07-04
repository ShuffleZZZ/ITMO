#include <iostream>
#include <algorithm>

const long long INF = 104857601;

int main()
{
	unsigned short k;
	unsigned long long n;
	std::cin >> k >> n;
	long long a[2 * k] = {};
	for (unsigned short i = 0; i < k; ++i)
	{
		std::cin >> a[i];
	}
	long long c[k + 1];
	c[0] = 1;
	for (unsigned short i = 0; i < k; ++i)
	{
		unsigned int w;
		std::cin >> w;
		c[i + 1] = (INF - w) % INF;
	}
	--n;
	long long revC[k + 1], poly[k + 1];
	while (n >= k)
	{
		for (unsigned short i = k; i < 2 * k; ++i)
		{
			a[i] = 0;
			for (unsigned short j = 1; j <= k; ++j)
			{
				a[i] -= c[j] * a[i - j];
				a[i] %= INF;
				while (a[i] < 0)
				{
					a[i] += INF;
				}
			}
		}
		std::copy(c, c + k + 1, revC);
		for (unsigned short i = 1; i <= k; i += 2)
		{
			revC[i] = (INF - c[i]) % INF;
		}
		for (unsigned short i = 0; i <= k; ++i)
		{
			poly[i] = 0;
			for (unsigned short j = 0; j <= 2 * i; ++j)
			{
				if (j <= k && 2 * i <= k + j)
				{
					poly[i] += c[j] * revC[2 * i - j];
					poly[i] %= INF;
					if (poly[i] < 0)
					{
						poly[i] += INF;
					}
				}
			}
		}
		std::copy(poly, poly + k + 1, c);
		unsigned short ind = 0;
		for (unsigned short i = 0; i < 2 * k; ++i)
		{
			if ((n & 1) == (i & 1))
			{
				a[ind++] = a[i];
			}
		}
		n >>= 1;
	}
	std::cout << a[n] << '\n';
}

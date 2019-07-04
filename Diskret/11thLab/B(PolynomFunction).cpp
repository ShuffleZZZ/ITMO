#include <iostream>
#include <vector>
#include <cmath>

const unsigned int INF = 998244353;

long long gcd(long long a ,long long b, long long& x, long long& y)
{
	if (a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1;
	long long d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

long long reversed(long long a)
{
	long long x, y;
	long long g = gcd(a, INF, x, y);
	return x = (x % INF + INF) % INF;
}

int main()
{
	unsigned short n, m;
	std::cin >> n >> m;
	std::vector <long long> p(n + 1);
	std::vector <std::vector <long long>> koefs(m + 1);
	for (unsigned short i = 0; i <= n; ++i)
	{
		std::cin >> p[i];
	}
	koefs[0] = p;
	for (unsigned short k = 1; k <= m; ++k)
	{
		koefs[k].assign(koefs[k - 1].size() + n + 1, 0);
		for (unsigned short i = 0; i <= n; ++i)
		{
			for (unsigned int j = 0; j < koefs[k - 1].size(); ++j)
			{
				koefs[k][i + j] += p[i] * koefs[k - 1][j] % INF;
				koefs[k][i + j] %= INF;
				/*if (koefs[k][i + j] < 0)
				{
					koefs[k][i + j] += INF;
				}*/
			}
		}
		/*for (unsigned short i = 0; i < koefs[k].size(); ++i)
		{
			for (unsigned short j = 0; j <= i; ++j)
			{
				if (j < koefs[k - 1].size() && i <= j + n)
				{
					koefs[k][i] += koefs[k - 1][j] * p[i - j] % INF;
					koefs[k][i] %= INF;
					if (koefs[k][i] < 0)
					{
						koefs[k][i] += INF;
					}
				}
			}
		}*/
		/*std::vector<long long>::iterator ind = koefs[k].end() - 1;
		while (ind - 1 != koefs[k].begin() && !(*ind))
		{
			koefs[k].erase(ind--);
		}*/
	}
	/*for (auto i : koefs)
	{
		for (unsigned int j : i)
			std::cout << j << ' ';
		std::cout << '\n';
	}*/
	std::vector<long long> sqr(m, 0);
	sqr[0] = 1;
	long long koef = 2;
	sqr[1] = reversed(2);
	if (sqr[1] < 0)
	{
		sqr[1] = INF - sqr[1];
	}
	--koef;
	for (unsigned short i = 2; i < m; ++i)
	{
		long long num = 1, denom = 2;
		for (unsigned short j = 1; j < i; ++j)
		{
			num *= 1 - (j << 1);
			num %= INF;
			denom <<= 1;
			denom %= INF;
		}
		koef *= i;
		koef %= INF;
		denom *= koef;
		denom %= INF;
		sqr[i] = num * reversed(denom);
		sqr[i] %= INF;
		if (sqr[i] < 0)
		{
			sqr[i] += INF;
		}
	}
	std::vector <long long> exp(m, 0);
	koef = exp[0] = 1;
	for (unsigned short i = 1; i < m; ++i)
	{
		koef *= i;
		koef %= INF;
		exp[i] = reversed(koef);
		exp[i] %= INF;
		if (exp[i] < 0)
		{
			exp[i] += INF;
		}
	}
	std::vector <long long> log(m, 0);
	log[0] = 0;
	koef = -1;
	for (unsigned short i = 1; i < m; ++i)
	{
		log[i] = reversed(i);
		log[i] %= INF;
		if (log[i] < 0)
		{
			log[i] += INF;
		}
		koef *= -1;
		if (koef < 0)
		{
			koef += INF;
		}
		log[i] *= koef;
		log[i] %= INF;
	}
	unsigned int sz = koefs[koefs.size() - 1].size();
	std::vector <std::vector <long long>> ansSqr(sz), ansExp(sz), ansLog(sz);
	for (unsigned short i = 1; i < m; ++i)
	{
		for (unsigned int j = 0; j < koefs[i - 1].size(); ++j)
		{
			ansSqr[j].push_back((sqr[i] * koefs[i - 1][j]) % INF);
			ansExp[j].push_back((exp[i] * koefs[i - 1][j]) % INF);
			ansLog[j].push_back((log[i] * koefs[i - 1][j]) % INF);
		}
	}
	std::vector <long long> resSqr(sz, 0), resExp(sz, 0), resLog(sz, 0);
	resSqr[0] = resExp[0] = 1;
	for (unsigned short i = 0; i < sz; ++i)
	{
		for (unsigned int j = 0; j < ansSqr[i].size(); ++j)
		{
			resSqr[i] += ansSqr[i][j];
			resSqr[i] %= INF;
			resExp[i] += ansExp[i][j];
			resExp[i] %= INF;
			resLog[i] += ansLog[i][j];
			resLog[i] %= INF;
		}
	}
	for (unsigned short i = 0; i < m; ++i)
	{
		std::cout << resSqr[i] << ' ';
	}
	std::cout << '\n';
	for (unsigned short i = 0; i < m; ++i)
	{
		std::cout << resExp[i] << ' ';
	}
	std::cout << '\n';
	for (unsigned short i = 0; i < m; ++i)
	{
		std::cout << resLog[i] << ' ';
	}
	std::cout << '\n';
}

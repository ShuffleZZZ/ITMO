#include <iostream>
#include <vector>

const unsigned short num = 7;

std::vector <long long> ans;
std::string s;
unsigned int ind = 0;

long long factorial(long long l, long long r)
{
	long long res = 1;
	for (long long i = l + 1; i <= r; ++i)
	{
		res *= i;
	}
	return res;
}

std::vector <long long> parser()
{
	std::vector <long long> objects, weights(num, 0);
	if (s[ind] == 'B')
	{
		weights[1] = 1;
	} else if (s[ind] == 'L') {
		ind += 2;
		objects = parser();
		weights[0] = 1;
		for (unsigned short i = 1; i < num; ++i)
		{
			for (unsigned short j = 1; j <= i; ++j)
			{
				weights[i] += objects[j] * weights[i - j];
			}
		}
	} else if (s[ind] == 'P') {
		ind += 2;
		objects = parser();
		++ind; //comma
		std::vector <long long> objects2 = parser();
		for (unsigned short i = 0; i < num; ++i)
		{
			for (unsigned short j = 0; j <= i; ++j)
			{
				weights[i] += objects[j] * objects2[i - j];
			}
		}	
	} else if (s[ind] == 'S') {
		ind += 2;
		objects = parser();
		std::vector <std::vector <long long>> dp (num, std::vector <long long> (num, 0));
		dp[0] = std::vector <long long> (num, 1);
		dp[0][0] = weights[0] = 1;
		for (unsigned short n = 1; n < num; ++n)
		{
			for (unsigned short k = 1; k < num; ++k)
			{
				for (unsigned short i = 0; i <= n / k; ++i)
				{
					long long m = objects[k] + i - 1;
					if (m < 0)
					{
						m = 0;
					}
					long long C = factorial(m - i, m) / factorial(1, i);
					dp[n][k] += C * dp[n - i * k][k - 1];
				}
			}
			weights[n] = dp[n][n];
		}
	}
	++ind;
	return weights;
}

int main()
{
	std::getline(std::cin, s);
	ans = parser();
	for (unsigned short i = 0; i < num; ++i)
	{
		std::cout << ans[i] << ' ';
	}
	std::cout << '\n';
}

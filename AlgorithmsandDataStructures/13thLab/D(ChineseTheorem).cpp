#include <iostream>

int gcd(int a, int b, long long& x, long long& y)
{
	if (a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1;
	int d = gcd((b + a) % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

long long reversed(int a, int b)
{
	long long x, y;
	int g = gcd(a, b, x, y);
	return x = (x % b + b) % b;
}

int main()
{
	unsigned int a, b, n, m;
	std::cin >> a >> b >> n >> m;
	std::cout << (reversed(m, n) * m * ((a + n) % n) + reversed(n, m) * n * ((b + m) % m) + 1ll * n * m) % (1ll * n * m);
}

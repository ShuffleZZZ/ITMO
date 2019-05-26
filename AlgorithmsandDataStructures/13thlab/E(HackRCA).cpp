#include <iostream>

unsigned long long mult(unsigned long long x, unsigned long long y, unsigned long long p)
{
    unsigned long long res = 0;
    while (y > 0)
    {
        if (y & 1 == 1)
        {
            res = (res + x) % p;
        }
        y /= 2;
        x = (x + x) % p;
    }
    return res;
}

unsigned long long powr(unsigned long long x, unsigned long long y, unsigned long long p)
{
    unsigned long long res = 1;
    while (y > 0)
    {
        if (y & 1 == 1)
        {
            res = mult(res, x, p);
        }
        y >>= 1;
        x = mult(x, x, p);
    }
    return res;
}

long long gcd(unsigned int a, unsigned long long b, long long& x, long long& y)
{
	if (a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1;
	long long d = gcd((b + a) % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

unsigned long long reversed(unsigned int a, unsigned long long b)
{
	long long x, y;
	long long g = gcd(a, b, x, y);
	return x = (x + b) % b;
}

int main()
{
    unsigned int n, e, c;
    std::cin >> n >> e >> c;
    unsigned int p, q;
    for (unsigned int i = 2; i * i <= n; ++i)
    {
        if (!(n % i))
        {
            p = i;
            q = n / i;
            break;
        }
    }
    unsigned long long phi = 1ll * (p - 1) * (q - 1);
    unsigned long long d = reversed(e, phi);
    std::cout << powr(c, d, n);
}

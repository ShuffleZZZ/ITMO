#include <iostream>
#include <ctime>

const unsigned short MAGIC = 10;

long long mult(long long x, long long y, long long p)
{
    long long res = 0;
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

long long powr(long long x, long long y, long long p)
{
    long long res = 1;
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

bool prime(long long a)
{
    if (a == 2 || a == 3)
    {
        return 1;
    }
    if (a <= 1 || a % 2 == 0)
    {
        return 0;
    }
    long long d = a - 1;
    long long cnt = 0;
    while (d % 2 == 0)
    {
        ++cnt;
        d /= 2;
    }
    for (unsigned int i = 0; i < MAGIC; ++i)
    {
        long long rng = 2 + (rand() % (a - 2));
        long long x = powr(rng, d, a);
        if (x != 1 && x != a - 1)
        {
            for (unsigned int i = 1; i < cnt; ++i)
            {
                x = powr(x, 2, a);
                if (x == 1)
                {
                    return 0;
                }
                if (x == a - 1)
                {
                    break;
                }
            }
            if (x != a - 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    srand(NULL);
    unsigned short n;
    std::cin >> n;
    for (unsigned short i = 0; i < n; ++i)
    {
        long long a;
        std::cin >> a;
        if (prime(a))
        {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}

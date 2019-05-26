#include <iostream>
#include <vector>

const unsigned int MAX = 20000000, SQR = 4473;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
    unsigned int n;
    std::cin >> n;
    std::vector <bool> prime(MAX + 1, 1);
    prime[0] = prime[1] = 0;
    for (unsigned int i = 2; i <= MAX; ++i)
    {
        if (prime[i] && i <= SQR)
        {
            for (unsigned int j = i * i; j <= MAX; j += i)
            {
                prime[j] = 0;
            }
        }
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        unsigned int a;
        std::cin >> a;
        if (prime[a])
        {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}

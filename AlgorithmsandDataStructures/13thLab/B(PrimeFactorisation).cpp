#include <iostream>

const unsigned int MAX = 1e6;

unsigned int prime[MAX + 1] = {};

int main()
{
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
    unsigned int n;
    std::cin >> n;
    for (unsigned int i = 2; i * i <= MAX; ++i)
    {
    	for (unsigned int j = i << 1; j <= MAX; j += i)
    	{
    		if (!prime[j])
    		{
    			prime[j] = i;
    		}
    	}
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        unsigned int a;
        std::cin >> a;
        while (prime[a])
        {
        	std::cout << prime[a] << ' ';
        	a /= prime[a];
        }
        if (a != 1) {
            std::cout << a;
        }
        std::cout << '\n';
    }
}

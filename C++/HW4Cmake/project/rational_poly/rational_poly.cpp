#include <iostream>

#include "../lib_rational/lib_rational.h"

int compute(int* coef, int n, int q)
{
	int sum = coef[0];
	for (int i = 1; i < n; ++i)
	{
		sum = sum * q + coef[i];
	}
	return sum;
}

int main()
{
	std::cout << "Enter highest degree and first value to evaluate\n";
	int n1, q1;
    std::cin >> n1 >> q1;
    int coef1[n1 + 1];
    std::cout << "Enter first coefficients\n";
    for (int i = 0; i <= n1; ++i) 
    {
    	std::cin >> coef1[i];
    }
    std::cout << "Enter highest degree and second value to evaluate\n";
    int n2, q2;
    std::cin >> n2 >> q2;
    int coef2[n2 + 1];
    std::cout << "Enter second coefficients\n";
    for (int i = 0; i <= n2; ++i) 
    {
    	std::cin >> coef2[i];
    }
    int res1 = compute(coef1, n1 + 1, q1);
    int res2 = compute(coef2, n2 + 1, q2);
    if (res1 > res2)
    {
    	std::cout << "Polynom evaluation with q1 more than with q2\n";
    } else if (res1 == res2)
    {
    	std::cout << "Polynom evaluations are equal\n";
    } else 
    {
    	std::cout << "Polynom evaluation with q2 more than with q1\n";
    }
    std::cout << "With q1 = " << res1 << '\n';
    std::cout << "With q2 = " << res2 << '\n';
}
    
    

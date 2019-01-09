#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	int n, k;
	std::cin >> n >> k;
	if (n == 1)
	{
		std::cin >> k >> k >> k >> k;
		std::cout << k;
		return 0;
	}
	std::vector <int> a(n);
	int A, B, C;
	std::cin >> A >> B >> C >> a[0] >> a[1];
	for (int i = 2; i < n; ++i)
	{
		a[i] = A * a[i - 2] + B * a[i - 1] + C;
	}
	std::nth_element(a.begin(), a.begin() + k - 1, a.end());
	std::cout << a[k - 1];
}
	

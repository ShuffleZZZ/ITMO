#include <iostream>
#include <sstream>
#include <ext/rope>

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	__gnu_cxx::rope <int> a;
	for (int i = 0; i < n; ++i)
	{
		a.push_back(i + 1);
	}
	for (int i = 0; i < m; ++i)
	{
		int l, r;
		std::cin >> l >> r;
		if (l != 1)
		{
			r = r - l + 1;
			--l;
			__gnu_cxx::rope <int> temp = a.substr(l, r);
			a.erase(l, r);
			a.insert(a.mutable_begin(), temp);
		}
	}
	std::stringstream stream;
	for (auto i : a)
	{
		stream << i << ' ';
	}
	std::cout << stream.str();
}

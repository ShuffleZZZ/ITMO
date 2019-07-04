#include <iostream>
#include <algorithm>

const long long magic = 31;

int main()
{
	std::string s;
	int m;
	std::cin >> s >> m;
	long long pows[s.size()], hash[s.size()];
	pows[0] = 1;
	hash[0] = s[0] - 'a' + 1;
	for (int i = 1; i < s.size(); ++i)
	{
		pows[i] = pows[i - 1] * magic;
		hash[i] = (s[i] - 'a' + 1) * pows[i] + hash[i - 1];
	}
	for (int i = 0; i < m; ++i)
	{
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		if (b - a != d - c)
		{
			std::cout << "No\n";
		} else
		{
			if (c < a)
			{
				std::swap(a, c);
				std::swap(b, d);
			}
			long long hash1 = hash[b - 1] * pows[c - a];
			long long hash2 = hash[d - 1];
			if (a > 1)
			{
				hash1 -= hash[a - 2] * pows[c - a];
			}
			if (c > 1)
			{
				hash2 -= hash[c - 2];
			}
			if (hash1 == hash2)
			{
				std::cout << "Yes\n";
			} else
			{
				std::cout << "No\n";
			}
		}
	}
}

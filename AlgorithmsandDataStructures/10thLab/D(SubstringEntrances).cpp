#include <iostream>
#include <vector>

int main()
{
	std::string s, t, sum;
	std::cin >> s >> t;
	sum = s + ' ' + t;
	int func[sum.size()];
	func[0] = 0;
	for (int i = 1; i < sum.size(); ++i)
	{
		int cur = func[i - 1];
		while (cur > 0 && sum[i] != sum[cur])
		{
			cur = func[cur - 1];
		}
		func[i] = sum[i] == sum[cur] ? cur + 1 : cur;
	}
	std::vector <int> ans;
	for (int i = s.size(); i < sum.size(); ++i)
	{
		if (func[i] == s.size())
		{
			ans.push_back(i + 1 - (s.size() << 1));
		}
	}
	std::cout << ans.size() << '\n';
	for (auto i : ans)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';
}

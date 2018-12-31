#include <iostream>

int main()
{
	std::string s;
	std::cin >> s;
	int func[s.size()];
	func[0] = 0;
	for (int i = 1; i < s.size(); ++i)
	{
		int cur = func[i - 1];
		while (cur > 0 && s[i] != s[cur])
		{
			cur = func[cur - 1];
		}
		func[i] = s[i] == s[cur] ? cur + 1 : cur;
	}
	int cur = func[s.size() - 1];
	while (cur && (s.size() % (s.size() - cur)))
	{
		cur = func[cur - 1];
	}
	std::cout << s.size() - cur << '\n';
}

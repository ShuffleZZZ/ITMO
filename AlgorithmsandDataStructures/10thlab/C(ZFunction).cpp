#include <iostream>

int main()
{
	std::string s;
	std::cin >> s;
	int func[s.size()], l = 0, r = 0;
	for (int i =  1; i < s.size(); ++i)
	{
		func[i] = std::max(0, std::min(r - i, func[i - l]));
		while (i + func[i] < s.size() && s[func[i]] == s[i + func[i]])
		{
			++func[i];
		}
		if (i + func[i] > r)
		{
			l = i;
			r = l + func[i];
		}
	}
	for (int i = 1; i < s.size(); ++i)
	{
		std::cout << ' ' << func[i];
	}
}

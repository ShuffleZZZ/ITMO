#include <iostream>
#include <unordered_set>
#include <sstream>

const int STRING_SIZE = 18;

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	std::unordered_set <int> set;
	std::stringstream stream;
	char s[STRING_SIZE];
	while (std::cin.getline(s, STRING_SIZE))
	{
		int x = std::atoi(&s[7]);
		if (s[0] == 'i')
		{
			set.insert(x);
		} else if (s[0] == 'd')
		{
			set.erase(x);
		} else if (s[0] == 'e')
		{
			if (set.count(x))
			{
				stream << "true\n";
			} else
			{
				stream << "false\n";
			}
		}
	}
	std::cout << stream.str();
}

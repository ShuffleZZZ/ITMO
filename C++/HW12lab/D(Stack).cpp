#include <iostream>
#include <stack>
#include <sstream>

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	std::stack <int> stack;
	int m;
	std::cin >> m;
	std::stringstream stream;
	for (int i = 0; i < m; ++i)
	{
		char s;
		std::cin >> s;
		if (s == '+')
		{
			int n;
			std::cin >> n;
			stack.push(n);
		} else if (s == '-')
		{
			stream << stack.top() << '\n';
			//std::cout << stack.top() << '\n';
			stack.pop();
		}
	}
	std::cout << stream.str();
}

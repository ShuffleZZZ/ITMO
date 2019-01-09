#include <iostream>
#include <queue>
#include <sstream>

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	std::queue <int> queue;
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
			queue.push(n);
		} else if (s == '-')
		{
			stream << queue.front() << '\n';
			//std::cout << queue.front() << '\n';
			queue.pop();
		}
	}
	std::cout << stream.str();
}

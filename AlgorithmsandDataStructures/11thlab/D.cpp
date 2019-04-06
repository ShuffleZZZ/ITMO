#include <iostream>
#include <vector>

std::vector <std::vector <int>> graph;
std::vector <int> matching;
std::vector <bool> came;

bool dfs(int i)
{
	if (!came[i])
	{
		came[i] = 1;
		for (auto j : graph[i])
		{
			if (matching[j] == -1 || dfs(matching[j]))
			{
				matching[j] = i;
				return 1;
			}
		}
	}
	return 0;
}
	

int main()
{
	int n, m;
	std::cin >> n >> m;
	graph.resize(n);
	matching.resize(m, -1);
	for (int i = 0; i < n; ++i)
	{
		int a;
		std::cin >> a;
		if (a != 0)
		{
			graph[i].push_back(a - 1);
			--i;
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i)
	{
		came.assign(n, 0);
		if (dfs(i)) 
		{
			++ans;
		}
	}
	std::cout << ans << '\n';
	for (int i = 0; i < m; ++i)
	{
		if (matching[i] != -1)
		{
			std::cout << matching[i] + 1 << ' ' << i + 1 << '\n';
		}
	}
}
		
	

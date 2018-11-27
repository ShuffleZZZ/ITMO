#include <iostream>
#include <vector>
#include <queue>

std::vector <int> p, came;
std::vector <std::vector <int>> counted;
bool ans = 1;

bool cross(std::pair <int, int> fi, std::pair <int, int> se)
{
	return p[fi.second] < p[se.second] && p[fi.second] > p[se.first] && p[fi.first] < p[se.first];
}

void dfs(int i)
{
	for (auto j : counted[i])
	{
		if (came[j] == 0)
		{
			came[j] -= came[i];
			dfs(j);
		} else
		{
			ans &= (came[i] != came[j]);
		}
	}
}
			

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::pair <int, int> graph[m];
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		std::cin >> u >> v;
		graph[i] = {u - 1, v - 1};
	}
	p.resize(n);
	for (int i = 0; i < n; ++i)
	{
		int a;
		std::cin >> a;
		p[a - 1] = i;
	}
	for (std::pair <int, int>& i : graph)
	{
		if (p[i.second] < p[i.first])
		{
			int tmp = i.first;
			i.first = i.second;
			i.second = tmp;
		}
	}
	counted.resize(m);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (cross(graph[i], graph[j]) || cross(graph[j], graph[i]))
			{
				counted[i].push_back(j);
			}
		}
	}
	came.resize(m, 0);
	for (int i = 0; i < m; ++i)
	{
		if (came[i] == 0)
		{
			came[i] = 1;
			dfs(i);
		}
	}
	if (ans)
	{
		std::cout << "YES" << '\n';
		for (int i = 0; i < n; ++i)
		{
			std::cout << (p[i] << 1) << " 0 ";
		}
		std::cout << '\n';
		for (int i = 0; i < m; ++i)
		{
			std::cout << p[graph[i].first] + p[graph[i].second] << ' ' << 
			abs(p[graph[i].first] - p[graph[i].second]) * came[i] << '\n';
		}
	} else
	{
		std::cout << "NO" << '\n';
	}
}

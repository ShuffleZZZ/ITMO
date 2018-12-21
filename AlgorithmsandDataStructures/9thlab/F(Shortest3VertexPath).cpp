#include <iostream>
#include <vector>
#include <set>

const long long INF = 8ll * 1e18;

std::vector <std::vector <std::pair <unsigned int, unsigned int>>> a;
std::vector <unsigned long long> e;

void dijkstra(unsigned int u)
{
	std::set <std::pair <unsigned long long, unsigned int>> q;
	q.insert({0, u});
	while (!q.empty())
	{
		unsigned int minp = q.begin() -> second;
		q.erase(q.begin());
		for (auto i : a[minp])
		{
			unsigned long long fi = e[minp] + i.second;
			unsigned int se = i.first;
			if (fi < e[se])
			{
				q.erase({e[se], se});
				e[se] = fi;
				q.insert({e[se], se});
			}
		}
	}
}

int main()
{
	unsigned int n, m;
	std::cin >> n >> m;
	a.resize(n);
	for (unsigned int i = 0; i < m; ++i)
	{
		unsigned int u, v, w;
		std::cin >> u >> v >> w;
		a[u - 1].push_back({v - 1, w});
		a[v - 1].push_back({u - 1, w});
	}
	unsigned int a, b, c;
	std::cin >> a >> b >> c;
	--a, --b, --c;
	long long ways[3];
	e.resize(n, INF);
	e[a] = 0;
	dijkstra(a);
	ways[0] = e[b];
	ways[1] = e[c];
	e.assign(n, INF);
	e[b] = 0;
	dijkstra(b);
	ways[2] = e[c];
	if ((ways[0] == INF && ways[1] == INF) || 
	(ways[1] == INF && ways[2] == INF) || 
	(ways[0] == INF && ways[2] == INF))
	{
		std::cout << -1;
	} else if (ways[0] == INF)
	{
		std::cout << ways[1] + ways[2];
	} else if (ways[1] == INF)
	{
		std::cout << ways[0] + ways[2];
	} else if (ways[2] == INF)
	{
		std::cout << ways[0] + ways[1];
	} else
	{
		std::cout << std::min((long long)ways[0] + ways[1], 
		std::min((long long)ways[0] + ways[2],
				(long long)ways[1] + ways[2]));
	}
}
	
	

#include <iostream>
#include <vector>

const long long INF = (long long) 1e20;

struct edge
{
	int u, v;
	long long w;
};

std::vector <std::vector <unsigned int>> a;
std::vector <bool> came;

void dfs(int i)
{
	came[i] = 1;
	for (auto j : a[i])
	{
		if (!came[j])
		{
			dfs(j);
		}
	}
}

int main()
{
	unsigned int n, m, s;
	std::cin >> n >> m >> s;
	edge graph[m];
	a.resize(n);
	std::vector <long long> d(n, INF);
	came.resize(n, 0);
	d[s - 1] = 0;
	for (int i = 0; i < m; ++i)
	{
		std::cin >> graph[i].u >> graph[i].v >> graph[i].w;
		--graph[i].u;
		--graph[i].v;
		a[graph[i].u].push_back(graph[i].v);
	}
	for (int i = 0; i < n - 1; ++i)
	{
		for (auto j : graph)
		{
			long long int cont = std::max(-INF, (long long) (d[j.u] + j.w));
			if (d[j.u] < INF && cont < d[j.v])
			{
				d[j.v] = cont;
			}
		}
	}
	std::vector <long long> oldbl(d); // HA MECTE 8)
	for (auto j : graph)
	{
		long long int cont = std::max(-INF, (long long) (d[j.u] + j.w));
		if (d[j.u] < INF && cont < d[j.v])
		{
			d[j.v] = cont;
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if (d[i] != oldbl[i])
		{
			dfs(i);
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if (came[i])
		{
			std::cout << "-\n";
		} else if (d[i] == INF)
		{
			std::cout << "*\n";
		} else
		{
			std::cout << oldbl[i] << '\n';
		}
	}
}

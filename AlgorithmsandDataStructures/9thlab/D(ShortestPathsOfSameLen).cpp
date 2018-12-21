#include <iostream>
#include <vector>

const int INF = 1e7;

struct edge
{
	int u, v, w;
};

int main()
{
	int n, m, k, s;
	std::cin >> n >> m >> k >> s;
	edge a[m];
	std::vector <std::vector <int>> d(k + 1, std::vector <int> (n, INF));
	d[0][s - 1] = 0;
	for (int i = 0; i < m; ++i)
	{
		std::cin >> a[i].u >> a[i].v >> a[i].w;
		--a[i].u;
		--a[i].v;
	}
	for (int i = 0; i < k; ++i)
	{
		for (auto g : a)
		{
			if (d[i][g.u] < INF)
			{
				d[i + 1][g.v] = std::min(d[i + 1][g.v], d[i][g.u] + g.w);
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if (d[k][i] != INF)
		{
			std::cout << d[k][i] << '\n';
		} else 
		{
			std::cout << -1 << '\n';
		}
	}
}

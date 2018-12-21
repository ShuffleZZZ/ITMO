#include <iostream>
#include <vector>
#include <algorithm>

const int FILL = 1e9;

struct edge
{
	int u, v, w;
};

int main()
{
	int n;
	std::cin >> n;
	std::vector <edge> graph;
	std::vector <int> d(n, FILL), came(n, -1);
	d[0] = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int w;
			std::cin >> w;
			if (w != 100000)
			{
				graph.push_back({i, j, w});
			}
		}
	}
	int upd;
	for (int i = 0; i < n; ++i)
	{
		upd = -1;
		for (auto j : graph)
		{
			int cont = d[j.u] + j.w;
			if (cont < d[j.v])
			{
				upd = j.v;
				d[upd] = std::max(-FILL, cont);
				came[upd] = j.u;
			}
		}
	}
	if (upd != -1)
	{
		std::cout << "YES\n";
		std::vector<int> ans;
		for (int i = 0; i < n; ++i)
		{
			upd = came[upd];
		}
		int cond = upd;
		while (!(upd == cond) || !(ans.size() > 1))
		{
			ans.push_back(cond + 1);
			cond = came[cond];
		}
		std::cout << ans.size() << '\n';
		for (int i = ans.size() - 1; i > -1; --i)
		{
			std::cout << ans[i] << ' ';
		}
		std::cout << '\n';
	} else
	{
		std::cout << "NO\n";
	}
}

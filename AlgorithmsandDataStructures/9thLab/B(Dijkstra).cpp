#include <iostream>
#include <vector>
#include <set>

const int MAX = 1e6;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	std::vector <std::vector <std::pair <int, int>>> a(n);
	std::vector <int> b(n, MAX);
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		std::cin >> u >> v >> w;
		a[u - 1].push_back({v - 1, w});
		a[v - 1].push_back({u - 1, w});
	}
	b[0] = 0;
	std::set <std::pair <int, int>> q;
	q.insert({0, 0});
	while (!q.empty())
	{
		int minp = q.begin() -> second;
		q.erase(q.begin());
		for (auto i : a[minp])
		{
			int fi = b[minp] + i.second;
			int se = i.first;
			if (fi < b[se])
			{
				q.erase({b[se], se});
				b[se] = fi;
				q.insert({b[se], se});
			}
		}
	}
	for (auto i : b)
	{
		std::cout << i << ' ';
	}
}

#include <fstream>
#include <vector>
#include <set>

int main()
{
	std::ifstream in;
	in.open("dwarf.in");
	std::ofstream out;
	out.open("dwarf.out");
	int n, m;
	in >> n >> m;
	unsigned int c[n];
	std::set <std::pair <unsigned int, int>> q;
	for (int i = 0; i < n; ++i)
	{
		in >> c[i];
		q.insert({c[i], i});
	}
	std::vector <std::pair <int, int>> b[n];
	for (int i = 0; i < m; ++i)
	{
		int a, x, y;
		in >> a >> x >> y;
		b[x - 1].push_back({y - 1, a - 1});
		b[y - 1].push_back({x - 1, a - 1});
	}
	while (!q.empty())
	{
		int minp = q.begin() -> second;
		q.erase(q.begin());
		for (auto i : b[minp])
		{
			unsigned int fi = c[minp] + c[i.first];
			int se = i.second;
			if (fi < c[se])
			{
				q.erase({c[se], se});
				c[se] = fi;
				q.insert({c[se], se});
			}
		}
	}
	out << c[0] << '\n';
	in.close();
	out.close();
}

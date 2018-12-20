#include <fstream>
#include <vector>
#include <algorithm>

std::vector <std::vector <unsigned int>> graph;
std::vector <int> matching, ans;
std::vector <bool> came;

bool dfs(unsigned int i)
{
	if (!came[i])
	{
		came[i] = 1;
		for (auto j : graph[i])
		{
			if (matching[j] == -1 || dfs(matching[j]))
			{
				matching[j] = i;
				ans[matching[j]] = j;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	std::ifstream in;
	in.open("matching.in");
	std::ofstream out;
	out.open ("matching.out");
	unsigned int n;
	in >> n;
	graph.resize(n);
	matching.resize(n, -1);
	ans = matching;
	std::vector <std::pair <unsigned int, unsigned int>> edge;
	for (unsigned int i = 0; i < n; ++i)
	{
		unsigned int w;
		in >> w;
		edge.push_back({w, i});
	}
	std::sort(edge.rbegin(), edge.rend());
	for (unsigned int i = 0; i < n; ++i)
	{
		unsigned int e;
		in >> e;
		for (unsigned int j = 0; j < e; ++j)
		{
			unsigned int r;
			in >> r;
			graph[i].push_back(r - 1);
		}
	}
	for (unsigned int i = 0; i < n; ++i)
	{
		came.assign(n, 0);
		dfs(edge[i].second);
	}
	for (auto i : ans)
	{
		out << i + 1 << ' ';
	}
	out << '\n';
	in.close();
	out.close();
}	

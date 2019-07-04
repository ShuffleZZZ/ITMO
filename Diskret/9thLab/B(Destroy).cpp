#include <fstream>
#include <algorithm>
#include <vector>

class g
{
	public:
		g() : i(0), p(0), c(0), w(0) {};
		explicit g(const unsigned int i, const unsigned int a,
					const unsigned int b, const unsigned long long c) 
					: i(i), p(a), c(b), w(c) {};
					
		bool operator <(const g& b) const
		{
			return w < b.w;
		}
		
		unsigned int i, p, c;
		unsigned long long w;
};

std::vector <unsigned int> p;

unsigned int get(unsigned int i)
{
	if (p[i] == i)
	{
		return i;
	}
	return p[i] = get(p[i]);
}
	
int main()
{
	std::ifstream in;
	in.open("destroy.in");
	std::ofstream out;
	out.open ("destroy.out");
	unsigned int n, m;
	unsigned long long s;
	in >> n >> m >> s;
	std::vector <g> graph;
	for (unsigned int i = 0; i < m; ++i)
	{
		unsigned int a, b;
		unsigned long long c;
		in >> a >> b >> c;
		graph.push_back(g(i, a - 1, b - 1, c));
	}
	std::sort(graph.begin(), graph.end());
	for (unsigned int i = 0; i < n; ++i)
	{
		p.push_back(i);
	}
	std::vector <bool> came(m, 0);
	for (int i = m - 1; i >= 0; --i)
	{
		unsigned int p1 = get(graph[i].c);
		unsigned int p2 = get(graph[i].p);
		if (p1 != p2)
		{
			came[i] = 1;
			p[p1] = p2;
		}
	}
	std::vector <unsigned int> ans;
	for (unsigned int i = 0; i < m; ++i)
	{
		if (!came[i] && graph[i].w <= s)
		{
			ans.push_back(graph[i].i);
			s -= graph[i].w;
		}
	}
	out << ans.size() << '\n';
	std::sort(ans.begin(), ans.end());
	for (auto i : ans)
	{
		out << i + 1 << ' ';
	}
	out << '\n';
	in.close();
	out.close();
}

#include <fstream>
#include <vector>
#include <set>
#include <queue>

const int N = 105, M = 5050;

class g
{
	public:
		g() : from(0), to(0), c(0) {};
		explicit g(const int from, const int to, const int c)
		: from(from), to(to), c(c) {};
		int from, to, c;
};

std::vector <int> p, s;

int get(int x)
{
	if (p[x] == x)
	{
		return x;
	}
	return p[x] = get(p[x]);
}

void uni(int x, int y)
{
	x = get(x);
	y = get(y);
	if (x != y)
	{
		if (s[x] < s[y])
		{
			std::swap(x, y);
		}
		if (s[x] == s[y])
		{
			++s[x];
		}
		p[y] = x;
	}
}

int main()
{
	std::ifstream in;
	in.open("rainbow.in");
	std::ofstream out;
	out.open ("rainbow.out");
	int n, m;
	in >> n >> m;
	g graph[M];
	std::set <int> excess, ans;
	std::vector <bool> side(N, 0);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		in >> a >> b >> c;
		graph[i] = g(a - 1, b - 1, c);
		excess.insert(i);
	}
	bool maxS = 0;
	while (!maxS)
	{
		std::vector <std::vector <int>> matrix(M, std::vector <int> ());
		for (auto i : ans)
		{
			s.assign(N, 0);
			p.resize(N);
		 	for (int j = 0; j < N; j++)
			{
				p[j] = j;
			}
			for (auto j : ans)
			{
				if (i != j)
				{
					uni(graph[j].from, graph[j].to);
				}
			}
			for (auto j : excess)
			{
				if (graph[i].c == graph[j].c || !side[graph[j].c])
				{
					matrix[j].push_back(i);
				}
				if (get(graph[j].to) != get(graph[j].from))
				{
					matrix[i].push_back(j);
				}
			}
		}
		std::vector <bool> Xl(M, 0), Xr(M, 0);
		s.assign(N, 0);
		p.resize(N);
		for (int i = 0; i < N; i++)
		{
			p[i] = i;
		}
		for (auto i : ans)
		{
			uni(graph[i].to, graph[i].from);
		}
		std::vector <bool> came(M, 0);
		std::vector <int> back(M, 0);
		std::queue <int> q;
		for (auto i : excess)
		{
			if (get(graph[i].to) != get(graph[i].from))
			{
				Xl[i] = came[i] = 1;
				back[i] = -1;
				q.push(i);
			}
			Xr[i] = side[graph[i].c] ? 0 : 1;
		}
		maxS = 1;
		while (!q.empty())
		{
			if (Xr[q.front()])
			{
				int a = q.front();
				while (a != -1)
				{
					side[graph[a].c] = excess.find(a) != excess.end();
					if (side[graph[a].c])
					{
						ans.insert(a);
						excess.erase(a);
					} else
					{
						excess.insert(a);
						ans.erase(a);
					}
					a = back[a];
				}
				q.pop();
				maxS = 0;
				break;
			} else
			{
				for (auto i : matrix[q.front()])
				{
					if (!came[i])
					{
						came[i] = 1;
						back[i] = q.front();
						q.push(i);
					}
				}
				q.pop();
			}	
		}
	}
	out << ans.size() << '\n';
	for (auto i : ans)
	{
		out << i + 1 << ' ';
	}
	out << '\n';
	in.close();
	out.close();
}

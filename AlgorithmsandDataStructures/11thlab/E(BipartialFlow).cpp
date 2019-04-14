#include <iostream>
#include <vector>
#include <algorithm>

std::vector <std::vector <char>> table;
std::vector <std::vector <unsigned short>> graph, graphB;
std::vector <bool> came, cameW, cameB;
std::vector <short> p;

class Ans
{
	public:
		unsigned short x, y;
		bool diag;
		char c;
		Ans(bool diag, unsigned short x, unsigned short y, char c)
		 : diag(diag), x(x), y(y), c(c) {}
};

std::ostream& operator << (std::ostream& out, const Ans& ans)
{
	out << (ans.diag ? 2 : 1) << ' ' << ans.x + 1 << ' ' << ans.y + 1 << ' ' << ans.c << '\n';
	return out;
}

bool dfs(unsigned short i)
{
    came[i] = 1;
    for (unsigned short j : graph[i])
	{
        if (p[j] == -1 || (!came[p[j]] && dfs(p[j])))
		{
            p[j] = i;
            return 1;
        }
    }
    return 0;
}

void dfs2(unsigned short i)
{
    cameW[i] = 1;
    for (unsigned short j : graph[i])
	{
        cameB[j] = 1;
        if (p[j] != -1 && !cameW[p[j]])
		{
            dfs2(p[j]);
        }
    }
}

int main()
{
	unsigned short n, m;
    std::cin >> n >> m;
    unsigned short N = n + m - 1;
    unsigned short ans = n * m + 200;
    unsigned short diag = 2;
    table.resize(n, std::vector <char> (m));
    for (unsigned short i = 0; i < n; i++)
	{
        for (unsigned short j = 0; j < m; j++)
		{
            std::cin >> table[i][j];
        }
    }
    std::vector <Ans> res;
    while (diag)
    {
    	--diag;
		graph.assign(N, std::vector <unsigned short> ());
		graphB.assign(N, std::vector <unsigned short> ());
        for (unsigned short i = 0; i < n; i++)
		{
            for (unsigned short j = 0; j < m; j++)
			{
				if (((i + j) % 2 == diag) == (table[i][j] == 'B'))
				{
					graph[i + j].push_back(m - 1 + i - j);
                    graphB[m - 1 + i - j].push_back(i + j);
                }
            }
        }
        unsigned short upd = 0;
        came.assign(N, 0);
        p.assign(N, -1);
        for (unsigned short i = 0; i < N; i++)
		{
			came.assign(N, 0);
            if (dfs(i))
			{
                ++upd;
            }
        }
        if (upd < ans)
		{
            ans = upd;
            std::vector <bool> in(N);
            cameW.assign(N, 0);
            cameB.assign(N, 0);
            res.clear();
            for (unsigned short i = 0; i < N; i++)
			{
                if (p[i] != -1)
				{
                    graph[p[i]].erase(std::find(graph[p[i]].begin(), graph[p[i]].end(), i));
                    in[p[i]] = 1;
                }
            }
            for (unsigned short i = 0; i < N; i++)
			{
                if (!in[i] && !cameW[i])
				{
                    dfs2(i);
                }
            }
            for (unsigned short i = 0; i < N; i++)
			{
                if (!cameW[i])
				{
                    unsigned short x;
                    unsigned short y;
                    if (i < n)
                    {
                    	x = i;
                    	y = 0;
                    } else {
                    	x = n - 1;
                    	y = i - n + 1;
                    }
                    res.push_back(Ans(0, x, y, (x + y) % 2 == diag ? 'W' : 'B'));
                }
                if (cameB[i])
				{
                    unsigned short x;
                    unsigned short y = m - 1;
                    if (i < n)
                    {
                    	x = i;
                    } else {
                    	x = n - 1;
                    	y -= i - n + 1;
                    }
                    res.push_back(Ans(1, x, y, (x + y) % 2 == diag ? 'W' : 'B'));
                }
            }
        }
    }
    std::cout << ans << '\n';
    for (Ans& i : res)
	{
		std::cout << i;
	}
}

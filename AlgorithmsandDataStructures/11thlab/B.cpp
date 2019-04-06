#include <iostream>
#include <vector>
#include <queue>
#include <map>

const unsigned int INF = 1e7 + 100;

std::vector <bool> came;
std::vector <short> prev;
std::vector <std::vector <unsigned int>> nums;
std::map <std::pair <unsigned short, unsigned short>,
		  std::pair <unsigned short, unsigned int>> pipeline;
unsigned short n;

bool bfs()
{
	came.assign(n, 0);
	prev.assign(n, 0);
	std::queue <unsigned short> q;
	q.push(0);
	came[0] = 1;
	prev[0] = -1;
	while (!q.empty())
	{
		for (unsigned short i = 0; i < n; ++i)
		{
			if (!came[i] && nums[q.front()][i] > 0)
			{
				came[i] = 1;
				q.push(i);
				prev[i] = q.front();
			}
		}
		q.pop();
	}
	return came[n - 1];
}

void dfs(unsigned short v)
{
	came[v] = 1;
	for (unsigned short i = 0; i < n; ++i)
	{
		if (!came[i] && nums[v][i])
		{
			dfs(i);
		}
	}
}

int main()
{
	unsigned short m;
	std::cin >> n >> m;
	nums.resize(n, std::vector <unsigned int> (n, 0));
	for (unsigned short i = 0; i < m; i++)
	{
		unsigned short a, b;
		unsigned int c;
		std::cin >> a >> b >> c;
		pipeline[{--a, --b}] = {i + 1, c};
		pipeline[{b, a}] = {i + 1, c};
		nums[a][b] = nums[b][a] = c;
	}
	while (bfs())
	{
		unsigned int flow = INF;
		for (unsigned short i = n - 1; i != 0; i = prev[i])
		{
			flow = std::min(flow, nums[prev[i]][i]);
		}
		for (unsigned short i = n - 1; i != 0; i = prev[i])
		{
			nums[prev[i]][i] -= flow;
			nums[i][prev[i]] += flow;
		}
	}
	came.assign(n, 0);
	dfs(0);
	unsigned int volume = 0;
	std::vector <unsigned short> volumes;
  	for (unsigned short i = 0; i < n; ++i)
	{
		for (unsigned short j = 0; j < n; ++j)
		{
			std::pair <unsigned short, unsigned int> cur = pipeline[{i, j}];
			if (came[i] && !came[j] && cur.second != 0)
			{
				volume += cur.second;
				volumes.push_back(cur.first);
			}
		}
	}
	std::cout << volumes.size() << ' ' << volume << '\n';
	for (unsigned short i : volumes) std::cout << i << ' ';
}

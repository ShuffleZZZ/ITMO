#include <iostream>
#include <vector>
#include <queue>

class Pipe
{
	public:
		int volume = 0;
		int capacity, inTo, outOf;
		Pipe(int capacity, int inTo, int outOf) 
		: capacity(capacity), inTo(inTo), outOf(outOf) {}
};

std::vector <int> prev;
std::vector <std::vector <int>> nums;
std::vector <Pipe> pipeline;
std::vector <int> route[2];
int n, s, t, flow = 0;

bool bfs()
{
	std::vector <bool> came(n, 0);
	prev.assign(n, -1);
	std::queue <int> q;
	q.push(s);
	came[s] = 1;
	while(!q.empty())
	{
		for(int i : nums[q.front()])
		{
			int gap = pipeline[i].capacity - pipeline[i].volume;
			int pipe = pipeline[i].outOf;
			if (!came[pipe] && gap > 0)
			{
				q.push(pipe);
				came[pipe] = 1;
				prev[pipe] = i;
			}
		}
		q.pop();
	}
	return came[t];
}

bool dfs(int v)
{
	route[flow].push_back(v + 1);
	if (v == t)
	{
		return 1;
	}
    for(int i : nums[v])
	{
		if (pipeline[i].volume > 0)
		{
			dfs(pipeline[i].outOf);
			--pipeline[i].volume;
			return 1;
		}
	}
	return 0;
}

int main()
{
	int m;
	std::cin >> n >> m >> s >> t;
	nums.resize(n); --s; --t;
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		pipeline.push_back(Pipe(1, --a, --b));
		pipeline.push_back(Pipe(0, b, a));
		nums[a].push_back(2 * i);
		nums[b].push_back(2 * i + 1);	
	}
	while (flow != 2 && bfs())
	{
		bool flag = 0;
		for (int v = t; v != s; v = pipeline[prev[v]].inTo)
		{
			flag = prev[v] & 1;
			++pipeline[prev[v]].volume;
			--pipeline[prev[v] ^ 1].volume;
		}
		if (flag)
		{
			--flow;
		} else {
			++flow;
		}
	}
	flow = 0;
	while (flow != 2 && dfs(s)) ++flow;
	if (flow >= 2)
	{
		std::cout << "YES" << '\n';
		for(int j : route[0])
		{
			std::cout << j << ' ';
		}
		std::cout << '\n';
		for(int j : route[1])
		{
			std::cout << j << ' ';
		}
		std::cout << '\n';
	} else {
		std::cout << "NO" << '\n';
	}
}

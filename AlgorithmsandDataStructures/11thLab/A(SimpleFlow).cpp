#include <iostream>
#include <vector>
#include <queue>

const unsigned int INF = 1e6;

class Pipe
{
	public:
		int volume = 0;
		unsigned int capacity;
		unsigned short inTo, outOf;
		Pipe(unsigned int capacity, unsigned short inTo, unsigned short outOf)
		: capacity(capacity), inTo(inTo), outOf(outOf) {}
};

std::vector <int> prevv;
std::vector <std::vector <unsigned int>> nums;
std::vector<Pipe> pipeline;
unsigned short n;

unsigned int bfs()
{
	std::vector <bool> used(n, 0);
	prevv.assign(n, -1);
	std::queue<unsigned short> q;
	q.push(0);
	used[0] = 1;
	unsigned int flow = INF;
	while (!q.empty())
	{
		for (unsigned int i : nums[q.front()])
		{
			int gap = pipeline[i].capacity - pipeline[i].volume;
			unsigned short pipe = pipeline[i].outOf;
			if (!used[pipe] && gap > 0)
			{
				if (gap < flow)
				{
					flow = gap;
				}
				q.push(pipe);
				used[pipe] = 1;
				prevv[pipe] = i;
			}
		}
		q.pop();
	}
	return used[n - 1] ? flow : 0;
}

int dfs(unsigned short v, int flow)
{
	if (v == n - 1)
	{
		return flow;
	}
	for (unsigned int j : nums[v])
	{
		if (pipeline[j].volume > 0)
		{
			int volume = dfs(pipeline[j].outOf, std::min(flow, pipeline[j].volume));
			pipeline[j].volume -= volume;
			return volume;
		}
	}
	return 0;
}

int main()
{
	unsigned int m;
	std::cin >> n >> m;
	nums.resize(n);
	for (unsigned int i = 0; i < m; ++i)
	{
		unsigned short a, b;
		unsigned int c;
		std::cin >> a >> b >> c;
		pipeline.push_back(Pipe(c, --a, --b));
		pipeline.push_back(Pipe(c, b, a));
		nums[a].push_back(2 * i);
		nums[b].push_back(2 * i + 1);
	}
	unsigned int volume = bfs();
	while (volume)
	{
		for (unsigned short v = n - 1; v != 0; v = pipeline[prevv[v]].inTo)
		{
			pipeline[prevv[v]].volume += volume;
			pipeline[prevv[v] ^ 1].volume -= volume;
		}
		volume = bfs();
	}
	std::vector <int> volumes;
	for (unsigned int i = 0; i < 2 * m; i += 2)
	{
		volumes.push_back(pipeline[i].volume);
	}
	volume = 0;
	int tmp = dfs(0, INF);
	while (tmp)
	{
		volume += tmp;
		tmp = dfs(0, INF);
	}
	std::cout << volume << '\n';
	for (int i : volumes) std::cout << i << '\n';
}

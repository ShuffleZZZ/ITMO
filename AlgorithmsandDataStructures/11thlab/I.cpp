#include <iostream>
#include <vector>
#include <queue>

const int INF = 1e9 + 1;

class Pipe
{
	public:
		unsigned int outOf;
		int capacity, volume = 0;
		Pipe(unsigned int outOf, int capacity) 
		: outOf(outOf), capacity(capacity) {}
};

std::vector <std::vector <unsigned int>> table, nums;
std::vector <unsigned int> came, dist;
std::vector <Pipe> pipeline;
int shift;

bool bfs()
{
	dist.assign(shift + 1, INF);
    came.assign(shift + 1, 0);
    std::queue <unsigned int> q;
    q.push(0);
    dist[0] = 0;
    while (!q.empty())
	{
        for (unsigned int i : nums[q.front()])
		{
            int gap = pipeline[i].capacity - pipeline[i].volume;
            unsigned int pipe = pipeline[i].outOf;
            if (dist[pipe] == INF && gap > 0)
			{
                q.push(pipe);
                dist[pipe] = dist[q.front()] + 1;
            }
        }
        q.pop();
    }
    return dist[shift] != INF;
}

int dfs(unsigned int v, int flow)
{
    if (v == shift)
    {
        return flow;
    }
    if (flow)
    {
	    while (came[v] < nums[v].size())
	    {
	        int j = nums[v][came[v]];
	        if (dist[pipeline[j].outOf] == dist[v] + 1)
			{
	            int volume = dfs(pipeline[j].outOf, std::min(flow, pipeline[j].capacity - pipeline[j].volume));
				pipeline[j].volume += volume;
	            pipeline[j ^ 1].volume -= volume;
	            if (volume) return volume;
	        }
	        ++came[v];
	    }
	}
    return 0;
}

void add(unsigned int inTo, unsigned int outOf, int capacity)
{
    nums[inTo].push_back(pipeline.size());
    nums[outOf].push_back(pipeline.size() + 1);
    pipeline.push_back(Pipe(outOf, capacity));
    pipeline.push_back(Pipe(inTo, 0));
}

int main()
{
	unsigned short n;
   	std::cin >> n;
   	table.resize(n, std::vector <unsigned int> (n));
   	nums.resize(n * n + n);
   	int p[n] = {};
   	shift = n + 1;
    for (unsigned short i = 0; i < n; ++i)
	{
        for (unsigned short j = 0; j < n; ++j)
		{
			char c;
			std::cin >> c;
			if (c == 'L')
			{
				table[i][j] = 0;
			} else if (c == 'l') {
				table[i][j] = 1;
				p[i] -= table[i][j];
			} else if (c == 'w') {
				table[i][j] = 2;
				p[i] -= table[i][j];
			} else if (c == 'W') {
				table[i][j] = 3;
				p[i] -= table[i][j];
			} else if (c == '.') {
				table[i][j] = 4;
				if (i < j)
				{
					add(0, shift, 3);
                	add(shift, i + 1, INF);
                	add(shift++, j + 1, INF);
                }
			} else if (c == '#') {
				table[i][j] = 5;
			}
        }
    }
    for (unsigned short i = 0; i < n; ++i)
	{
		unsigned short c;
        std::cin >> c;
        p[i] += c;
        add(i + 1, shift, p[i] > 0 ? p[i] : 0);
    }
    while (bfs()) dfs(0, INF);
    for (unsigned short i = n + 1; i < shift; ++i)
	{
        std::vector <unsigned int> pipes;
        for (int j : nums[i])
		{
            if (pipeline[j].outOf)
			{
                pipes.push_back(j);
            }
        }
        while (pipeline[pipes[0]].volume + pipeline[pipes[1]].volume < 3) ++pipeline[pipes[0]].volume;
        table[--pipeline[pipes[0]].outOf][--pipeline[pipes[1]].outOf] = pipeline[pipes[0]].volume;
        table[pipeline[pipes[1]].outOf][pipeline[pipes[0]].outOf] = pipeline[pipes[1]].volume;
    }
    for (unsigned short i = 0; i < n; ++i)
	{
        for (unsigned short j = 0; j < n; ++j)
		{
			if (table[i][j] == 0)
			{
				std::cout << 'L';
			} else if (table[i][j] == 1) {
				std::cout << 'l';
			} else if (table[i][j] == 2) {
				std::cout << 'w';
			} else if (table[i][j] == 3) {
				std::cout << 'W';
			} else {
				std::cout << '#';
			}
        }
        std::cout << '\n';
    }
}

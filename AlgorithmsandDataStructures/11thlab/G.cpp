#include <iostream>
#include <vector>
#include <queue>

const int INF = 1e9 + 1;

class Pipe
{
	public:
		int outOf;
		int capacity;
		int volume = 0;
		Pipe(int outOf, int capacity) 
		: outOf(outOf), capacity(capacity) {}
};

std::vector <std::vector <int>> table, nums;
std::vector <int> came;
std::vector <int> dist;
std::vector <Pipe> pipeline;
int shift;

bool bfs()
{
	dist.assign(shift + 1, INF);
	came.assign(shift + 1, 0);
    std::queue <int> q;
    q.push(0);
    dist[0] = 0;
    while (!q.empty())
	{
        for (int i : nums[q.front()])
		{
			int gap = pipeline[i].capacity - pipeline[i].volume;
            int pipe = pipeline[i].outOf;
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

int dfs(int v, int flow)
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

void add(int inTo, int outOf, int capacity)
{
    nums[inTo].push_back(pipeline.size());
    nums[outOf].push_back(pipeline.size() + 1);
    pipeline.push_back(Pipe(outOf, capacity));
    pipeline.push_back(Pipe(inTo, 0));
}

int main()
{
	int n, m;
    std::cin >> n >> m;
    table.resize(n, std::vector <int> (m));
    shift = n * m << 1 + 1;
    nums.resize(shift + 1);
    for (int i = 0; i < n; ++i)
	{
        for (int j = 0; j < m; ++j)
		{
			char c;
			std::cin >> c;
			if (c == '#')
			{
				table[i][j] = 4;
			} else if (c == '.') {
				table[i][j] = 3;
			} else if (c == 'A') {
				table[i][j] = 0;
			} else if (c == 'B') {
	            table[i][j] = 1;
	        } else if (c == '-') {
	        	table[i][j] = 2;
	        }
        }
    }
    for (int i = 0; i < n; ++i)
	{
        for (int j = 0; j < m; ++j)
		{
			if (table[i][j] != 4)
			{
				int pos = (i * m + j + 1) << 1;
				if (table[i][j] == 3)
				{
					add(pos - 1, pos, 1);
				} else {
					if (table[i][j] == 0)
					{
	                	add(0, pos - 1, INF);
	            	} else if (table[i][j] == 1) {
	                	add(pos, shift, INF);
	            	}
	            	add(pos - 1, pos, INF);
	            }
	            if (i > 0 && table[i - 1][j] != 4)
	            {
	            	add(pos, pos - 2 * m - 1, INF);
	            }
	            if (j > 0 && table[i][j - 1] != 4)
	            {
	            	add(pos, pos - 3, INF);
	            }
	            if (i < n - 1 && table[i + 1][j] != 4)
	            {
	            	add(pos, pos + 2 * m - 1, INF);
	            }
	            if (j < m - 1 && table[i][j + 1] != 4)
	            {
	            	add(pos, pos + 1, INF);
	            }
	        }
        }
    }
    int maxFlow = 0;
    while (bfs())
	{
		int input = dfs(0, INF);
        while (input)
		{
            maxFlow += input;
            input = dfs(0, INF);
        }
    }
    if (maxFlow > n)
	{
        std::cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < nums.size(); ++i)
	{
        if (dist[i] != INF)
		{
            bool build = 0;
            for (int j : nums[i])
			{
				int gap = pipeline[j].capacity - pipeline[j].volume;
                int pipe = pipeline[j].outOf;
                if (dist[pipe] == INF && !gap)
                {
                    build = pipeline[j].capacity;
                }
                if (build)
                {
                	break;
                }
            }
            shift = (i - 1) / 2;
            int x = shift / m, y = shift % m;
            if (build && table[x][y] == 3)
			{
                table[x][y] = 5;
            }
        }
    }
	std::cout << maxFlow << '\n';
	for (int i = 0; i < n; ++i)
	{
	    for (int j = 0; j < m; ++j)
		{
			if (table[i][j] == 0)
			{
				std::cout << 'A';
			} else if (table[i][j] == 1) {
				std::cout << 'B';
			} else if (table[i][j] == 2) {
				std::cout << '-';
			} else if (table[i][j] == 3) {
				std::cout << '.';
			} else if (table[i][j] == 4) {
				std::cout << '#';
			} else if (table[i][j] == 5) {
				std::cout << '+';
			}
	    }
	    std::cout << '\n';
	}
}

#include <iostream>
#include <vector>
#include <queue>

const unsigned long long INF = static_cast <unsigned long long>(1e18);

class Pipe
{
	public:
		long long ind, backPipes;
		long long capacity;
        long long cost, flow = 0;
		Pipe(long long ind, long long capacity, long long cost,
			 long long backPipes) : ind(ind), capacity(capacity),
			 cost(cost), backPipes(backPipes) {}
		Pipe() {}
};

std::vector <std::vector <Pipe>> pipeline;

void add(long long inTo, long long outOf, long long capacity, long long cost)
{
	pipeline[inTo].push_back(Pipe(outOf, capacity, cost, pipeline[outOf].size()));
	pipeline[outOf].push_back(Pipe(inTo, 0, -cost, pipeline[inTo].size() - 1));
}

int main()
{
    long long n, m;
    std::cin >> n >> m;
    pipeline.resize(2 * n + 2, std::vector <Pipe>());
    for (long long i = 0; i < n; ++i)
    {
        long long a;
        std::cin >> a;
        add(n + i + 1, i + 1, INF, a);
        add(0, n + i + 1, 1, 0);
        add(i + 1, 2 * n + 1, 1, 0);
        add(i + 1, n + i + 1, INF, 0);
    }
    for (long long i = 0; i < m; ++i)
    {
        long long u, v;
        long long c;
        std::cin >> u >> v >> c;
        add(n + u, v, INF, c);
    }
    n = 2 * n + 2;
    long long flow = 0, cost = 0;
	while (flow < INF)
	{
		std::vector <long long> d(n + 1, INF), came(n + 1), prev(n + 1), prevPipe(n + 1);
		std::queue <long long> q;
		q.push(0);
		d[0] = 0;
		while (!q.empty())
		{
			came[q.front()] = 0;
			for (long long i = 0; i < pipeline[q.front()].size(); ++i)
			{
				Pipe& pipe = pipeline[q.front()][i];
				long long expected = d[q.front()] + pipe.cost;
				if (pipe.flow < pipe.capacity && expected < d[pipe.ind])
				{
					d[pipe.ind] = expected;
					if (!came[pipe.ind])
					{
						q.push(pipe.ind);
					}
					came[pipe.ind] = 1;
					prev[pipe.ind] = q.front();
					prevPipe[pipe.ind] = i;
				}
			}
			q.pop();
		}
		if (d[n - 1] == INF)
		{
			std::cout << cost << '\n';
			break;
		}
		long long addFlow = INF;
		for (long long i = n - 1; i != 0; i = prev[i])
		{
			long long gap = pipeline[prev[i]][prevPipe[i]].capacity - pipeline[prev[i]][prevPipe[i]].flow;
			if (gap < addFlow)
			{
				addFlow = gap;
			}
		}
		for (long long i = n - 1; i != 0; i = prev[i])
		{
			pipeline[prev[i]][prevPipe[i]].flow += addFlow;
			pipeline[i][pipeline[prev[i]][prevPipe[i]].backPipes].flow -= addFlow;
			cost += addFlow * pipeline[prev[i]][prevPipe[i]].cost;
		}
		flow += addFlow;
	}
}
close

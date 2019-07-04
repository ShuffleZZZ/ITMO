#include <fstream>
#include <vector>
#include <queue>

const unsigned long long INF = static_cast <unsigned long long>(1e18);

class Pipe
{
	public:
		unsigned short ind, backPipes;
		int capacity, cost, flow = 0;
		Pipe(unsigned short ind, int capacity, int cost, 
			 unsigned short backPipes) : ind(ind), capacity(capacity), 
			 cost(cost), backPipes(backPipes) {}
		Pipe() {}
};

std::vector <std::vector <Pipe>> pipeline;

void add(unsigned short inTo, unsigned short outOf, int capacity, int cost)
{
	pipeline[inTo].push_back(Pipe(outOf, capacity, cost, pipeline[outOf].size()));
	pipeline[outOf].push_back(Pipe(inTo, 0, -cost, pipeline[inTo].size() - 1));
}

int main()
{
	std::ifstream in;
	in.open("mincost.in");
	std::ofstream out;
	out.open("mincost.out");
	unsigned short n, m;
	in >> n >> m;
	pipeline.resize(n, std::vector <Pipe>());
	for (unsigned short i = 0; i < m; ++i)
	{
		unsigned short a, b;
		int capacity, cost;
		in >> a >> b >> capacity >> cost;
		add(a - 1, b - 1, capacity, cost);
	}
	long long flow = 0, cost = 0;
	while (flow < INF)
	{
		std::vector <long long> d(n, INF), came(n), prev(n), prevPipe(n);
		std::queue <unsigned short> q;
		q.push(0);
		d[0] = 0;
		while (!q.empty())
		{
			came[q.front()] = 0;
			for (unsigned short i = 0; i < pipeline[q.front()].size(); ++i)
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
			out << cost << '\n';
			break;
		}
		long long addFlow = INF;
		for (unsigned short i = n - 1; i != 0; i = prev[i])
		{
			long long gap = pipeline[prev[i]][prevPipe[i]].capacity - pipeline[prev[i]][prevPipe[i]].flow;
			if (gap < addFlow)
			{
				addFlow = gap;
			}
		}
		for (unsigned short i = n - 1; i != 0; i = prev[i])
		{
			pipeline[prev[i]][prevPipe[i]].flow += addFlow;
			pipeline[i][pipeline[prev[i]][prevPipe[i]].backPipes].flow -= addFlow;
			cost += addFlow * pipeline[prev[i]][prevPipe[i]].cost;
		}
		flow += addFlow;
	}
	in.close();
	out.close();
}
	

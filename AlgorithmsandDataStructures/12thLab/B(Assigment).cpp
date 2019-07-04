#include <iostream>
#include <fstream>
#include <vector>

const unsigned int INF = 1e9;

int main()
{
	std::ifstream in;
	in.open("assignment.in");
	std::ofstream out;
	out.open("assignment.out");
	unsigned short n;
	in >> n;
	unsigned int c[n + 1][n + 1] = {};
	for (unsigned short i = 1; i <= n; ++i)
	{
		for (unsigned short j = 1; j <= n; ++j)
		{
			in >> c[i][j];
		}
	}
	int p1[n + 1] = {}, p2[n + 1] = {};
	unsigned short ind[n + 1] = {}, route[n + 1] = {};
	for (unsigned short i = 0; i < n; ++i)
	{
		ind[0] = i + 1;
		unsigned short curJ = 0;
		int best[n + 1];
		std::fill(best, best + n + 1, INF);
		bool came[n + 1] = {}, isPos = 1;
		while(isPos)
		{
			came[curJ] = 1;
			int gap = INF;
			unsigned short newJ;
			for (unsigned short j = 1; j <= n; ++j)
			{
				if (!came[j])
				{
					int cur = 1 * c[ind[curJ]][j] - p1[ind[curJ]] - p2[j];
					if (cur < best[j])
					{
						best[j] = cur;
						route[j] = curJ;
					}
					if (best[j] < gap)
					{
						gap = best[j];
						newJ = j;
					}
				}
			}
			for (unsigned short j = 0; j <= n; ++j)
			{
				if (came[j])
				{
					p1[ind[j]] += gap;
					p2[j] -= gap;
				} else {
					best[j] -= gap;
				}
			}
			curJ = newJ;
			isPos = ind[curJ];
		}
		isPos = 1;
		while (isPos)
		{
			unsigned short lastJ = route[curJ];
			ind[curJ] = ind[lastJ];
			isPos = curJ = lastJ;
		}
	}
	unsigned long long sum = 0;
	for (unsigned short i = 1; i <= n; ++i)
	{
		sum += c[ind[i]][i];
	}
	out << sum << '\n';
	for (unsigned short i = 1; i <= n; ++i)
	{
		out << ind[i] << ' ' << i << '\n';
	}
	//in.close();
	//out.close();
}

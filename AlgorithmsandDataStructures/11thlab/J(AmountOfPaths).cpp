#include <iostream>
#include <vector>

const long long INF = 1e9 + 1;

class Ikea
{
	public:
		long long x1, x2, y1, y2;
		explicit Ikea(long long x1, long long x2, long long y1, long long y2)
		 : x1(x1), y1(y1), x2(x2), y2(y2) {}
		explicit Ikea() {}
};

long long dist(Ikea fi, Ikea se)
{
	return std::max(
			std::max(fi.x1 <= se.x1 ? se.x1 - fi.x2 : fi.x1 - se.x2,
					 fi.y1 <= se.y1 ? se.y1 - fi.y2 : fi.y1 - se.y2), static_cast <long long>(0));
}

int main()
{
	unsigned short n;
	long long w;
	std::cin >> n >> w;
	Ikea stats[n];
	for (unsigned short i = 0; i < n; ++i)
	{
		long long x1, x2, y1, y2;
		std::cin >> x1 >> y1 >> x2 >> y2;
		stats[i] = Ikea(x1, x2, y1, y2);
	}
	long long place[n + 2][n + 2] = {};
	place[0][n + 1] = place[n + 1][0] = w;
	for (unsigned short i = 0; i < n; ++i)
	{
		place[0][i + 1] = 
		place[i + 1][0] = std::min(stats[i].y1, stats[i].y2);
		place[n + 1][i + 1] = 
		place[i + 1][n + 1] = w - std::max(stats[i].y1, stats[i].y2);
		for (unsigned short j = 0; j < n; ++j)
		{
			if (i != j)
			{
				place[i + 1][j + 1] = 
				place[j + 1][i + 1] = dist(stats[i], stats[j]);
			}
		}	
	}
	std::vector <long long> d(n + 2, INF);
	std::vector <bool> came(n + 2, 0);
	d[0] = 0;
	for (unsigned short i = 0; i < n + 2; ++i)
	{
		long long cur = -1;
		for (unsigned short j = 0; j < n + 2; ++j)
		{
			if (!came[j] && (cur == -1 || d[j] < d[cur]))
			{
				cur = j;
			}
		}
		came[cur] = 1;
		for (unsigned short k = 0; k < n + 2; ++k)
		{
			d[k] = std::min(d[cur] + place[cur][k], d[k]);
		}
	}
	if (d[n + 1] == INF) 
	{
		std::cout << 0 << '\n';
	} else {
		std::cout << d[n + 1] << '\n';
	}	
}

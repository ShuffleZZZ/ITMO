#include <iostream>
#include <vector>
#include <cmath>

const double PRECISION = 0.00001;
const double IKEA_SQUARE = 100000.0;

class Ikea
{
	public:
		double x, y, kmh;
		explicit Ikea(double x, double y, double kmh)
		 : x(x), y(y), kmh(kmh) {}
		explicit Ikea() {}
};

std::vector <Ikea> stats;
std::vector <std::pair <unsigned short, unsigned short>> place;
std::vector <std::vector <unsigned short>> movable;
std::vector <short> matching;
std::vector <bool> came;
unsigned short n;

bool dfs(unsigned short i)
{
	if (!came[i])
	{
		came[i] = 1;
		for (auto j : movable[i])
		{
			if (matching[j] == -1 || dfs(matching[j]))
			{
				matching[j] = i;
				return 1;
			}
		}
	}
	return 0;
}

bool enough(unsigned short i, unsigned short j, double time)
{
	return sqrt((stats[i].x - place[j].first) * (stats[i].x - place[j].first) + 
			 (stats[i].y - place[j].second) * (stats[i].y - place[j].second)) / 
			  stats[i].kmh <= time;
}

bool reshuffle(double rand)
{
	movable.assign(n, std::vector <unsigned short> ());
	for (unsigned short i = 0; i < n; ++i)
	{
		for (unsigned short j = 0; j < n; ++j)
		{
			if (enough(i, j, rand))
			{
				movable[i].push_back(j);
			}
		}
	}
	unsigned short ans = 0;
	matching.assign(n, -1);
	for (unsigned short i = 0; i < n; ++i)
	{
		came.assign(n, 0);
		if (dfs(i)) 
		{
			++ans;
		}
	}
	return (ans == n);
}

int main()
{
	std::cout.precision(8);
	//std::cout.setf(std::ios::fixed);
	//std::cout.setf(std::ios::showpoint);
	std::cin >> n;
	stats.resize(n);
	place.resize(n);
	for (unsigned short i = 0; i < n; ++i)
	{
		double x, y, kmh;
		std::cin >> x >> y >> kmh;
		stats[i] = Ikea(x, y, kmh);
	}
	for (unsigned short i = 0; i < n; ++i)
	{
		unsigned short a, b;
		std::cin >> a >> b;
		place[i] = {a, b};
	}
	double l = 0;
	double r = IKEA_SQUARE;
	while (r - l > PRECISION)
	{
		double m = (l + r) / 2;
		if (reshuffle(m))
		{
			r = m;
		} else {
			l = m;
		}
	}
	std::cout << l << '\n';
}

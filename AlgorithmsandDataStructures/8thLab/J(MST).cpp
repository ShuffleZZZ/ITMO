#include <iostream>
#include <vector>
#include <algorithm>

struct g
{
	unsigned int b, e, w;
};

bool sortx(g c, g d)
{
	return c.w < d.w;
}

std::vector <g> a;
std::vector <unsigned int> ufd;

unsigned int get(unsigned int i)
{
	if (ufd[i] == i)
	{
		return i;
	} else
	{
		return ufd[i] = get(ufd[i]);
	}
}

void uni(unsigned int c, unsigned int d)
{
	ufd[get(c)] = get(d);
}

int main()
{
	unsigned int n, m;
	std::cin >> n >> m;
	a.resize(m);
	long long ans = 0;
	for (unsigned int i = 0; i < n; ++i)
	{
		ufd.push_back(i);
	}
	for (unsigned int i = 0; i < m; ++i)
	{
		unsigned int b, e, w;
		std::cin >> b >> e >> w;
		a[i].b = b - 1;
		a[i].e = e - 1;
		a[i].w = w;
	}
	sort(a.begin(), a.end(), sortx);
	for (unsigned int i = 0; i < m; ++i)
	{
		if (get(a[i].b) != get(a[i].e))
		{
			uni(a[i].b, a[i].e);
			ans += a[i].w;
		}
	}
	std::cout << ans << '\n';
}
	
	
	

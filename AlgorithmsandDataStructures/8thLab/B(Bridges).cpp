#include <iostream>
#include <vector>
#include <algorithm>

unsigned int n, m, time;
std::vector <std::vector <std::pair <unsigned int, unsigned int>>> a;
std::vector <bool> came;
std::vector <unsigned int> ans, tin, bedge;

void dfs(unsigned int i, int pr = -1)
{
	came[i] = 1;
	tin[i] = bedge[i] = time++;
	for (auto j : a[i])
	{
		if (j.first != pr)
		{
			if (came[j.first])
			{
				bedge[i] = std::min(bedge[i], tin[j.first]);
			} else
			{
				dfs(j.first, i);
				bedge[i] = std::min(bedge[i], bedge[j.first]);
				if (tin[i] < bedge[j.first])
				{
					ans.push_back(j.second);
				}
			}
		}
	}
}
		

int main()
{
	std::cin >> n >> m;
	a.resize(n);
	came.resize(n, 0);
	time = 0;
	tin.resize(n, 0);
	bedge = tin;
	for (unsigned int i = 1; i <= m; ++i)
	{
		unsigned int b, c;
		std::cin >> b >> c;
		a[b - 1].push_back({c - 1, i});
		a[c - 1].push_back({b - 1, i});
	}
	for (unsigned int i = 0; i < n; ++i)
	{
		if(!came[i])
		{
			dfs(i);
		}
	}
	sort(ans.begin(), ans.end());
	std::cout << ans.size() << '\n';
	for (auto i : ans)
	{
		std::cout << i << ' ';
	}
}

#include <iostream>
#include <vector>
#include <algorithm>

int n, m, time, c;
std::vector <std::vector <std::pair <int, int>>> a;
std::vector <bool> came;
std::vector <int> ans, tin, bedge;
 
void dfs(int i, int pr = -1)
{
	came[i] = 1;
	int kids = 0;
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
			}
		}
	}
}

void dfs2(int i, int cnt, short p)
{
	came[i] = 1;
	for (auto j : a[i])
	{
		if (j.first != p)
		{
			if (!came[j.first])
			{
				if (bedge[j.first] >= tin[i])
				{
					++c;
					for (auto k : a[i])
					{
						if (k.first == j.first)
						{
							ans[k.second] = c;
						}
					}
					dfs2(j.first, c, i);
				} else
				{
					for (auto k : a[i])
					{
						if (k.first == j.first)
						{
							ans[k.second] = cnt;
						}
					}
					dfs2(j.first, cnt, i);
				}
			} else if (tin[j.first] < tin[i])
			{
				for (auto k : a[i])
					{
						if (k.first == j.first)
						{
							ans[k.second] = cnt;
						}
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
	ans.resize(m, 0);
	time = 0;
	c = 0;
	tin.resize(n, 0);
	bedge = tin;
	for (int i = 0; i < m; ++i)
	{
		int b, c;
		std::cin >> b >> c;
		a[b - 1].push_back({c - 1, i});
		a[c - 1].push_back({b - 1, i});
	}
	for (int i = 0; i < n; ++i)
	{
		if (!came[i])
		{
			dfs(i);
		}
	}
	came.assign(n, 0);
	for (int i = 0; i < n; ++i)
	{
		if (!came[i])
		{
			dfs2(i, c, -1);
		}
	}
	std::cout << c << '\n';
	for (auto i : ans)
	{
		std::cout << i << ' ';
	}
}

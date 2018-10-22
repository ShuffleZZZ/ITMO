#include <iostream>
#include <vector>
#include <algorithm>

unsigned int n, m, time, c;
std::vector <std::vector <unsigned int>> a;
std::vector <bool> came;
std::vector <unsigned int> ans, tin, bedge;

void dfs(unsigned int i, int pr = -1)
{
	came[i] = 1;
	tin[i] = bedge[i] = time++;
	for (auto j : a[i])
	{
		if (j != pr)
		{
			if (came[j])
			{
				bedge[i] = std::min(bedge[i], tin[j]);
			} else
			{
				dfs(j, i);
				bedge[i] = std::min(bedge[i], bedge[j]);
			}
		}
	}
}

void dfs2(unsigned int i, unsigned int cnt)
{
	ans[i] = cnt;
	for (auto j : a[i])
	{
		if (!ans[j])
		{
			if (bedge[j] > tin[i])
			{
				unsigned int e = 0;
				for (auto k : a[i])
				{
					if (k == j)
					{
						++e;
					}
					if (e > 1)
					{
						break;
					}
				}
				if (e > 1)
				{
					dfs2(j, cnt);
				} else
				{
					++c;
					dfs2(j, c);
				}
			} else
			{
				dfs2(j, cnt);
			}
		}
	}
}
		

int main()
{
	std::cin >> n >> m;
	a.resize(n);
	came.resize(n, 0);
	ans.resize(n, 0);
	time = 0;
	c = 0;
	tin.resize(n, 0);
	bedge = tin;
	for (unsigned int i = 0; i < m; ++i)
	{
		unsigned int b, c;
		std::cin >> b >> c;
		if (b != c)
		{
			a[b - 1].push_back(c - 1);
			a[c - 1].push_back(b - 1);
		}
	}
	for (unsigned int i = 0; i < n; ++i)
	{
		if(!came[i])
		{
			dfs(i);
		}
	}
	for (unsigned int i = 0; i < n; ++i)
	{
		if(!ans[i])
		{
			++c;
			dfs2(i, c);
		}
	}
	std::cout << c << '\n';
	for (auto i : ans)
	{
		std::cout << i << ' ';
	}
}

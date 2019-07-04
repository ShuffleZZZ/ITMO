#include <iostream>
#include <vector>
#include <algorithm>

unsigned int n, m, time;
std::vector <std::vector <unsigned int>> a;
std::vector <bool> came, in;
std::vector <unsigned int> ans, tin, bedge;
 
void dfs(int i, int pr = -1)
{
	came[i] = 1;
	int kids = 0;
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
				if (tin[i] <= bedge[j] && !in[i] && pr != -1)
				{
					in[i] = 1;
					ans.push_back(i + 1);
				}
				++kids;
			}
		}
	}
	if (kids >= 2 && !in[i] && pr == -1)
	{
		in[i] = 1;
		ans.push_back(i + 1);
	}
}
 
int main()
{
	std::cin >> n >> m;
	a.resize(n);
	came.resize(n, 0);
	in = came;
	time = 0;
	tin.resize(n, 0);
	bedge = tin;
	for (unsigned int i = 0; i < m; ++i)
	{
		unsigned int b, c;
		std::cin >> b >> c;
		a[b - 1].push_back(c - 1);
		a[c - 1].push_back(b - 1);
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

#include <iostream>
#include <vector>
#include <map>

int n, m, amount;
std::vector <std::vector <int>> a;
std::vector <std::vector <int>> c;
std::vector <int> ans, came;
std::vector <std::string> revb;
std::map <std::string, int> b;

void dfs(int i)
{
	came[i] = 1;
	for (auto j : a[i])
	{
		if (!came[j])
		{
			dfs(j);
		}
	}
	ans.push_back(i);
}

void dfs2(int i)
{
	came[i] = amount;
	for (auto j : c[i])
	{
		if (came[j] == 0)
		{
			dfs2(j);
		}
	}
}

int main()
{
	std::cin >> n >> m;
	a.resize(2 * n);
	revb.resize(n);
	c.resize(2 * n);
	came.resize(2 * n, 0);
	for (int i = 0; i < n; ++i)
	{
		std::string name;
		std::cin >> name;
		b[name] = i;
		revb[i] = name;
	}
	for (int i = 0; i < m; ++i)
	{
		std::string first, temp, second;
		std::cin >> first >> temp >> second;
		bool sign1 = 1, sign2 = 1;
		if (first[0] == '-')
		{
			sign1 = 0;
		}
		first.erase(first.begin());
		if (second[0] == '-')
		{
			sign2 = 0;
		}
		second.erase(second.begin());
		if (sign1)
		{
			if (sign2)
			{
				a[b[first]].push_back(b[second]);
				a[b[second] + n].push_back(b[first] + n);
				c[b[second]].push_back(b[first]);
				c[b[first] + n].push_back(b[second] + n);
			} else
			{
				a[b[first]].push_back(b[second] + n);
				a[b[second]].push_back(b[first] + n);
				c[b[second] + n].push_back(b[first]);
				c[b[first] + n].push_back(b[second]);
			}
		} else if (sign2)
		{
			a[b[first] + n].push_back(b[second]);
			a[b[second] + n].push_back(b[first]);
			c[b[second]].push_back(b[first] + n);
			c[b[first]].push_back(b[second] + n);
		} else
		{
			a[b[first] + n].push_back(b[second] + n);
			a[b[second]].push_back(b[first]);
			c[b[first]].push_back(b[second]);
			c[b[second] + n].push_back(b[first] + n);
		}
	}
	/*for (int i = 0; i < 2 * n; ++i)
	{
		std::cout << i << ": ";
		for (auto j : a[i])
		{
			std::cout << j << ' ';
		}
		std::cout << '\n';
	}
	for (int i = 0; i < 2 * n; ++i)
	{
		std::cout << i << ": ";
		for (auto j : c[i])
		{
			std::cout << j << ' ';
		}
		std::cout << '\n';
	}*/
	for (int i = 0; i < 2 * n; ++i)
	{
		if (!came[i])
		{
			dfs(i);
		}
	}
	/*for (int i = 0; i < 2 * n; ++i)
	{
		std::cout << ans[i] << ' ';
	}
	std::cout << '\n';*/
	came.assign(2 * n, 0);
	amount = 0;
	for (int i = 2 * n - 1; i >= 0; --i)
	{
		if (came[ans[i]] == 0)
		{
			++amount;
			dfs2(ans[i]);
		}
	}
	amount = 0;
	ans.clear();
	for (int i = 0; i < n; ++i)
	{
		if (came[i] > came[i + n])
		{
			++amount;
			ans.push_back(i);
		} else if (came[i] == came[i + n])
		{
			std::cout << -1 << '\n';
			return 0;
		}
	}
	std::cout << amount << '\n';
	for (auto i : ans)
	{
		std::cout << revb[i] << '\n';
	}
}

#include <iostream>
#include <vector>
#include <set>

unsigned int n, m, amount;
std::vector <std::vector <unsigned int>> a, b;
std::vector <unsigned int> ans, came;
std::set <std::pair <unsigned short, unsigned short>> res;

void dfs(unsigned int i)
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

void dfs2(unsigned int i)
{
	came[i] = amount;
	for (auto j : b[i])
	{
		if (came[j] == 0)
		{
			dfs2(j);
		}
	}
}

int main() {
	std::cin >> n >> m;
	came.resize(n, 0);
	a.resize(n);
	b = a;
	for (unsigned int i = 0; i < m; ++i)
	{
		unsigned short c, d;
		std::cin >> c >> d;
		if (c != d)
		{
			a[c - 1].push_back(d - 1);
			b[d - 1].push_back(c - 1);
		}
	}
	for (unsigned short i = 0; i < n; ++i)
	{
		if (!came[i])
		{
			dfs(i);
		}
	}
	came.assign(n, 0);
	amount = 0;
	for (int i = n - 1; i >= 0; --i)
	{
		if (came[ans[i]] == 0)
		{
			++amount;
			dfs2(ans[i]);
		}
	}
	for (unsigned short i = 0; i < n; ++i)
	{
		for (unsigned int j = 0; j < a[i].size(); ++j)
		{
			if (came[i] != came[a[i][j]])
			{
				res.insert({came[i], came[a[i][j]]});
			}
		}
	}
	std::cout << res.size() << '\n';
}

#include <fstream>
#include <vector>

int n, l, m, r, b1, b2;
std::vector <std::vector <int>> a, b;
std::vector <int> came, came2;

void dfs(int i, int c)
{
	++b1;
	came[i] = 1;
	for (int j = 0; j < n; ++j)
	{
		if (!came[j] && a[i][j] <= c)
		{
			dfs(j, c);
		}
	}
}

void dfs2(int i, int c)
{
	++b2;
	came2[i] = 1;
	for (int j = 0; j < n; ++j)
	{
		if (!came2[j] && b[i][j] <= c)
		{
			dfs2(j, c);
		}
	}
}
 
int main()
{
	std::ifstream in;
	in.open("avia.in");
	std::ofstream out;
	out.open("avia.out");
	in >> n;
	a.resize(n, std::vector <int>(n));
	b.resize(n, std::vector <int>(n));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			in >> a[i][j];
			b[j][i] = a[i][j];
		}
	}
	l = -1;
	r = 1e9;
	while (l + 1 < r)
	{
		int m = (l + r) / 2;
		came.assign(n, 0);
		came2.assign(n, 0);
		b1 = 0;
		b2 = 0;
		dfs(0, m);
		dfs2(0, m);
		if (b1 == n && b2 == n) r = m;
		else l = m;
	}
	out << r << '\n';
}

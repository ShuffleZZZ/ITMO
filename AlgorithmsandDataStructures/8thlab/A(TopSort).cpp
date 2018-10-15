#include <iostream>
#include <vector>

unsigned int n, m;
std::vector <std::vector <unsigned int>> a;
std::vector <unsigned int> ans, came;
bool circle = 0;

void dfs(unsigned int i) {
	came[i] = 1;
	unsigned int j = 0;
	while (!circle && j < a[i].size()) {
		if (came[a[i][j]] == 0) dfs(a[i][j]);
		else if (came[a[i][j]] == 1) circle = 1;
		++j;
	}
	if (!circle) came[i] = 2;
	ans.push_back(i);
}

int main() {
	std::cin >> n >> m;
	came.resize(n, 0);
	a.resize(n, std::vector <unsigned int> ());
	for (unsigned int i = 0; i < m; ++i) {
		unsigned int b, c;
		std::cin >> b >> c;
		a[b - 1].push_back(c - 1);
	}
	unsigned int i = 0;
	while (!circle && i < n) {if (!came[i]) dfs(i); ++i;}
	if (!circle) for (int i = ans.size() - 1; i > -1; --i)
		std::cout << ans[i] + 1 << ' ';
	else std::cout << -1 << '\n';
}

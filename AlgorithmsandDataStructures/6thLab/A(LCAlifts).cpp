#include <iostream>

using namespace std;

int p[500000];
int lvl[500000];
int dp[500000][19];

int lca(int x, int y) {
	if (lvl[x] < lvl[y]) return lca(y, x);
	int dif = lvl[x] - lvl[y];
	int lift = 0;
	while (dif > 0) {
		if (dif & 1) x = dp[x][lift];
		dif >>= 1;
		++lift;
	}
	for (int i = 18; i >= 0; --i) {
		if (dp[x][i] != dp[y][i]) {
			x = dp[x][i];
			y = dp[y][i];
		}
	}
	if (x != y) return p[x];
	else return x;
}

int main() {
	int n;
	cin >> n;
	p[1] = 1;
	lvl[1] = 0;
	for (int i = 2; i <= n; ++i) {
		int x;
		cin >> x;
		p[i] = x;
		lvl[i] = lvl[x] + 1;
	}
	for (int i = 1; i <= n; i++) {
		dp[i][0] = p[i];
		for (int j = 1; j < 19; j++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		cout << lca(u, v) << '\n';
	}
}

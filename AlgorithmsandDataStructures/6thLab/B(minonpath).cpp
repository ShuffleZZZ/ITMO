#include <fstream>

using namespace std;

int p[500000];
int w[500000];
int lvl[500000];
int dp[500000][19];
int dpw[500000][19];

int minlen(int x, int y) {
	if (lvl[x] < lvl[y]) return minlen(y, x);
	int dif = lvl[x] - lvl[y];
	int lift = 0;
	int len = 2000000;
	while (dif > 0) {
		if (dif & 1) {
			len = min(len, dpw[x][lift]);
			x = dp[x][lift];
		}
		dif >>= 1;
		++lift;
	}
	for (int i = 18; i >= 0; --i)
		if (dp[x][i] != dp[y][i]) {
			len = min(len, dpw[x][i]);
			len = min(len, dpw[y][i]);
			x = dp[x][i];
			y = dp[y][i];
		}
	if (x != y) return min(len, min(dpw[x][0], dpw[y][0]));
	else return len;
}

int main() {
	ifstream in;
    in.open("minonpath.in");
    ofstream out;
    out.open("minonpath.out");
	int n;
	in >> n;
	p[1] = 1;
	lvl[1] = 0;
	w[1] = 2000000;
	for (int i = 2; i <= n; ++i) {
		int x;
		in >> x >> w[i];
		p[i] = x;
		lvl[i] = lvl[x] + 1;
	}
	for (int i = 1; i <= n; ++i) {
		dp[i][0] = p[i];
		dpw[i][0] = w[i];
		for (int j = 1; j < 19; ++j) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
			dpw[i][j] = min(dpw[i][j - 1], dpw[dp[i][j - 1]][j - 1]);
		}
	}
	int m;
	in >> m;
	for (int i = 0; i < m; ++i) {
		int u, v;
		in >> u >> v;
		out << minlen(u, v) << '\n';
	}
	in.close();
	out.close();
}

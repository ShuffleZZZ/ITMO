#include <iostream>

using namespace std;

int p[200500];
int lvl[200500];
int dp[200500][18];

int lca(int x, int y) {
    if (lvl[x] < lvl[y]) return lca(y, x);
    int dif = lvl[x] - lvl[y];
    int lift = 0;
	while (dif > 0) {
		if (dif & 1) x = dp[x][lift];
		dif >>= 1;
		++lift;
	}
    for (int i = 17; i >= 0; --i) {
        if (dp[x][i] != dp[y][i]) {
            x = dp[x][i];
            y = dp[y][i];
        }
    }
    if (x != y) return dp[x][0];
    else return x;
}

int justice(int ind) {
	if (ind == p[ind]) return ind;
	else return p[ind] = justice(p[ind]);
}

void victim(int x, int y) {
    x = justice(x);
    y = justice(y);
    if (x == y) return;
    if (lvl[x] < lvl[y]) p[y] = x;
    else p[x] = y;
}

int main() {
    int m;
    cin >> m;
   	p[0] = 0; 
    int n = 1;
    for (int i = 0; i < m; ++i) {
        char c;
        cin >> c;
        if (c == '+') {
            int v;
            cin >> v;
            dp[n][0] = v - 1;
            p[n] = n;
            lvl[n] = lvl[v - 1] + 1;
            for (int j = 1; j < 18; ++j) dp[n][j] = dp[dp[n][j - 1]][j - 1];
            ++n;
        } else if (c == '-') {
            int v;
            cin >> v;
            victim(v - 1, dp[v - 1][0]);
        } else if (c == '?') {
            int u, v;
            cin >> u >> v;
            cout << justice(lca(u - 1, v - 1)) + 1 << '\n';
        }
    }
}

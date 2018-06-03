#include <iostream>
#include <vector>

using namespace std;

vector< vector< int > > ways;
int dp[300000][19], p[300000];
int leftb[300000], rightb[300000];
long long  tr[4 * 300000];
int boarder = 0;

void update(int ind, int l, int r, int pos, long long v) {
    if (l == r) { 
		tr[ind] += v; 
		return;
	}
    if (l > r) return;
    int m = (l + r) / 2;
    if (pos <= m) update(2 * ind + 1, l, m, pos, v);
    else update(2 * ind + 2, m + 1, r, pos, v);
    tr[ind] = tr[2 * ind + 1] + tr[2 * ind + 2];
}

long long sum(int ind, int left, int right, int l, int r) {
    if ((l > right) or (r < left) or (l > r) or (left > right)) return 0;
    if ((left == l) and (right == r)) return tr[ind];
    int m = (left + right) / 2;
    return sum(2 * ind + 1, left, m, l, min(m, r)) +
    sum(2 * ind + 2, m + 1, right, max(m + 1, l), r);
}

void dfs(int ind, int prev) {
    leftb[ind] = boarder++;
    if (prev == -1) p[ind] = 0;
    else p[ind] = prev;
    for (auto tr : ways[ind]) if (tr != prev) dfs(tr, ind);
    rightb[ind] = boarder - 1;
}

bool parent(int a, int b) {
    return ((leftb[a] <= leftb[b]) and (rightb[b] <= rightb[a]));
}

int lca(int x, int y) {
    if (parent(x, y)) return x;
    for (int i = 18; i >= 0; i--)
        if (!parent(dp[x][i], y)) x = dp[x][i];
    return p[x];
}

int main() {
    int n;
    cin >> n;
    ways.resize(n + 1);
    ways[0].push_back(1);
    ways[1].push_back(0);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        ways[v].push_back(u);
        ways[u].push_back(v);
    }
    dfs(0, -1);
    for (int i = 0; i <= n; ++i)
    	if (p[i] < 0) dp[i][0] = i;
    	else dp[i][0] = p[i];
    for (int j = 1; j < 19; ++j) 
    	for (int i = 0; i <= n; ++i)
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char c;
        cin >> c;
        if (c == '+') {
            int v, u;
			long long d;
            cin >> v >> u >> d;
            update(0, 0, n + 2, leftb[v], d);
            update(0, 0, n + 2, leftb[u], d);
            update(0, 0, n + 2, leftb[lca(v, u)], -d);
            update(0, 0, n + 2, leftb[p[lca(v, u)]], -d);
        } else if (c == '?') {
            int v;
            cin >> v;
            cout << sum(0, 0, n + 2, leftb[v], rightb[v]) << '\n';
        }
    }
}

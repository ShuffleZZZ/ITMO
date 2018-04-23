#include <fstream>

using namespace std;

const int maxn = 100005;
const long long neutral = -2147483648;

struct tree {
	int l, r;
	long long v;
};

ifstream in;
ofstream out;
tree a[maxn];
long long n, m, ans[maxn];
long long rmq[17][maxn];
long long tr[4 * maxn];

template<typename A, typename B>
A max(A a, B b) {
	if (a >= b) return a;
	else return b;
}

void buildtree(int ind, int l, int r) {
	tr[ind] = neutral;
	if (l == r) {
		return;
	}
	int m = (l + r) / 2;
	buildtree(2 * ind, l, m);
	buildtree(2 * ind + 1, m + 1, r);
}

void set(int ind, int l, int r, int fl, int fr, int value) {
	if ((l == fl) and (r == fr)) {
		tr[ind] = max(tr[ind], value);
		return;
	}
	int m = (l + r) / 2;
	if (fr <= m) {
		return set(2 * ind, l, m, fl, fr, value);
	}
	if (m < fl) {
		return set(2 * ind + 1, m + 1, r, fl, fr, value);
	}
	set(2 * ind, l, m, fl, m, value);
	set(2 * ind + 1, m + 1, r, m + 1, fr, value);
}

void get(int ind, int l, int r, int fn, long long &res) {
	res = max(res, tr[ind]);
	if (l == r) {
		return;
	}
	int m = (l + r) / 2;
	if (fn <= m) {
		get(2 * ind, l, m, fn, res);
	} else {
		get(2 * ind + 1, m + 1, r, fn, res);
	}
}

long long childs(int l, int r) {
	int i = 31 - __builtin_clz(r - l + 1);
	return min(rmq[i][l], rmq[i][r - (1 << i) + 1]);
}

int main() {
	in.open("rmq.in");
	out.open("rmq.out");
	in >> n >> m;
	for(int i = 0; i < m; ++i) {
		in >> a[i].l >> a[i].r >> a[i].v;
	}
	buildtree(1, 1, n);
	for(int i = 0; i < m; ++i) {
		set(1, 1, n, a[i].l, a[i].r, a[i].v);
	}
	for(int i = 0; i < n; ++i) {
		ans[i + 1] = neutral;
		get(1, 1, n, i + 1, ans[i + 1]);
	}
	for(int i = 0; i < n; ++i) {
		rmq[0][i + 1] = ans[i + 1];
	}
	for(int i = 0; i < 16; ++i) {
		for (int j = 0; j + (1 << (i + 1)) < n + 2; ++j) {
			rmq[i + 1][j] = min(rmq[i][j], rmq[i][j + (1 << i)]);
		}
	}
	for(int i = 0; i < m; ++i) {
		if (childs(a[i].l, a[i].r) != a[i].v) {
			out << "inconsistent";
			return 0;
		}
	}
	out << "consistent\n";
	for(int i = 0; i < n; ++i) {
		out << ans[i + 1] << " ";
	}
}

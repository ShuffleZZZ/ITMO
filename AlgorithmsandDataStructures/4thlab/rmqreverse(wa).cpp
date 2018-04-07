#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const long long neutral = (1ll << 31) + 10;

struct tree {
	long long x = neutral, y = -neutral;
};

bool sortx(pair <pair <int, int>, int> a, pair <pair <int, int>, int> b) {
	return (a.second < b.second);
}

void push(tree tr[], int ind, int l, int r) {
	if (tr[ind].y == -neutral) {
		return;
	}
	if (l != r) {
		tr[2 * ind].y = tr[ind].y;
		tr[2 * ind + 1].y = tr[ind].y;
	}
	tr[ind].x = tr[ind].y;
	tr[ind].y = -neutral;
}

void update(tree tr[], int ind, int l, int r, int tleft, int tright, int x) {
	if (tleft > tright) {
		return;
	}
	push(tr, ind, l, r);
	if ((tleft == l) and (tright == r)) {
		tr[ind].y = x;
		return;
	}
	int m = (l + r) / 2;
	update(tr, 2 * ind, l, m, tleft, min(m, tright), x);
	update(tr, 2 * ind + 1, m + 1, r, max(m + 1, tleft), tright, x);
	push(tr, 2 * ind, l, m);
	push(tr, 2 * ind + 1, m + 1, r);
	tr[ind].x = min(tr[2 * ind].x, tr[2 * ind + 1].x);
}

long long get(tree tr[], int ind, int l, int r, int tleft, int tright) {
	if (tleft > tright) {
		return neutral;
	}
	push(tr, ind, l, r);
	if ((tleft == l) and (tright == r)) {
		return tr[ind].x;
	}
	int m = (l + r) / 2;
	return min(get(tr, 2 * ind, l, m, tleft, min(m, tright)),
	get(tr, 2 * ind + 1, m + 1, r, max(m + 1, tleft), tright));
}

int main() {
	ifstream in;
	in.open("rmq.in");
	ofstream out;
	out.open("rmq.out");
	int n, m;
	in >> n >> m;
	pair <pair <int, int>, int> a[m + 1];
	for (int i = 0; i < m; ++i) {
		in >> a[i + 1].first.first >> a[i + 1].first.second >> a[i + 1].second;
	}
	sort(a + 1, a + m + 1, sortx);
	tree tr[4 * m + 10];
	for (int i = 0; i < m; ++i) {
		update(tr, 1, 1, n, a[i + 1].first.first, a[i + 1].first.second, a[i + 1].second);
	}
	for (int i = 0; i < m; ++i) {
		if (get(tr, 1, 1, n, a[i + 1].first.first, a[i + 1].first.second) != a[i + 1].second) {
			out << "inconsistent";
			return 0;
		}
	}
	out << "consistent" << '\n';
	for (int i = 0; i < n; ++i) {
		out << get(tr, 1, 1, n, i + 1, i + 1) << ' ';
	}
}

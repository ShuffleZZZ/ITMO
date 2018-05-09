#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct aero{
	int x1, y1, x2, y2;
};

bool sortx(aero a, aero b) {
	return ((b.x1 > a.x1) or (b.x2 < a.x2) and (b.x1 == a.x1));
}

const int maxv = 16777316;
const int shift = 2097152;
int n, res, res1, res2;
vector <int> b, c;

void push(int ind, int l, int r) {
	int x = b[ind];
	b[ind] = 0;
	if (l == r) {
		return;
	}
	c[2 * ind] += x;
	c[2 * ind + 1] += x;
	b[2 * ind] += x;
	b[2 * ind + 1] += x;
}

void add(int ind, int l, int r, int y1, int y2, int x2) {
	if (y1 > y2) {
	    return;
	}
	if ((l == y1) and (y2 == r)) {
		c[ind] += x2;
		b[ind] += x2;
		return;
	}
	push(ind, l, r);
	int m = (l + r) / 2;
	add(2 * ind, l, m, y1, min(m, y2), x2);
	add(2 * ind + 1, m + 1, r, max(m + 1, y1), y2, x2);
	c[ind] = max(c[2 * ind], c[2 * ind + 1]);
}

void find(int ind, int l, int r, int x1) {
	if (l == r) {
		if (res < c[ind]) {
			res = c[ind];
			res1 = x1;
			res2 = l;
		}
		return;
	}
	push(ind, l, r);
	int m = (l + r) / 2;
	if (c[2 * ind] > c[2 * ind + 1]) {
		find(2 * ind, l, m, x1);
	} else {
		find(2 * ind + 1, m + 1, r, x1);
	}
}

int main(){
	cin >> n;
	aero a[2 * n];
	b.resize(maxv, 0);
	c.resize(maxv, 0);
	for (int i = 0; i < n; i++){
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		a[2 * i].x1 = x1 + shift + 1;
		a[2 * i].x2 = 1;
		a[2 * i].y1 = y1 + shift + 1;
		a[2 * i].y2 = y2 + shift + 1;
		a[2 * i + 1].x1 = x2 + shift + 1;
		a[2 * i + 1].x2 = -1;
		a[2 * i + 1].y1 = y1 + shift + 1;
		a[2 * i + 1].y2 = y2 + shift + 1;
	}
	sort(a, a + 2 * n, sortx);
	res = -1;
	for (int i = 0; i < 2 * n; ++i) {
		add(1, 1, 2 * shift + 10, a[i].y1, a[i].y2, a[i].x2);
		find(1, 1, 2 * shift + 10, a[i].x1);
	}
	cout << res << '\n' << res1 - shift - 1 << ' ' << res2 - shift - 1;
}

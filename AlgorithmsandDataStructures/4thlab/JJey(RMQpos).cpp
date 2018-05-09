#include <iostream>
#include <vector>

using namespace std;

const int neutral = 2147483647;

struct tree {
	int l, r, value, x, d, num;
	bool in;
};

void buildtree(tree tr[], int x, int l, int r) {
	if (l >= r) return;
	tr[x].num = l;
	tr[x].x = x;
	tr[x].d = 0;
	tr[x].value = 0;
	tr[x].in = true;
	if (l + 1 == r) {
		tr[x].l = l;
		tr[x].r = r;
		return;
	}	
	int m = (l + r) / 2;
	buildtree(tr, 2 * x, l, m);
	buildtree(tr, 2 * x + 1, m, r);
	tr[x].l = tr[2 * x].l;
	tr[x].r = tr[2 * x + 1].r;
}

int value(tree tr[], int x) {
    if (!tr[x].in) {
        return tr[x].d;
    }
    return tr[x].value;
}

void clc(tree tr[], int x) {
    if (value(tr, 2 * x) > value(tr, 2 * x + 1)) {
    	tr[x].value = value(tr, 2 * x + 1);
		tr[x].num = tr[2 * x + 1].num;
    } else {
        tr[x].value = value(tr, 2 * x);
		tr[x].num = tr[2 * x].num;
    }
}

void push(tree tr[], int x) {
    if (!tr[x].in) {
        tr[2 * x].d = max(value(tr, tr[2 * x].x), tr[x].d);
        tr[2 * x + 1].d = max(value(tr, tr[2 * x + 1].x), tr[x].d);
        tr[2 * x].in = false;
        tr[2 * x + 1].in = false;
        tr[x].in = true;
    }
}

void update(tree tr[], int ind, int l, int r, int x) {
    if (l >= r) return;
    if ((tr[ind].l == l) and (tr[ind].r == r)) {
        tr[ind].d = max(value(tr, ind), x);
        tr[ind].in = false;
        return;
    }
    push(tr, ind);
    int m = (tr[ind].l + tr[ind].r) / 2;
    if (tr[ind].l < m) {
        update(tr, 2 * ind, l, min(r, m), x);
    }
    if (tr[ind].r >= m) {
        update(tr, 2 * ind + 1, max(l, m), r, x);
    }
    clc(tr, ind);
}

pair <int, int> get(tree tr[], int x, int l, int r) {
	pair <int, int> res;
	res.first = neutral;
	res.second = neutral;
	if ((tr[x].l >= r) or (tr[x].r <= l) or (l >= r)) {
		return res;
	}
	if ((tr[x].l == l) and (tr[x].r == r)) {
		res.first = value(tr, x);
		res.second = tr[x].num;
		return res;
	}
	push(tr, x);
	int m = (tr[x].l + tr[x].r) / 2;
    if (tr[x].l < m) {
    	pair <int, int> a = get(tr, 2 * x, l, min(r, m));
    	res = min(res, a);
    }
    if (tr[x].r >= m) {
        pair <int, int> a = get(tr, 2 * x + 1, max(l, m), r);
        res = min(res, a);
    }
    clc(tr, x);
	return res;
}

int main() {
	int n, m, o = 0;
	cin >> n >> m;
	tree tr[4 * n];
	buildtree(tr, 1, 0, n);
	pair <int, int> a[m];
	for (int i = 0; i < m; ++i) {
		string s;
		int k, l;
		cin >> s >> k >> l;
		if (s == "defend") {
			int m;
			cin >> m;
			update(tr, 1, k - 1, l, m);
		} else {
			a[o] = get(tr, 1, k - 1, l);
			o++;
		}
	}
	for (int i = 0; i < o; ++i) {
		cout << a[i].first << ' ' << a[i].second + 1 << '\n';
	}
}

#include <iostream>

using namespace std;

const long long neutral = 9223372036854775807;

struct tree {
	int l, r;
	long long value, add, set;
	bool in = false;
};

long long min(long long  a, long long b) {
	if (a <= b) return a;
	else return b;
}

void update(tree tr[], int x) {
	tr[x].value = min(tr[2 * x].value, tr[2 * x + 1].value);
}

void buildtree(long long a[], tree tr[], int x, int l, int r) {
	tr[x].l = l;
	tr[x].r = r;
	tr[x].add = neutral;
	tr[x].set = neutral;
	tr[x].in = true;
	if (l + 1 == r) {
		tr[x].value = a[l];
		return;
	}
	int m = (l + r) / 2;
	buildtree(a, tr, 2 * x, l, m);
	buildtree(a, tr, 2 * x + 1, m, r);
	update(tr, x);
}

void push(tree tr[], int x, int n) {
    if (tr[x].set != neutral) {
        if (((2 * x + 1) < 4 * n) and (tr[2 * x + 1].in)) {
        	tr[2 * x].set = tr[x].set;
        	tr[2 * x + 1].set = tr[x].set;
        	tr[2 * x].value = tr[x].set;
        	tr[2 * x + 1].value = tr[x].set;
        	tr[2 * x].add = neutral;
        	tr[2 * x + 1].add = neutral;
        }
        tr[x].set = neutral;
    }
    if (tr[x].add != neutral) {
        if (((2 * x + 1) < 4 * n) and (tr[2 * x + 1].in)) {
        	if (tr[2 * x].set != neutral) {
				tr[2 * x].set += tr[x].add;
			} else if (tr[2 * x].add != neutral) {
				tr[2 * x].add += tr[x].add;
			} else {
				tr[2 * x].add = tr[x].add;
			}
			tr[2 * x].value += tr[x].add;
        	if (tr[2 * x + 1].set != neutral) {
				tr[2 * x + 1].set += tr[x].add;
			} else if (tr[2 * x + 1].add != neutral) {
				tr[2 * x + 1].add += tr[x].add;
			} else {
				tr[2 * x + 1].add = tr[x].add;
			}
			tr[2 * x + 1].value += tr[x].add;
        }
        tr[x].add = neutral;
    }
}

long long get(tree tr[], int x, int l, int r, int n) {
	push(tr, x, n);
	if ((tr[x].l >= r) or (tr[x].r <= l)) {
		return neutral;
	}
	if ((tr[x].l >= l) and (tr[x].r <= r)) {
		return tr[x].value;
	}
	update(tr, x);
	return min(get(tr, 2 * x, l, r, n), get(tr, 2 * x + 1, l, r, n));
}

void set(tree tr[], int ind, int l, int r, long long x, int n) {
	if ((tr[ind].l >= r) or (tr[ind].r <= l)) {
		return;
	}
	push(tr, ind, n);
	if ((tr[ind].l >= l) and (tr[ind].r <= r)) {
		tr[ind].set = x;
        tr[ind].value = x;
        tr[ind].add = neutral;
		push(tr, ind, n);
		return;
	}
    set(tr, 2 * ind, l, r, x, n);
    set(tr, 2 * ind + 1, l, r, x, n);
    update(tr, ind);
}

/*void add(tree tr[], int ind, int l, int r, long long x, int n) {
	if ((tr[ind].l >= r) or (tr[ind].r <= l)) {
		return;
	}
	if ((tr[ind].l >= l) and (tr[ind].r <= r)) {
		if (tr[ind].set != neutral) {
			tr[ind].set += x;
		} else if (tr[ind].add != neutral) {
			tr[ind].add += x;
		} else {
			tr[ind].add = x;
		}
		tr[ind].value += x;
		push(tr, ind, n);
		return;
	}
	push(tr, ind, n);
    add(tr, 2 * ind, l, r, x, n);
    add(tr, 2 * ind + 1, l, r, x, n);
    update(tr, ind);
}*/

int main() {
	unsigned n;
	cin >> n;
	char s;
	while (cin >> s != 'E') {
		switch(s) {
			case('I'):
				int a, b, D;
				cin >> a >> b >> D;
				break;
			case('Q'):
				int h;
				cin >> h;
		}
	}
}

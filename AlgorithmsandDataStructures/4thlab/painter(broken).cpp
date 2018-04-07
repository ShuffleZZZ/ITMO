#include <fstream>

using namespace std;

const int shift = 500000;
const int neutral = 2147483648;

struct tree {
	int l, r, value = 0, set = neutral, amount = 0;
	bool in = false;
};

void update(tree tr[], int x) {
	tr[x].value = tr[2 * x].value + tr[2 * x + 1].value;
	tr[x].amount = tr[2 * x].amount + tr[2 * x + 1].amount;
	//if (a[tr[2 * x].r] == a[tr[2 * x + 1].l]) {
	//	tr[x].amount -= 1;
	//}
}

void buildtree(tree tr[], int x, int l, int r) {
	tr[x].l = l;
	tr[x].r = r;
	tr[x].in = true;
	if (l == r) {
		return;
	}
	int m = (l + r) / 2;
	buildtree(tr, 2 * x, l, m);
	buildtree(tr, 2 * x + 1, m + 1, r);
}

void push(tree tr[], int x, int n) {
    if (tr[x].set != neutral) {
        if (((2 * x + 1) < 4 * n) and (tr[2 * x + 1].in)) {
        	tr[2 * x].set = tr[x].set;
        	tr[2 * x + 1].set = tr[x].set;
        	tr[2 * x].value = tr[x].set;
        	tr[2 * x + 1].value = tr[x].set;
        	tr[2 * x].amount = tr[x].amount;
        	tr[2 * x + 1].amount = tr[x].amount;
        }
        tr[x].set = neutral;
    }
}

/*pair*/int get(tree tr[], int x, int l, int r, int n) {
	push(tr, x, n);
	if ((tr[x].l > r) or (tr[x].r < l)) {
		return /*{0, */0/*}*/;
	}
	if ((tr[x].l >= l) and (tr[x].r <= r)) {
		return /*{tr[x].amount, */tr[x].value/*}*/;
	}
	update(tr, x);
	return (get(tr, 2 * x, l, r, n) + get(tr, 2 * x + 1, l, r, n));
}

void set(tree tr[], int ind, int l, int r, int x, int n) {
	if ((tr[ind].l > r) or (tr[ind].r < l)) {
		return;
	}
	push(tr, ind, n);
	if ((tr[ind].l >= l) and (tr[ind].r <= r)) {
		tr[ind].set = x;
        tr[ind].value = x;
        tr[ind].amount += 1;
		push(tr, ind, n);
		return;
	}
    set(tr, 2 * ind, l, r, x, n);
    set(tr, 2 * ind + 1, l, r, x, n);
    update(tr, ind);
}

int main() {
	ifstream in;
	in.open("painter.in");
	ofstream out;
	out.open("painter.out");
	int n;
	in >> n;
	tree tr[4 * n];
	buildtree(tr, 1, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		char c; int x, l;
		in >> c >> x >> l;
		if (c == 'W') {
			set(tr, 1, x - 1, x + l - 1, 0, n);
			for (int i = 0; i < 4 * n; ++i) {
				out << tr[i].value << ' ' << tr[i].l << ' ' << tr[i].r << ' ' << i << '\n';
			}
			//out << get(tr, 1, 0, n, n) << '\n';
		} else {
			set(tr, 1, x - 1, x + l - 1, 1, n);
			for (int i = 0; i < 4 * n; ++i) {
				out << tr[i].value << ' ' << tr[i].l << ' ' << tr[i].r << ' ' << i << '\n';
			}
			//out << get(tr, 1, 0, n, n) << '\n';
		}
	}
	in.close();
	out.close();
}
	

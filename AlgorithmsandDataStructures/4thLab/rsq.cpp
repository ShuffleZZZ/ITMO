#include <fstream>

using namespace std;

struct tree {
	int l, r;
	long long value;
};

void update(tree tr[], int x) {
	tr[x].value = tr[2 * x].value + tr[2 * x + 1].value;
}

void buildtree(long long a[], tree tr[], int x, int l, int r) {
	tr[x].l = l;
	tr[x].r = r;
	if (l + 1 == r) {
		tr[x].value = a[l];
		return;
	}
	int m = (l + r) / 2;
	buildtree(a, tr, 2 * x, l, m);
	buildtree(a, tr, 2 * x + 1, m, r);
	update(tr, x);
}

long long get(tree tr[], int x, int l, int r) {
	if ((tr[x].l >= r) or (tr[x].r <= l)) {
		return 0;
	}
	if ((tr[x].l >= l) and (tr[x].r <= r)) {
		return tr[x].value;
	}
    return (get(tr, x * 2, l, r) + get(tr, x * 2 + 1, l, r));
}

void set(tree tr[], int ind, int place, long long x) {
    if ((tr[ind].l > place) or (tr[ind].r <= place)) {
        return;
    }
    if ((tr[ind].l + 1 == tr[ind].r) and (tr[ind].l == place)) {
        tr[ind].value = x;
        return;
    }
    set(tr, ind * 2, place, x);
    set(tr, ind * 2 + 1, place, x);
    update(tr, ind);
}

int main() {
	ifstream in;
    in.open("rsq.in");
    ofstream out;
    out.open("rsq.out");
    int n;
    in >> n;
    long long  a[n];
    for (int i = 0; i < n; i++) {
    	in >> a[i];
    }
	tree tr[4 * n];
	buildtree(a, tr, 1, 0, n);
	while (in) {
	    string s;
	    long long i, j;
	    in >> s >> i >> j;
	    if(s == "set") {
	        set(tr, 1, i - 1, j);
	    } else if(s == "sum") {
	        long long res = get(tr, 1, i - 1, j);
	        out << res << '\n';
	    }
	}
	in.close();
	out.close();
}

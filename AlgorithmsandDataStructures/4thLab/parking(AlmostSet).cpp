#include <fstream>

using namespace std;

const int neutral = -1;

struct tree {
	int l, r, value;
};

void update(tree tr[], int x) {
    if (tr[x * 2].value != -1) {
        tr[x].value = tr[x * 2].value;
    } else {
        tr[x].value = tr[x * 2 + 1].value;
    }
}

void buildtree(tree tr[], int x, int l, int r) {
	tr[x].l = l;
	tr[x].r = r;
	if (l + 1 == r) {
		tr[x].value = l;
		return;
	}
	int m = (l + r) / 2;
	buildtree(tr, 2 * x, l, m);
	buildtree(tr, 2 * x + 1, m, r);
	update(tr, x);
}

int get(tree tr[], int x, int l, int r) {
	if ((tr[x].l >= r) or (tr[x].r <= l)) {
		return neutral;
	}
	if ((tr[x].l >= l) and (tr[x].r <= r)) {
		return tr[x].value;
	}
    int a = get(tr, x * 2, l, r);
    if (a == -1) {
        a = get(tr, x * 2 + 1, l, r);
    }
    return a;
}

void set(tree tr[], int ind, int place, int x) {
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

int min(tree tr[], int l, int r) {
    int a = get(tr, 1, l, r);
    if (a == neutral) {
        a = get(tr, 1, 0, l);
    }
    return a;
}

int main() {
	ifstream in;
    in.open("parking.in");
    ofstream out;
    out.open("parking.out");
    int n, m;
    in >> n >> m;
    tree tr[4 * n];
   	buildtree(tr, 1, 0, n);
    for (int i = 0; i < m; i++) {
    	string s;
    	in >> s;
    	int a;
    	int b;
    	if (s == "enter") {
    		in >> a;
    		b = min(tr, a - 1, n);
    		out << b + 1 << '\n';
    		set(tr, 1, b, -1);
    	} else {
    		in >> a;
    		set(tr, 1, a - 1, a - 1);
    	}
    }
    in.close();
    out.close();
}

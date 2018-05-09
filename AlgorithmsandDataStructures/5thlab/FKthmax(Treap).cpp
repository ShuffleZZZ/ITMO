#include<iostream>

using namespace std;

struct tree {
	int x = 0, pos = 0, y;
	tree *l = NULL, *r = NULL;
};

tree *root, *L, *R, *mostR, *mid;

void update(tree *tr) {
	if (tr != NULL) {
	tr -> pos = 1;
		if ( tr -> l != NULL) tr -> pos += tr -> l -> pos;
		if ( tr -> r != NULL) tr -> pos += tr -> r -> pos;
	}
}

void split(tree *tr, int x, tree* &t1, tree* &t2) {
	update(tr); update(t1); update(t2);
	if (tr == NULL) {
		t2 = t1 = NULL;
		return;
	}
	if (tr -> x >= x) {
		split(tr -> l, x, t1, tr -> l);
	 	t2 = tr;
	} else {
		split(tr -> r, x, tr -> r, t2);
		t1 = tr;
	}
	update(t1); update(t2); update(tr);
}

void merge(tree* &t, tree* l, tree* r) {
    update(l); update(r); update(t);
    if (l == NULL) {
		t = r;
		return;
	}
	if (r == NULL) {
    	t = l;
		return;
    }
    if (l -> y > r -> y) {
		merge(l -> r, l -> r, r);
	  	t = l;
    } else {
		merge(r->l, l, r->l);
		t = r;
	}
    update(l); update(r); update(t);
}

int get(tree *tr, int x) {
	int temp = 0;
	if (tr -> r != NULL) temp = tr -> r -> pos;
	if (x - 1 == temp) return tr -> x;
	if (temp < x) return get(tr -> l, x - temp - 1);
	else return get(tr -> r, x);
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int q, x;
	    cin >> q >> x;
	    if (q > 0) {
			tree* tmp = new tree;
			tmp -> x = x;
			tmp -> pos = 1;
			tmp -> y = rand();
			split(root, x, L, R);
			merge(R, tmp, R);
			merge(root, L, R);
		} else if (q == 0) {
			cout << get(root, x) << '\n';
		} else {
			split(root, x, L, R);
			split(R, x + 1, mid, mostR);
			merge(root, L, mostR);
		}
	}
}

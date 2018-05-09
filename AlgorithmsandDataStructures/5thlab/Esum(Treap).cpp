#include <iostream>

using namespace std;

struct tree {
    int y = 0;
    long long x = 0, sum = 0;
    tree * l = 0, * r = 0;
};

void update (tree* &tr) {
    tr -> sum = tr -> x;
    if (tr -> l != NULL) tr -> sum += tr -> l -> sum;
    if (tr -> r != NULL) tr -> sum += tr -> r -> sum;
}

tree *root = NULL;

void split (tree *tr, long long k, tree* &t1, tree* &t2) {
    if (tr == NULL) {
		t1 = t2 = NULL;
		return;
	}
    if (tr -> x < k) {
        t1 = tr;
        split(t1 -> r, k, t1 -> r, t2);
        update(t1);
    } else {
        t2 = tr;
        split(t2 -> l, k, t1, t2 -> l);
        update(t2);
    }
}

void merge (tree *t1, tree *t2, tree* &tr) {
    if (t1 == NULL) {
		tr = t2;
		return;
	}
    if (t2 == NULL) {
		tr = t1;
		return;
	}
    if (t1 -> y < t2 -> y) {
        tr = t1;
        merge(tr -> r, t2, tr -> r);
    } else {
        tr = t2;
        merge(t1, tr -> l, tr -> l);
    }
    update(tr);
}

bool find (tree *tr, long long k) {
    if (tr == NULL) return 0;
    if (tr -> x == k) return 1;
    else if (k < tr -> x) return find(tr -> l, k);
    else return find(tr -> r, k);
}

void add (long long k) {
    if (find(root, k)) return;
    tree * temp = new tree;
    temp -> x = k;
    temp -> y = rand() * (1 << 15) + rand();
    update(temp);
    tree *l = new tree, *r = new tree;
    split(root, k, l, r);
    merge(l, temp, l);
    merge(l, r, root); 
}

long long get (int left, int right) {
    tree * l, * m, * r;
    split(root, left, l, m);
    split(m, right + 1, m, r);
    long long res = 0;
    if (m != NULL) res = m -> sum;
    merge(l, m, m);
    merge(m, r, root);
    return res;
}

int main () {
	int n;
    cin >> n;
    long long last = 0;
    bool was = 0;
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        if (c == '?') {
            int l, r;
            cin >> l >> r;  
            was = 1;
            last = get(l, r);
            cout << last << "\n";
        } else if (c == '+') {
            long long i;
            cin >> i;
            if (was) i = (i + last) % 1000000000;
            was = 0;
            add(i);
        }
    }
}

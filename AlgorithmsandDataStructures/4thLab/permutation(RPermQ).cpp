#include <fstream>
#include <set>

using namespace std;

const int neutral = 1488322228;

int a[100200];

struct tree {
    int lv, rv;
    tree *l, *r;
    int x, prev;
    tree(int lv, int rv) : lv(lv), rv(rv) {
        x = a[lv];
    }
    tree(tree *l, tree *r) : l(l), r(r) {
        lv = l -> lv;
        rv = r -> rv;
        x = max(l -> x, r -> x);
    }
};

tree *buildtree(int l, int r) {
    if (l + 1 == r) return new tree(l, r);
    int m = (l + r) / 2;
    return new tree(buildtree(l, m), buildtree(m, r));
}

void update(tree *tr, int ind, int value) {
    if (tr -> lv + 1 == tr -> rv) {
        tr -> x = value;
        return;
    }
    if (ind < tr -> l -> rv) update(tr -> l, ind, value);
    else update(tr -> r, ind, value);
    tr -> x = max(tr -> l -> x, tr -> r -> x);
}

void update2(tree *tr, int ind, int value) {
    if (tr -> lv + 1 == tr -> rv) {
        tr -> prev = value;
        return;
    }
    if (ind < tr -> l -> rv) update2(tr -> l, ind, value);
    else update2(tr -> r, ind, value);
    tr -> prev = max(tr -> l -> prev, tr -> r -> prev);
}

int get(tree *tr, int l, int r) {
    if ((tr -> rv <= l) or (r <= tr -> lv)) return -neutral;
    if ((l <= tr -> lv) and (tr -> rv <= r)) return tr -> x;
    return max(get(tr -> l, l, r), get(tr -> r, l, r));
}

int get2(tree *tr, int l, int r) {
    if ((tr -> rv <= l) or (r <= tr -> lv)) return -neutral;
    if ((l <= tr -> lv) and (tr -> rv <= r)) return tr -> prev;
    return max(get2(tr -> l, l, r), get2(tr -> r, l, r));
}

int main() {
    ifstream in;
    in.open("permutation.in");
    ofstream out;
    out.open("permutation.out");
    int n, m;
    in >> n;
    set <int> set[n + 1];
    for (int i = 1; i <= n; i++) {
        in >> a[i];
        set[a[i]].insert(i);
        set[i].insert(-1);
    }
    tree *tr = buildtree(0, n + 1);
    for (int i = 1; i <= n; i++) {
        for (auto j = ++set[i].begin(), prev = set[i].begin(); j != set[i].end(); ++j, ++prev) {
            update2(tr, *j, *prev);
        }
    }
    in >> m;
    for (int i = 0; i < m; i++) {
        int t, x, y;
        in >> t >> x >> y;
        if (t == 2) {
        	if ((get(tr, x, y + 1) + x == y + 1) and (get2(tr, x, y + 1) < x)) {
                out << "YES" << '\n';
            } else {
                out << "NO" << '\n';
            }
        } else {
            if (set[a[x]].upper_bound(x) != set[a[x]].end()) {
                int prev = *(--set[a[x]].lower_bound(x));
                int next = *set[a[x]].upper_bound(x);
                update2(tr, next, prev);
            }
            set[a[x]].erase(x);
            set[y].insert(x);
            a[x] = y;
            int prev = *(--set[a[x]].lower_bound(x));
            update2(tr, x, prev);
            if (set[a[x]].upper_bound(x) != set[a[x]].end()) {
                int next = *set[a[x]].upper_bound(x);
                update2(tr, next, x);
            }
            update(tr, x, y);
        }
    }
    in.close();
    out.close();
}

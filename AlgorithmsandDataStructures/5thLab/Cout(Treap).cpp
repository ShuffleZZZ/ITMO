#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int neutral = 1e7;

struct tree {
    int x, y;
    int p, l, r;
    int n;
};

struct treeDek {
    int l, r;
    int left, right;
    int k, ind;
};

bool xdef(tree a, tree b) {
    return (a.x < b.x);
}

bool ndef(tree a, tree b) {
    return (a.n < b.n);
}

vector<tree> tree;
vector<treeDek> treeDek;

int n;
int rootheap = 0;
int rootDek = -1;

int buildtreeDek(int l, int r) {
	treeDek[rootheap].l = l;
    treeDek[rootheap].r = r;
    int root = rootheap++;
    if (l + 1 == r) {
        treeDek[root].k = tree[l].y;
        treeDek[root].ind = l;
        return root;
    }
    int m = (l + r) / 2;
    int L = treeDek[root].left = buildtreeDek(l, m);
    int R = treeDek[root].right = buildtreeDek(m, r);
    if (treeDek[L].k > treeDek[R].k) {
    	treeDek[root].k = treeDek[R].k;
        treeDek[root].ind = treeDek[R].ind;
    } else {
        treeDek[root].k = treeDek[L].k;
        treeDek[root].ind = treeDek[L].ind;
    }
    return root;
}

int indmin(int ind, int l, int r) {
    if ((treeDek[ind].r <= l) or (treeDek[ind].l >= r)) return n;
    if ((l <= treeDek[ind].l) and (treeDek[ind].r <= r)) return treeDek[ind].ind;
    int L = indmin(treeDek[ind].left, l, r);
    int R = indmin(treeDek[ind].right, l, r);
    if (tree[L].y > tree[R].y) return R;
    else return L;
}

int buildtree(int l, int r) {
    if (l == r) return -1;
    int root = indmin(rootDek, l, r);
    int left = tree[root].l = buildtree(l, root);
    int right = tree[root].r = buildtree(root + 1, r);
    if (left == -1) tree[root].l = left;
    else tree[root].l = tree[left].n;
    if (right == -1) tree[root].r = right;
    else tree[root].r = tree[right].n;
    if ((l == 0) and (r == n)) tree[root].p = -1;
    if (left != -1) tree[left].p = tree[root].n;
    if (right != -1) tree[right].p = tree[root].n;
    return root;
}

int main() {
    cin >> n;
    tree.resize(n + 1);
    treeDek.resize(2 * n + 1);
    for (int i = 0; i < n; i++) {
        cin >> tree[i].x >> tree[i].y;
        tree[i].n = i;
    }
    tree[n].y = tree[n].x = tree[n].n = neutral;
    sort(tree.begin(), tree.end(), xdef);
    rootDek = buildtreeDek(0, n);
    buildtree(0, n);
    sort(tree.begin(), tree.end(), ndef);
    cout << "YES" << '\n';
    for (int i = 0; i < tree.size() - 1; i++) {
        cout << tree[i].p + 1 << ' ' << tree[i].l + 1 << ' ' << tree[i].r + 1 << '\n';
    }
}

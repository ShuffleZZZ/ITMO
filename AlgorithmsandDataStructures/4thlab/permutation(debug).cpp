#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 123;
const int INF = 1234567890;

int n;
int a[N];

struct Node {
    int L, R;
    Node *l, *r;
    int mx, prevmx;

    Node() {}
    Node(int L, int R) : L(L), R(R) {
        mx = a[L];
    }
    Node(Node *l, Node *r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        mx = max(l->mx, r->mx);
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void update1(Node *node, int pos, int val) {
    if (node->R - node->L == 1) {
        node->mx = val;
        return;
    }
    if (pos < node->l->R) update1(node->l, pos, val);
    else update1(node->r, pos, val);
    node->mx = max(node->l->mx, node->r->mx);
}

int getmax1(Node *node, int L, int R) {
    if (node->R <= L || R <= node->L) return -INF;
    if (L <= node->L && node->R <= R) return node->mx;
    return max(getmax1(node->l, L, R), getmax1(node->r, L, R));
}

void update2(Node *node, int pos, int val) {
    if (node->R - node->L == 1) {
        node->prevmx = val;
        return;
    }
    if (pos < node->l->R) update2(node->l, pos, val);
    else update2(node->r, pos, val);
    node->prevmx = max(node->l->prevmx, node->r->prevmx);
}

int getmax2(Node *node, int L, int R) {
    if (node->R <= L || R <= node->L) return -INF;
    if (L <= node->L && node->R <= R) return node->prevmx;
    return max(getmax2(node->l, L, R), getmax2(node->r, L, R));
}

int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);

    scanf("%d", &n);

    vector< set<int> > pos(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        pos[a[i]].insert(i);
        pos[i].insert(-1);
    }

    Node *root = buildTree(0, n + 1);

    for (int i = 1; i <= n; i++) {
        for (auto it = ++pos[i].begin(), prev = pos[i].begin(); it != pos[i].end(); it++, prev++) {
            update2(root, *it, *prev);
        }
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);

        if (t == 1) {
            if (pos[a[x]].upper_bound(x) != pos[a[x]].end()) {
                int prev = *(--pos[a[x]].lower_bound(x));
                int nxt = *pos[a[x]].upper_bound(x);
                update2(root, nxt, prev);
            }
            pos[a[x]].erase(x);
            a[x] = y;
            pos[a[x]].insert(x);
            int prev = *(--pos[a[x]].lower_bound(x));
            update2(root, x, prev);
            if (pos[a[x]].upper_bound(x) != pos[a[x]].end()) {
                int nxt = *pos[a[x]].upper_bound(x);
                update2(root, nxt, x);
            }
            update1(root, x, y);
        } else {
            int mx1 = getmax1(root, x, y + 1);
            int mx2 = getmax2(root, x, y + 1);
            if (mx1 == y - x + 1 && mx2 < x) {
                puts("YES");
            } else {
                puts("NO");
            }
        }
    }
}

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100000;

struct tree {
    int value = 0, length = 0, x, lv;
    bool l = 0, r = 0, push = false, p = false;
    char c;
};

tree tr[8 * maxn];
vector <int> have;

int get(int pos) {
    return lower_bound(have.begin(), have.end(), pos) - have.begin();
}

void apply(int ind, int l, int r, bool value) {
    tr[ind].length = (have[r] - have[l]) * value;
    tr[ind].value = tr[ind].l = tr[ind].r = value;
    tr[ind].push = true;
    tr[ind].p = value;
}

void push(int ind, int l, int r) {
    if (tr[ind].push) {
        int m = (l + r) / 2;
        apply(ind * 2 + 1, l, m, tr[ind].p);
        apply(ind * 2 + 2, m, r, tr[ind].p);
        tr[ind].push = false;
    }
}

void update(int ind, int l, int r) {
    tr[ind].length = tr[ind * 2 + 1].length + tr[ind * 2 + 2].length;
    tr[ind].value = tr[ind * 2 + 1].value + tr[ind * 2 + 2].value - (tr[ind * 2 + 1].r & tr[ind * 2 + 2].l);
    tr[ind].l = tr[ind * 2 + 1].l;
    tr[ind].r = tr[ind * 2 + 2].r;    
}

void set(int ind, int l, int r, int L, int R, bool value) {
    if (L <= l && r <= R) {
        apply(ind, l, r, value);
        return;
    }    
    if (r <= L || R <= l) {
        return;
    }
    push(ind, l, r);
    int m = (l + r) / 2;
    set(ind * 2 + 1, l, m, L, R, value);
    set(ind * 2 + 2, m, r, L, R, value);
    update(ind, l, r);    
}

int main () {
    ifstream in;
	in.open("painter.in");
	ofstream out;
	out.open("painter.out");
	int n;
    in >> n;
    for (int i = 0; i < n; ++i) {
        in >> tr[i].c >> tr[i].x >> tr[i].lv;
        have.push_back(tr[i].x);
        have.push_back(tr[i].x + tr[i].lv);
    }
    sort(have.begin(), have.end());
    have.resize(unique(have.begin(), have.end()) - have.begin());
    for (int i = 0; i < n; i++) {
        set(0, 0, have.size() - 1, get(tr[i].x), get(tr[i].x + tr[i].lv), tr[i].c == 'B');
        out << tr[0].value << ' ' << tr[0].length << '\n';
    }
    in.close();
    out.close();
}

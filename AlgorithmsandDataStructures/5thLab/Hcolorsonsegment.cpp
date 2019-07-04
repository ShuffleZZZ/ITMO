#include <fstream>

using namespace std;
 
struct tree {
    int x1, x2, y = rand(), ch;
    uint32_t chbits;
    tree *l = NULL, *r = NULL;
};

tree *root = NULL;
 
void update(tree* tr) {
	if (tr != NULL) {
		tr -> x1 = tr -> x2;
		tr -> chbits = (1 << tr -> ch);
		if (tr -> l != NULL) {
			tr -> x1 += tr -> l -> x1;
			tr -> chbits |= tr -> l -> chbits;
		}
		if (tr -> r != NULL) {
			tr -> x1 += tr -> r -> x1;
			tr -> chbits |= tr -> r -> chbits;
		}
    }
}
 
tree* merge(tree* t1, tree* t2) {
	if (t2 == NULL) return t1;
	if (t1 == NULL) return t2;
	if (t1 -> y > t2 -> y) {
		t1 -> r = merge (t1 -> r, t2);
		update(t1 -> r);
		update(t1);
		return t1;
	}
    t2 -> l = merge(t1, t2 -> l);
    update(t2 -> l);
    update(t2);
    return t2;
}
 
pair <tree*, tree*> split(tree* tr, int k) {
	if (tr == NULL) return {NULL, NULL};
	int size = 1;
	if (tr -> l != NULL) size += tr -> l -> x1;
	if ((size < k) and (k <= size + tr -> x2)) {
		tree* temp1 = new tree;
		temp1 -> ch = tr -> ch;
		temp1 -> chbits = (1 << tr -> ch);
		tree* temp2 = new tree;
		temp2 -> ch = tr -> ch;
		temp2 -> chbits = (1 << tr -> ch);
		temp1 -> x2 = k - size;
		temp1 -> x1 = k - size;
		temp2 -> x2 = tr -> x2 - k + size;
		temp2 -> x1 = tr -> x2 - k + size;
        pair<tree*, tree*> temp = {temp1, temp2};
        if (temp.first -> x2) temp.first -> l = tr -> l;
        else temp.first = tr -> l;
        if (temp.second -> x2) temp.second -> r = tr -> r;
        else temp.second = tr -> r;
        update(temp.first);
        update(temp.second);
        return temp;
    }
    if (k > size + tr -> x2) {
        pair<tree*, tree*> temp = split(tr -> r, k - size + 1 - tr -> x2);
        tr -> r = temp.first;
        update(tr -> r);
        update(tr);
        update(temp.second);
        return {tr, temp.second};
    }
    pair<tree*, tree*> temp = split(tr -> l, k);
    tr -> l = temp.second;
    update(tr -> l);
    update(tr);
    update(temp.first);
    return {temp.first, tr};
}
 
tree* insert(tree* tr, char ch, int l, int r) {
	tree* t1 = new tree;
	t1 -> ch = ch;
	t1 -> chbits = (1 << ch);
	t1 -> x2 = r - l + 1;
	t1 -> x1 = r - l + 1;
	if (tr == NULL) return t1;
    pair<tree*, tree*> temp = split(tr, l);
    return merge(merge(temp.first, t1), temp.second);
}
 
tree* remove(tree *tr, int l, int r) {
	if (tr == NULL) return tr;
	if ((r <= 0) or (l > tr -> x1)) return tr;
	if ((r >= tr -> x1) and (l <= 1)) return NULL;
	int size = tr -> x2;
	if (tr -> l != NULL) size += tr -> l -> x1;
    tr -> l = remove(tr -> l, l, r);
    tr -> r = remove(tr -> r, l - size, r - size);
    update(tr -> l);
    update(tr -> r);
    if ((l <= size) and (r > size - tr -> x2)) {
    	if ((l <= size - tr -> x2 + 1) and (r >= size)) tr = merge(tr -> l, tr -> r);
        else {
        	tr -> x2 = max(l - size + tr -> x2 - 1, 0);
        	if (size > r) tr -> x2 += size - r;
        }
    }
    update(tr);
    return tr;
}
 
int get(tree* tr, int l, int r) {
	if (tr == NULL) return 0;
	if ((r <= 0) or (l > tr -> x1)) return 0;
	if ((l <= 1) and (r >= tr -> x1)) return tr -> chbits;
	int size = tr -> x2;
	if (tr -> l != NULL) size += tr -> l -> x1;
	int res = 0;
	if ((l <= size) and (r > size - tr -> x2)) res = (1 << tr -> ch);
    return res | get(tr -> l, l, r) | get(tr -> r, l - size, r - size);
}
 
int main() {
	ifstream in;
	in.open("log.in");
	ofstream out;
	out.open("log.out");
	int n;
	in >> n;
    for (int i = 0; i < n; ++i) {
    	char c; int a, b;
    	in >> c >> a >> b;
        if (c == '+') {
        	char l;
        	in >> l;
        	root = insert(root, l - 97, a, a + b - 1);
		} else if (c == '-') {
			root = remove(root, a, a + b - 1);
		} else if (c == '?') { 
			int res = 0;
			for (int i = get(root, a, b); i > 0; i >>= 1)
				res += i & 1;
			out << res << '\n';
			//out << __builtin_popcount(get(root, a, b)) << '\n'; 
		}
    }
    in.close();
    out.close();
}

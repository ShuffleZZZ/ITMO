#include <iostream>

using namespace std;

struct SPtree{
    int x;
    SPtree* l = NULL;
    SPtree* r = NULL;
    SPtree* p = NULL;
};

SPtree* root = NULL;
SPtree* t1 = NULL;
SPtree* t2 = NULL;

SPtree* searchInTree (SPtree* tr, int k) {
    if (tr == root) {
        t1 = NULL;
        t2 = NULL;
    }
    if ((tr == NULL) or (tr -> x == k)) return tr;
    if (tr -> x > k) {
        if ((t2 == NULL) or (t2 -> x > tr -> x)) t2 = tr;
        return searchInTree(tr -> l, k);
    } else {
        if((t1 == NULL) or (t1 -> x < tr -> x)) t1 = tr;
        return searchInTree(tr -> r, k);
    }
    SPtree *temp = NULL;
    return temp;
}

void rotateL (SPtree* tr) {
    SPtree* temp = tr -> r;
    tr -> r = temp -> l;
    if (temp -> l != NULL) temp -> l -> p = tr;
    temp -> p = tr -> p;
    if (tr -> p == NULL) root = temp;
    else if(tr == tr -> p -> l) tr -> p -> l = temp;
    else tr -> p -> r = temp;
    temp -> l = tr;
    tr -> p = temp;
}

void rotateR (SPtree* tr) {
    SPtree* temp = tr -> l;
    tr -> l = temp -> r;
    if (temp -> r != NULL) temp -> r -> p = tr;
    temp -> p = tr -> p;
    if (tr -> p == NULL) root = temp;
	else if (tr == tr -> p -> l) tr -> p -> l = temp;
    else tr -> p -> r = temp;
    temp -> r = tr;
    tr -> p = temp;
}

void splay (SPtree* tr) {
    if (tr == NULL) return;
    while (tr -> p != NULL) {
        if (tr -> p -> p == NULL) {
            if (tr -> p -> l == tr) rotateR(tr -> p);
            else rotateL(tr -> p);
        } else if ((tr -> p -> l == tr) and (tr -> p -> p -> l == tr -> p)) {
            rotateR(tr -> p -> p);
            rotateR(tr -> p);
        } else if ((tr -> p -> r == tr) and (tr -> p -> p -> r == tr -> p)) {
            rotateL(tr -> p -> p);
            rotateL(tr -> p);
        } else if ((tr -> p -> l == tr) and (tr -> p -> p -> r == tr -> p)) {
            rotateR(tr -> p);
            rotateL(tr -> p);
        } else { 
            rotateL(tr -> p);
            rotateR(tr -> p);
        }
    }
}

bool exists (SPtree* tr, int k) {
    if (tr == NULL) return false;
    else if (tr -> x == k) {
        splay(tr);
        return true;
	} else if (tr -> x > k) return exists(tr -> l, k);
    else return exists(tr -> r, k);
}

SPtree* minval (SPtree* tr) {
    if (tr -> l == NULL) {
        splay(tr);
        return tr;
    }
    return minval(tr -> l);
}

SPtree* maxval (SPtree* tr) {
    if (tr -> r == NULL) {
        splay(tr);
        return tr;
    }
    return maxval(tr -> r);
}

void remove (SPtree* tr) {
    SPtree* temp = new SPtree;
    if ((tr -> l != NULL) and (tr -> r != NULL)) {
        if (tr -> r != NULL) temp = minval(tr -> r);
        else temp = t2;
        int mk = temp -> x;
        remove(temp);
        tr -> x = mk;
    } else if ((tr -> l != NULL) or (tr -> r != NULL)) {
        temp = (tr -> l == NULL ? tr -> r : tr -> l);
        if (tr -> p == NULL) {
            root = temp;
            temp -> p = NULL;
            return;
        }
        if (tr -> p -> l == tr) {
            tr -> p -> l = temp;
            temp -> p = tr -> p;
        } else {
            tr -> p -> r = temp;
            temp -> p = tr -> p;
        }
    } else if ((tr -> l == NULL) and (tr -> l == NULL)) {
        if (tr -> p == NULL) {
            root = NULL;
            return;
        }
        if (tr -> p -> l == tr) tr -> p -> l = NULL;
        else tr -> p -> r = NULL;
    }
}

SPtree* nextval (int k) {
    SPtree* temp = searchInTree(root, k);
    if ((temp != NULL) and (temp -> r != NULL)) return minval(temp -> r);
    if (t2 != NULL) splay(t2);
    if ((t2 == NULL) or (t2 -> x <= k)) {
    	SPtree *out = NULL;
    	return out;
    } else return t2;
}

SPtree* prevval (int k) {
    SPtree* temp = searchInTree(root, k);
    if ((temp != NULL) and (temp -> l != NULL)) return maxval(temp -> l);
    if (t1 != NULL) splay(t1);
    if ((t1 == NULL) or(t1 -> x >= k)) {
    	SPtree *out = NULL;
    	return out;
    } else return t1;
}

void ins (SPtree* tree1, SPtree* tree2) {
    if (tree2 -> x > tree1 -> x) {
        if (tree1 -> r != NULL) {
            ins(tree1 -> r, tree2);
            return;
        } else {
            tree1 -> r = tree2;
            tree2 -> p = tree1;
            return;
        }
    } else if (tree1 -> l != NULL) {
        ins(tree1 -> l, tree2);
        return;
    } else {
        tree1 -> l = tree2;
        tree2 -> p = tree1;
        return;
    }
}

void insert (int k) {
    if (exists(root, k)) return;
    SPtree* temp = new SPtree;
    temp -> x = k;
    if (root != NULL) {
        ins(root, temp);
        splay(temp);
    } else root = temp;
}

int main() {
    /*string s;
	while(cin >> s) {
		int a;
		cin >> a;
        if (s == "insert") {
			insert(a);
		} else if (s == "delete") {
			SPtree* tmp = searchInTree(root, a);
    		if(tmp != NULL) remove(tmp);
        } else if (s == "exists") {
            cout << (exists(root, a) ? "true\n" : "false\n");
        } else if (s == "next") {
            SPtree* temp = nextval(a);
            if (temp == NULL) {
                cout << "none" << '\n';
            } else {
                cout << temp -> x << '\n';
            }
        } else if (s == "prev") {
            SPtree *temp = prevval(a);
            if (temp == NULL) {
                cout << "none" << '\n';
            } else {
                cout << temp -> x << '\n';
            }
    	}
    }
    return 0;*/
}

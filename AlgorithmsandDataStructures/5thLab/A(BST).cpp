#include <iostream>

using namespace std;

const int MAGIC = 3221488;

struct tree {
	int x;
	tree *l = NULL, *r = NULL;//, *p = NULL;
};
	
void insert(tree* &tr, int value) {
	if (tr == NULL) {
		tree *t1 = new tree;
		t1 -> x = value;
		//t1 -> p = tr;
		tr = t1;
	} else if (value < tr -> x) {
		/*if (tr -> l == NULL) {
			tree *t1 = new tree;
			t1 -> x = value;
			//t1 -> p = tr;
			tr -> l = t1;
		} else {*/
			insert(tr -> l, value);
	} else if (value > tr -> x) {
		/*if (tr -> r == NULL) {
			tree *t1 = new tree;
			t1 -> x = value;
			//t1 -> p = tr;
			tr -> r = t1;
		} else {*/
			insert(tr -> r, value);
	}
	return;
}

int exists(tree* tr, int k) {
	if (tr == NULL) return -1;
	if (tr -> x == k) return 1;
	if ( tr -> x < k) return exists(tr -> r, k);
	return exists( tr -> l, k);
}

tree *minval(tree* &tr) {
	if (tr -> l == NULL) return tr;
	return minval(tr -> l);
}

/*int maxval(tree* &tr) {
	if (tr -> r == NULL) return tr -> x;
	else return maxval(tr -> r);
}*/

tree *next(tree* &tr, int k) {
   	tree *root = tr;
    tree *ans = NULL;
    while (root != NULL) {
        if (root -> x > k) {
            ans = root;
            root = root -> l;
        } else {
            root = root -> r;
        }
    }
    return ans;
}

tree *prev(tree* &tr, int k) {
    tree *root = tr;
    tree *ans = NULL;
    while (root != NULL) {
        if (root -> x < k) {
            ans = root;
            root = root -> r;
        } else {
            root = root -> l;
        }
    }
    return ans;
}

/*void deleter(tree* &tr, int k) {
	if (tr == NULL) {
        return;
    }
    if (k < tr -> x) {
        deleter(tr -> l, k);
    } else if (k > tr -> x) {
        deleter(tr -> r, k);
    } else if ((tr -> l != NULL) and (tr -> r != NULL)) {
        tree *m = tr -> r;
        while (m -> l != NULL) {
            m = m -> l;
        }
        tr -> x = m -> x;
        m -> p -> l = NULL;
        delete m;
    } else if (tr -> l != NULL) {
    	if (tr -> p == NULL) {
    		tr -> l -> p = NULL;
    	} else if (tr -> p -> l == tr) {
        	tr -> p -> l = tr -> l;
        	tr -> l -> p = tr -> p;
        } else {
        	tr -> p -> r = tr -> l;
        	tr -> l -> p = tr -> p;
        }
        delete tr;
    } else if (tr -> r != NULL) {
    	if (tr -> p == NULL) {
    		tr -> r -> p = NULL;
    	} else if (tr -> p -> l == tr) {
        	tr -> p -> l = tr -> r;
        	tr -> r -> p = tr -> p;
        } else {
        	tr -> p -> r = tr -> r;
        	tr -> l -> p = tr -> p;
        }
        delete tr;
    } else {
    	if (tr -> p == NULL) {
    		tr = NULL;
    	}else if (tr -> p -> l == tr) {
    		tr -> p -> l = NULL;
    		delete tr;
    	} else {
    		tr -> p -> r = NULL;
    		delete tr;
    	}
    }
}*/

tree *deleter(tree* &tr, int k) {
	if (tr == NULL) {
        return tr;
    }
    if (k < tr -> x) {
        tr -> l = deleter(tr -> l, k);
    } else if (k > tr -> x) {
        tr -> r = deleter(tr -> r, k);
    } else if ((tr -> l != NULL) and (tr -> r != NULL)) {
    	tr -> x = minval(tr -> r) -> x;
    	tr -> r = deleter(tr -> r, tr -> x);
    } else if (tr -> l != NULL) {
    	tr = tr -> l;
    } else {
    	tr = tr -> r;
    }
    return tr;
}

int main() {
	string s;
	tree *root = NULL;
	while(cin >> s) {
		int a;
		cin >> a;
		if (s == "insert") {
			insert(root, a);
		} else if (s == "next") {
			tree *ans = next(root, a);
			if (ans == NULL) {
				cout << "none" << '\n';
			} else {
				cout << ans -> x << '\n';
			}
		} else if (s == "prev") {
			tree *ans = prev(root, a);
			if (ans == NULL) {
				cout << "none" << '\n';
			} else {
				cout << ans -> x << '\n';
			}
		} else if (s == "delete") {
			deleter(root, a);
		} else if (s == "exists") {
			if (exists(root, a) == -1) {
				cout << "false" << '\n';
			} else {
				cout << "true" << '\n';
			}
		}
	}
	return 0;
}

#include <iostream>

using namespace std;

struct RBtree {
    int x;
    bool red;
    RBtree *p, *r, *l;
};

RBtree* NULLtree;
RBtree* root = 0;
RBtree* branch = 0;
int son = 0;

void rotateR(RBtree* tr) {
    RBtree* r = tr -> l;
    if(tr != root) {
        RBtree* p = tr -> p;
        if(tr == p -> l) p -> l = r;
        else p -> r = r;
        r -> p = p;
    } else {
        r -> p = NULLtree;
        root = r;
    }
    tr -> l = r -> r;
    if(tr -> l != NULLtree) tr -> l -> p = tr;
    tr -> p = r;
    r -> r = tr;
}

void rotateL(RBtree* tr) {
    RBtree* r = tr -> r;
    if(tr != root) {
        RBtree* p = tr -> p;
        if(tr == p -> r) p -> r = r;
        else p -> l = r;
        r -> p = p;
    } else {
        r -> p = NULLtree;
        root = r;
    }
    tr -> r = r -> l;
    if(tr -> r != NULLtree) tr -> r -> p = tr;
    tr -> p = r;
    r -> l = tr;
}

void insert(RBtree* tr, RBtree* temp) {
    if(root == NULLtree) {
        root = temp;
        temp -> p = NULLtree;
        temp -> red = 0;
        return;
    }
    if(tr -> x == temp -> x) return;
    if(tr -> x > temp -> x) {
        if(tr -> l == NULLtree) {
            tr -> l = temp;
            temp -> p = tr;
            while (temp -> p -> red == 1) {
        		if (temp -> p -> p -> l == temp -> p) {
            		RBtree* grand = temp -> p -> p -> r;
            		if(grand -> red) {
                		grand -> red = 0;
                		temp -> p -> red = 0;
                		temp -> p -> p -> red = 1;
                		temp = temp -> p -> p;
            		} else {
                		if(temp -> p -> r == temp) {
                    		temp = temp -> p;
                    		rotateL(temp);
                		}
                		temp -> p -> red = 0;
                		temp -> p -> p -> red = 1;
                		rotateR(temp -> p -> p);
            		}
        		} else {
            		RBtree* grand = temp -> p -> p -> l;
            		if(grand -> red) {
                		grand -> red = 0;
                		temp -> p -> red = 0;
                		temp -> p -> p -> red = 1;
                		temp = temp -> p -> p;
            		} else {
                		if(temp -> p -> l == temp) {
                    		temp = temp -> p;
                    		rotateR(temp);
                		}
                		temp -> p -> red = 0;
                		temp -> p -> p -> red = 1;
                		rotateL(temp->p->p);
            		}
        		}
    		}
    		root -> red = 0;
        } else insert(tr -> l, temp);
    } else {
        if(tr -> r == NULLtree) {
            tr -> r = temp;
            temp -> p = tr;
            while (temp -> p -> red == 1) {
        		if (temp -> p -> p -> l == temp -> p) {
            		RBtree* grand = temp -> p -> p -> r;
            		if(grand -> red) {
                		grand -> red = 0;
                		temp -> p -> red = 0;
                		temp -> p -> p -> red = 1;
                		temp = temp -> p -> p;
            		} else {
                		if(temp -> p -> r == temp) {
                    		temp = temp -> p;
                    		rotateL(temp);
                		}
                		temp -> p -> red = 0;
                		temp -> p -> p -> red = 1;
                		rotateR(temp -> p -> p);
            		}
        		} else {
            		RBtree* grand = temp -> p -> p -> l;
            		if(grand -> red) {
                		grand -> red = 0;
                		temp -> p -> red = 0;
                		temp -> p -> p -> red = 1;
                		temp = temp -> p -> p;
            		} else {
                		if(temp -> p -> l == temp) {
                    		temp = temp -> p;
                    		rotateR(temp);
                		}
                		temp -> p -> red = 0;
                		temp -> p -> p -> red = 1;
                		rotateL(temp->p->p);
            		}
        		}
    		}
    		root -> red = 0;
        } else insert(tr -> r, temp);
    }
}

RBtree* search(RBtree* tr, int k) {
    if(tr == root) branch = root;
    if(tr == NULLtree || tr -> x == k) return tr;
    if(tr -> x > k) {
        if(tr -> l == NULLtree) {
            branch = tr;
            son = 0;
        }
        return search(tr -> l, k);
    } else {
        if(tr -> r == NULLtree) {
            branch = tr;
            son = 1;
        }
        return search(tr -> r, k);
    }
}

RBtree* minimum(RBtree* tr) {
    if(tr -> l == NULLtree) return tr;
    return minimum(tr -> l);
}

RBtree* maximum(RBtree* tr) {
    if(tr -> r == NULLtree) return tr;
    return maximum(tr -> r);
}

RBtree* next(RBtree* tr) {
    if((tr != NULLtree) and (tr -> r != NULLtree)) return minimum(tr -> r);
    RBtree* p;
    if(tr == NULLtree) p = branch;
    else p = tr -> p;
    while ((p != NULLtree) and (((tr == NULLtree) and (son)) or ((tr != NULLtree) and (tr == p -> r)))) {
        tr = p;
        p = p -> p;
    }
    return p;
}

RBtree* prev(RBtree* tr) {
    if((tr != NULLtree) and (tr -> l != NULLtree)) return maximum(tr -> l);
    RBtree* p;
    if(tr == NULLtree) p = branch;
    else p = tr -> p;
    while ((p != NULLtree) and (((tr == NULLtree) and !son) or ((tr != NULLtree) and (tr == p -> l)))) {
        tr = p;
        p = p -> p;
    }
    return p;
}

void remove(RBtree* tr) {
    if(tr == NULLtree) return;
    RBtree* temp;
    if((tr -> r == NULLtree) or (tr -> l == NULLtree)) temp = tr;
    else temp = next(tr);
    RBtree* tempson;
    if(temp -> l != NULLtree) tempson = temp -> l;
    else tempson = temp -> r;
    tempson -> p = temp -> p;
    if(temp -> p == NULLtree) root = tempson;
    else if(temp == temp -> p -> l) temp -> p -> l = tempson;
    else temp -> p -> r = tempson;
    if(temp != tr) tr -> x = temp -> x;
    if(temp -> red == 0) {
		while ((tempson != root) and !(tempson -> red)) {
	        if(tempson == tempson -> p -> r) {
	            RBtree* w = tempson -> p -> l;
	            if(w -> red) {
	                w -> red = 0;
	                tempson -> p -> red = 1;
	                rotateR(tempson -> p);
	                w = tempson -> p -> l;
	            }
	            if(!(w -> l -> red) and !(w -> r -> red)) {
	                w -> red = 1;
	                tempson = tempson -> p;
	            } else {
	                if(!(w -> l -> red)) {
	                    w -> r -> red = 0;
	                    w -> red = 1;
	                    rotateL(w);
	                    w = tempson -> p -> l;
	                }
	                w -> red = tempson -> p -> red;
	                tempson -> p -> red = 0;
	                w -> l -> red = 0;
	                rotateR(tempson -> p);
	                tempson = root;
	            }
	        } else {
	            RBtree* w = tempson -> p -> r;
	            if(w -> red) {
	                w -> red = 0;
	                tempson -> p -> red = 1;
	                rotateL(tempson -> p);
	                w = tempson -> p -> r;
	            }
	            if(!(w -> r -> red) and !(w -> l -> red)) {
	                w -> red = 1;
	                tempson = tempson -> p;
	            } else {
	                if(!(w -> r -> red)) {
	                    w -> l -> red = 0;
	                    w -> red = 1;
	                    rotateR(w);
	                    w = tempson -> p -> r;
	                }
	                w -> red = tempson -> p -> red;
	                tempson -> p -> red = 0;
	                w -> r -> red = 0;
	                rotateL(tempson -> p);
	                tempson = root;
	            }
	        }
	    }
	    tempson -> red = 0;
	}
    delete temp;
}

int main () {
    NULLtree = new RBtree;
    NULLtree->red = 0;
    NULLtree->p = NULLtree;
    root = NULLtree;
    string s;
    while (cin >> s) {
        int a;
        cin >> a;
        if(s == "insert") {
        	RBtree *temp = new RBtree;
        	temp -> l = temp -> r = temp -> p = NULLtree;
        	temp -> red = 1;
        	temp -> x = a;
            insert(root, temp);
        } else if(s == "exists") {
            if(search(root, a) != NULLtree) cout << "true" << '\n';
            else cout << "false" << '\n';
        } else if(s == "next") {
            RBtree* temp = next(search(root, a));
            if(temp == NULLtree) cout << "none" << '\n';
            else cout << temp -> x << '\n';
        } else if(s == "prev") {
            RBtree* temp = prev(search(root, a));
            if(temp == NULLtree) cout << "none" << '\n';
            else cout << temp -> x << '\n';
        } else if(s == "delete") {
            remove(search(root, a));
        }
    }
}


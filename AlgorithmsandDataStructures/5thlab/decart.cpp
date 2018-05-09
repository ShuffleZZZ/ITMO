struct tree {
	int x, y, i;
	tree *l = NULL, *r = NULL, *p = NULL;
};

tree *root = NULL;

pair <tree*, tree*> split (tree* &tr, int k) {
	if (tr == NULL) {
		return {tr, tr};
	}
	if (k < tr -> x) {
		pair <tree*, tree*> temp = split(tr -> l, k);
		tr -> l = temp.second;
		if (temp.second != NULL) temp.second -> p = tr;
		if (temp.first != NULL) temp.first -> p = NULL;
		return {temp.first, tr};
	} else {
		pair <tree*, tree*> temp = split(tr -> r, k);
		tr -> r = temp.first;
		if (temp.first != NULL) temp.first -> p = tr;
		if (temp.second != NULL) temp.second -> p = NULL;
		return {tr, temp.second};
	}
}

tree *merge (tree* t1, tree* t2) {
	if (t1 == NULL) return t2;
	if (t2 == NULL) return t1;
	if (t1 -> y < t2 -> y) {
		t1 -> r = merge(t1 -> r, t2);
		if (t1 -> r != NULL) t1 -> r -> p = t1;
		return t1;
	} else {
		t2 -> l = merge(t1, t2 -> l);
		if (t2 -> l != NULL) t2 -> l -> p = t2;
		return t2;
	}
}

tree *insert (tree* &tr, int k, int high, int i) {
	tree *temp = new tree;
	temp -> x = k;
	temp -> y = high;
	temp -> i = i;
	pair <tree*, tree*> cut = split(tr, k);
	return merge(merge(cut.first, temp), cut.second);
}

tree *remove (tree* &tr, int k) {
	pair <tree*, tree*> temp = split(tr, k);
	pair <tree*, tree*> cut = split(temp.first, k - 1);
	return merge(cut.first, temp.second);
}

tree *exists (tree* tr, int k) {
	if (tr -> x == k) return tr;
	if (tr -> x > k) {
	    if (tr -> l == NULL) return tr;
	    else return exists(tr -> l, k);
	} else {
	    if (tr -> r == NULL) return tr;
	    else return exists(tr -> r, k);
	}
}

tree *next (int k) {
	if (root == NULL) return root;
	tree *temp = exists(root, k);
	if (temp -> x <= k) {
	    if (temp -> r != NULL) {
	        temp = temp -> r;
	        while (temp -> l != NULL) temp = temp -> l;
	        return temp;
	    }
	    while ((temp -> p != NULL) and (temp == temp -> p -> r)) temp = temp -> p;
	    return temp -> p;
	}
	return temp;
}

tree *prev (int k) {
	if (root == NULL) return root;
	tree *temp = exists(root, k);
	if (temp -> x >= k) {
	    if (temp -> l != NULL) {
	        temp = temp -> l;
	        while (temp -> r != NULL) temp = temp -> r;
	        return temp;
	    }
	    while ((temp -> p != NULL) and (temp == temp -> p -> l)) temp = temp -> p;
	    return temp -> p;
	}
	return temp;
}

void print(tree* tr) {
	if (tr -> p != NULL) cout << tr -> p -> i << ' ';
	else cout << 0 << ' ';
	if (tr -> l != NULL) cout << tr -> l -> i << ' ';
	else cout << 0 << ' ';
	if (tr -> r != NULL) cout << tr -> r -> i << ' ';
	else cout << 0 << ' ';
	cout << tr -> i << '\n';
}

int main() {
	/*string s;
	while(cin >> s) {
		int a;
		cin >> a;
		if (s == "insert") {
			if (root == NULL) {
				tree *temp = new tree;
				temp -> x = a;
				root = temp;
			} else if (exists(root, a) -> x != a) root = insert(root, a);
		} else if (s == "next") {
			tree *ans = next(a);
			if (ans == NULL) cout << "none" << '\n';
			else cout << ans -> x << '\n';
		} else if (s == "prev") {
			tree *ans = prev(a);
			if (ans == NULL) cout << "none" << '\n';
			else cout << ans -> x << '\n';
		} else if (s == "delete") {
			if ((root != NULL) and (exists(root, a) -> x == a)) root = remove(root, a);
		} else if (s == "exists") {
			if ((root != NULL) and (exists(root, a) -> x == a)) cout << "true" << '\n';
			else cout << "false" << '\n';
		}
	}
	return 0;*/
}

#include <iostream>

using namespace std;

struct tree {
	int x, y = rand(), value, in, a, b;
};

tree tr[500000];
int resp[500000];

void update (int t) {
	if (t == -1) return;
	tr[t].x = 1;
	if (tr[t].value == 0) tr[t].in = 1;
	else tr[t].in = 0;
	if (tr[t].a != -1) {
		tr[t].x += tr[tr[t].a].x;
		tr[t].in += tr[tr[t].a].in;
	}
	if (tr[t].b != -1) {
		tr[t].x += tr[tr[t].b].x;
		tr[t].in += tr[tr[t].b].in;
	}
}

void split (int ind, int x, int &l, int &r) {
	if (ind == -1) {
		l = r = -1;
		return;
	}
	int temp = 1;
	if (tr[ind].a != -1) temp += tr[tr[ind].a].x;
	if (x == temp) {
		l = ind;
		r = tr[ind].b;
		tr[ind].b = -1;
	} else if (x < temp) {
		split(tr[ind].a, x, l, tr[ind].a);
		r = ind;
	} else {
		split(tr[ind].b,x - temp,tr[ind].b, r);
		l = ind;
	}
	update(ind);
}

int merge (int& l, int& r) {
	if(l == -1) return r;
	if(r == -1) return l;
	if (tr[l].y > tr[r].y) {
		tr[r].a = merge(l, tr[r].a);
		update(r);
		return r;
	} else {
		tr[l].b = merge(tr[l].b, r);
		update(l);
		return l;
	}
}

int add (int ind, int cur) {
	if ((ind == -1) or (tr[ind].y > tr[cur].y)) {
		split(ind, tr[cur].x, tr[cur].a, tr[cur].b);
		update(cur);
		return cur;
	}
	int temp = 1;
	if (tr[ind].a != -1) temp += tr[tr[ind].a].x;
	if (tr[cur].x < temp) tr[ind].a = add(tr[ind].a, cur);
	else {
		tr[cur].x -= temp;
		tr[ind].b = add(tr[ind].b, cur);
	}
	update(ind);
	return ind;
}

bool insert (int ind, int x, int value) {
	if (ind == -1) return false;
	int temp = 1;
	if (tr[ind].a != -1) temp = tr[tr[ind].a].x + 1;
	if (x == temp) 
		if (!tr[ind].value) {
			--tr[ind].in;
			tr[ind].value = value;
			return true;
		} else return false;
	else if (x < temp) 
		if(insert(tr[ind].a, x, value)) {
			update(ind);
			return true;
		} else return false;
	else
		if(insert( tr[ind].b, x - temp, value)) {
			update(ind);
			return true;
		} else return false;
}

int remove (int ind) {
	if (ind == -1) return ind;
	int a = 0, b = 0;
	if (tr[ind].a != -1) a = tr[tr[ind].a].in;
	if (tr[ind].b != -1) b = tr[tr[ind].b].in;
	if (a) tr[ind].a = remove(tr[ind].a);
	else if (!tr[ind].value) {
		int temp = merge(tr[ind].a, tr[ind].b);
		update(temp);
		return temp;
	} else if (b) tr[ind].b = remove(tr[ind].b);	
	update(ind);
	return ind;
}

void print (int ind, int &ans) {
	if ( ind == -1 ) return;
	print(tr[ind].a, ans);
	resp[ans++] = ind;
	print(tr[ind].b, ans);
}

int main() {
	int n, m;
	cin >> n >> m;
	int root = -1;
	int ind = 0;
	for (int i = 0; i < m + n + 1; ++i) {
		tr[ind].value = tr[ind].in = 0;
		tr[ind].a = tr[ind].b = -1;
		tr[ind].x = i + 1;
		root = add(root, ind);
		ind++;
	}
	for (int i = 0; i < n; ++i) {
		int l;
		cin >> l;
		if (!insert(root, l, i + 1)) {
			int t1mrg = -1, t2mrg = -1, t3mrg = -1;
			split(root, l, t1mrg, t2mrg);
			split(t1mrg, l - 1, t1mrg, t3mrg);
			t2mrg = remove(t2mrg);
			tr[ind].a = tr[ind].b = -1;
			tr[ind].in = 0;
			tr[ind].x = 1;
			tr[ind].value = i + 1;
			root = merge(t1mrg, ind);
			t3mrg = merge(t3mrg, t2mrg);
			root = merge(root, t3mrg);
			++ind;
		}
	}
	int ans = 0;
	print(root, ans);
	--ans;
	while ((ans >= 0) and (tr[resp[ans]].value == 0)) --ans;
	++ans;
	cout << ans << '\n';
	for (int i = 0; i < ans; ++i) {
		cout << tr[resp[i]].value << ' ';
	}
}

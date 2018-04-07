#include <vector>
#include <fstream>

using namespace std;

vector <pair<int, int> > a;
vector<int> color;
vector <char> lb;
vector <char> rb;

void push(int ind, int l, int r) {
	if ((l == r) or (color[ind] == -1)) {
		return;
	}
	int len = (l + r) / 2 - l + 1;
	a[2 * ind] = {color[ind], color[ind] * len};
	a[2 * ind + 1] = {color[ind], color[ind] * (r - l + 1 - len)};
	color[2 * ind] = color[2 * ind + 1] = color[ind];
	color[ind] = -1;
	lb[2 * ind] = rb[2 * ind] = lb[2 * ind + 1] = rb[2 * ind + 1] = color[ind];
}

void set(int ind, int l, int r, int fleft, int fright, int value) {
	if (fleft > fright){
		return;
	}
	if ((l == fleft) and (r == fright)) {
		color[ind] = value;
		a[ind] = {value, value * (r - l + 1)};
		lb[ind] = rb[ind] = value;
		return;
	}
	if (color[ind] == value){
		push(ind, l, r);
		a[ind] = {value, value * (r - l + 1)};
		lb[ind] = rb[ind] = value;
		return;
	}
	push(ind, l, r);
	int m = (l + r) / 2;
	set(2 * ind, l, m, fleft, min(m, fright), value);
	set(2 * ind + 1, m + 1, r, max(m + 1, fleft), fright, value);
	a[ind].first = a[2 * ind].first + a[2 * ind + 1].first;
	a[ind].second = a[2 * ind].second + a[2 * ind + 1].second;
	if ((rb[2 * ind] == 1) and (lb[2 * ind + 1] == 1)) {
		a[ind].first--;
	}
	lb[ind] = lb[2 * ind];
	rb[ind] = rb[2 * ind + 1];
}

int main() {
	ifstream in;
	in.open("painter.in");
	ofstream out;
	out.open("painter.out");
	int n, max = 1000010;
	in >> n;
	a.resize(4 * max + 1, {0, 0});
	color.resize(4 * max + 1, -1);
	lb.resize(4 * max + 1, 0);
	rb.resize(4 * max + 1, 0);
	for (int i = 0; i < n; i++) {
		char c; int x, l;
		in >> c >> x >> l;
		if (c == 'W'){
			set(1, 1, max, x + 500001, x + 500000 + l, 0);
		}else{
			set(1, 1, max, x + 500001, x + 500000 + l, 1);
		}
		out << a[1].first << ' ' << a[1].second << '\n';
	}
}

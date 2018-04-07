#include <fstream>

using namespace std;

ifstream in;
ofstream out;

struct matrix {
	int a;
	int b;
	int c;
	int d;
};

matrix buildmatrix(int a, int b, int c, int d) {
	matrix e;
	e.a = a;
	e.b = b;
	e.c = c;
	e.d = d;
	return e;
}

matrix multiply (matrix m,matrix s, int r) {
	matrix e;
	e.a = (m.a * s.a + m.b * s.c) % r;
	e.b = (m.a * s.b + m.b * s.d) % r;
	e.c = (m.c * s.a + m.d * s.c) % r;
	e.d = (m.c * s.b + m.d * s.d) % r;
	return e;
}

void print(matrix e) {
	out << e.a << ' ' << e.b << ' ' << '\n' << e.c << ' ' << e.d << '\n';
}

const matrix neutral = buildmatrix(1, 0, 0, 1);

struct tree {
	int l;
	int r;
	matrix value;
};

void update(tree tr[], int x, int r) {
	tr[x].value = multiply(tr[2 * x].value, tr[2 * x + 1].value, r);
}

void buildtree(matrix mt[], tree tr[], int x, int l, int r, int r1) {
	tr[x].l = l;
	tr[x].r = r;
	if (l + 1 == r) {
		tr[x].value = mt[l];
		return;
	}
	int m = (l + r) / 2;
	buildtree(mt, tr, 2 * x, l, m, r1);
	buildtree(mt, tr, 2 * x + 1, m, r, r1);
	update(tr, x, r1);
}

matrix get(tree tr[], int x, int l, int r, int r1) {
	if ((tr[x].l >= r) or (tr[x].r <= l)) {
		return neutral;
	}
	if ((tr[x].l >= l) and (tr[x].r <= r)) {
		return tr[x].value;
	}
	return multiply(get(tr, 2 * x, l, r, r1), get(tr, 2 * x + 1, l, r, r1), r1);
}

int main() {
	in.open("crypto.in");
	out.open("crypto.out");
	int n, r, m;
	in >> r >> n >> m;
	matrix mt[n];
	for (int i = 0; i < n; i++) {
		int a, b, c, d;
		in >> a >> b >> c >> d;
		mt[i] = buildmatrix(a, b, c, d);
	}
	tree tr[n * 4];
	buildtree(mt, tr, 1, 0, n, r);
	/*for (int i = 0; i < 4 * n; i++) {
		print(tr[i].value);
		out << ' ' << i << '\n';
	}*/
	for (int i = 0; i < m; i++) {
		int l, r1;
		in >> l >> r1;
		print(get(tr, 1, l - 1, r1, r));
	}
	in.close();
	out.close();
}
	

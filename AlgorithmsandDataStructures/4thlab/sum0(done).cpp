#include <fstream>

using namespace std;

long long a[10000000], b[20000000], c[20000000];

int main() {
	ios_base:: sync_with_stdio(false);
	ifstream in;
	in.open("sum0.in");
	ofstream out;
	out.open("sum0.out");
	int n, x, y, m, z, t;
	long long res = 0;
	in >> n >> x >> y;
	in >> a[0];
	if (n > 1) {
		a[1] =(x * a[0] + y) & ((1 << 16) - 1);
	}
	for (int i = 2; i < n; ++i) {
		a[i] =(x * a[i - 1] + y) & ((1 << 16) - 1);
		a[i - 1] += a[i - 2];
	}
	a[n - 1] += a[n - 2];
	in >> m >> z >> t;
	in >> b[0];
	c[0] = b[0] % n;
	for (int i = 1; i < 2 * m; ++i) {
		b[i] = (z * b[i - 1] + t) & ((1 << 30) - 1);
		c[i] = b[i] % n;
	}
	for (unsigned i = 0; i < m; ++i) {
		res += a[max(c[2 * i], c[2 * i + 1])];
		if (min(c[2 * i], c[2 * i + 1]))
		res -= a[min(c[2 * i], c[2 * i + 1]) - 1];
	}
	out << res;
	in.close();
	out.close();
}
		

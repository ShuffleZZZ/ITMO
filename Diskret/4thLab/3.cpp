#include <fstream>
int main () {
	std::ifstream in;
	in.open("lottery.in");
	std::ofstream out;
	out.open("lottery.out");
	int n, m;
	double cur, ans = 0;
	in >> n >> m;
	int a[m], b[m];
	for (int i = 0; i < m; ++i) {
		in >> a[i] >> b[i];
	}
	cur = 1.0 / a[0];
	for (int i = 1; i < m; ++i) {
		ans += cur * b[i - 1] * (a[i] - 1.0) / a[i];
		cur /= a[i];
	}
	ans += b[m - 1] * cur;
	out.precision(9);
	out.setf(std::ios::fixed);
	out.setf(std::ios::showpoint);
	out << n - ans;
	in.close();
	out.close();
}

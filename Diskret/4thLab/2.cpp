#include <fstream>

int main(){
	std::ifstream in;
	in.open("shooter.in");
	std::ofstream out;
	out.open("shooter.out");
	unsigned n, m, k;
	double ans = 0, that;
	in >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
	double p;
	in >> p;
	p = 1.0 - p;
	double res = 1;
	for (int j = 0; j < m; ++j) {
		res *= p;
	}
	ans += res;
	if (i == k - 1) {
		that=res;
	}
	}
	out.precision(14);
	out.setf(std::ios::fixed);
	out.setf(std::ios::showpoint);
	if(ans) {
		out << that / ans;
	} else {
		out << 0;
	}
	in.close();
	out.close();
}

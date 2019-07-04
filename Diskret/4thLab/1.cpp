#include <fstream>

int main() {
	std::ifstream in;
	in.open("exam.in");
	std::ofstream out;
	out.open("exam.out");
	int k, n;
	in >> k >> n;
	double a[k], b[k], res;
	for(int i = 0; i < k; ++i){
	int p, m;
	in >> p >> m;
	a[i] = 1.0 * p / n;
	b[i] = m / 100.0;
	res += a[i] * b[i];
	}
	out.precision(6);
	out.setf(std::ios::fixed);
	out.setf(std::ios::showpoint);
	out<<res;
	in.close();
	out.close();
}

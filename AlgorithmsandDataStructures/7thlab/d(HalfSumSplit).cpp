#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

bool sortx(pair <unsigned, unsigned> fi, pair <unsigned, unsigned> se) {
	return fi.first > se.first;
}

int main() {
	ifstream in;
	in.open("sequence.in");
	ofstream out;
	out.open("sequence.out");
	unsigned n;
	in >> n;
	pair <unsigned, unsigned> a[n];
	long sum = 0;
	for (unsigned i = 0; i < n; ++i) {
		in >> a[i].first;
		a[i].second = i + 1;
		sum += a[i].first;
	}
	if (sum & 1) {
		out << -1;
		return 0;
	}
	sort(a, a + n, sortx);
	vector<unsigned> left, right;
	long lsum = 0, rsum = 0;
	for (int i = 0; i < n; ++i) {
		if (lsum < rsum) {
			left.push_back(a[i].second);
			lsum += a[i].first;
		} else {
			right.push_back(a[i].second);
			rsum += a[i].first;
		}
	}
	if (lsum != rsum) {
		out << -1;
		return 0;
	}
	sort(left.begin(), left.end());
	out << left.size() << '\n';
	for (auto i : left) out << i << ' ';
	in.close();
	out.close();
}

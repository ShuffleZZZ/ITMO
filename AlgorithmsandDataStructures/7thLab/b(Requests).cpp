#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

bool sortx(pair <short, short> a, pair <short, short> b) {
	return a.second < b.second;
}

int main() {
    ifstream in;
	in.open("request.in");
	ofstream out;
	out.open("request.out");
	short n;
	in >> n;
	pair <short, short> a[n];
	for (short i = 0; i < n; ++i)
		in >> a[i].first >> a[i].second;
	sort(a, a + n, sortx);
	int res = 0, i = 0;
	while (i < n) {
		int cur = a[i++].second;
		while (a[i].first < cur) ++i;
		++res;
	}
	out << res;
	in.close();
	out.close();
}

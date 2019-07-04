#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct axwell {
	int dis;
	int dif;
	int ind;
};

bool sortx(axwell fi, axwell se) {
	if (fi.dif < 0) {
		if (se.dif < 0)
			return (fi.dif + fi.dis) > (se.dif + se.dis);
		return 0;
	}
	if (se.dif < 0) return 1;
	return fi.dis < se.dis;
}

int main() {
    ifstream in;
	in.open("apples.in");
	ofstream out;
	out.open("apples.out");
	int n, s;
	in >> n >> s;
	axwell a[n];
	for (int i = 0; i < n; ++i) {
		int b;
		in >> a[i].dis >> b;
		a[i].dif = b - a[i].dis;
		a[i].ind = i;
	}
	sort(a, a + n, sortx);
	vector <bool> came(n, 0);
	vector <int> res;
	int i = 0;
	int j = 0;
	while (res.size() < n) {
		while ((i < n) and (s - a[i].dis < 1)) ++i;
		if (i == n) break;
		if (came[a[i].ind]) {
			++i;
			continue;
		}
		came[a[i].ind] = 1;
		s += a[i].dif;
		res.push_back(a[i].ind);
		i = 0;
	}
	if (i == n) out << -1;
	else for (int j = 0; j < res.size(); ++j) 
		out << res[j] + 1 << ' ';
	in.close();
	out.close();
}

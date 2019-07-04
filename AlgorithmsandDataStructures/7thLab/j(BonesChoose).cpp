#include <fstream>

using namespace std;

int main() {
    ifstream in;
	in.open("jurassic.in");
	ofstream out;
	out.open("jurassic.out");
	int n;
	in >> n;
	int a[n] = {};
	for (int i = 0; i < n; ++i) {
		string s;
		in >> s;
		for (int j = 0; j < s.size(); ++j)
			a[i] += 1 << (s[j] - 'A');
	}
	int max = 0;
	int ans = 0;
	for (int i = 1; i < (1 << n); ++i) {
		int res = 0;
		int amount = 0;
		for (int j = 0; j < n; ++j)
			if ((1 << j) & i) {
				res ^= a[j];
				++amount;
			}
		if ((res == 0) and (amount > max)) {
			max = amount;
			ans = i;
		}
	}
	out << max << '\n';
	if (max == 0) return 0;
	for (int i = 0; i < n; ++i)
		if ((1 << i) & ans) out << i + 1 << ' ';
	in.close();
	out.close();
}

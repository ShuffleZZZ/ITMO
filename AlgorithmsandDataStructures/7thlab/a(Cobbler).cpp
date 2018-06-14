#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ifstream in;
	in.open("cobbler.in");
	ofstream out;
	out.open("cobbler.out");
	short k, n;
	in >> k >> n;
	short a[n];
	for (short i = 0; i < n; ++i)
		in >> a[i];
	sort(a, a + n);
	short sum = 0;
	short res = 0;
	while (sum <= k) sum += a[res], ++res;
	out << res - 1;
	in.close();
	out.close();
}
		

#include <fstream>
#include <vector>
//#include <cstdlib>

using namespace std;

int main() {
	ifstream in;
	in.open("problem1.in");
	ofstream out;
	out.open("problem1.out");
	string s;
	in >> s;
	int n, m, k;
	in >> n >> m >> k;
	vector <bool> term(100100, 0);
	vector < vector<int> > dka(n, vector<int> (26, -1));
	for (int i = 0; i < k; ++i) {
		int trm;
		in >> trm;
		term[trm - 1] = 1;
	}
	for (int i = 0; i < m; ++i) {
		int a, b;
		char c;
		in >> a >> b >> c;
		dka[a - 1][c - 'a'] = b - 1;
	}
	int ind = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (dka[ind][s[i] - 'a'] == -1) {
			out << "Rejects";
			return 0;
		}
		ind = dka[ind][s[i] - 'a'];
	}
	if (term[ind]) {
		out << "Accepts";
	} else {
		out << "Rejects";
	}
	in.close();
	out.close();
}

#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream in;
	in.open("problem2.in");
	ofstream out;
	out.open("problem2.out");
	string s;
	in >> s;
	int n, m, k;
	in >> n >> m >> k;
	vector <bool> term(100100, 0);
	vector < vector< vector<int> > > nka(n, vector< vector <int> > (26, vector <int>()));
	for (int i = 0; i < k; ++i) {
		int trm;
		in >> trm;
		term[trm - 1] = 1;
	}
	for (int i = 0; i < m; ++i) {
		int a, b;
		char c;
		in >> a >> b >> c;
		nka[a - 1][c - 'a'].push_back(b - 1);
	}
	vector <bool> ind(2 * n, 0);
	ind[0] = 1;
	int cur = 0;
	for (int i = 0; i < s.size(); ++i) {
		vector <bool> next(2 * n, 0);
		for (int j = 0; j < cur + 1; ++j) {
			if (ind[j] == 0) continue;
			for (int k = 0; k < nka[j][s[i] - 'a'].size(); ++k) {
				next[nka[j][s[i] - 'a'][k]] = 1;
				if (cur < nka[j][s[i] - 'a'][k]) cur = nka[j][s[i] - 'a'][k];
			}
		}
		ind = next;
	}
	for (int i = 0; i < n; ++i) {
		if ((ind[i]) and (term[i])) {
			out << "Accepts";
			return 0;
		}
	}
	out << "Rejects";
	in.close();
	out.close();
}

#include <fstream>
#include <queue>
#include <vector>

using namespace std;

int main() {
	ifstream in;
	in.open("equivalence.in");
	ofstream out;
	out.open("equivalence.out");
	int n, m, k;
	in >> n >> m >> k;
	vector <bool> term, came(n + 1, 0);
	vector < vector <int> > dka(n + 1, vector <int>(26, 0));
	term = came;
	for (int i = 0; i < k; ++i) {
		int trm;
		in >> trm;
		term[trm] = 1;
	}
	for (int i = 0; i < m; ++i) {
		int a, b;
		char c;
		in >> a >> b >> c;
		dka[a][c - 'a'] = b;
	}
	int n2, m2, k2;
	in >> n2 >> m2 >> k2;
	vector <bool> term2, came2(n2 + 1, 0);	
	vector < vector <int> > dka2(n2 + 1, vector <int>(26, 0));
	term2 = came2;
	for (int i = 0; i < k2; ++i) {
		int trm;
		in >> trm;
		term2[trm] = 1;
	}
	for (int i = 0; i < m2; ++i) {
		int a, b;
		char c;
		in >> a >> b >> c;
		dka2[a][c - 'a'] = b;
	}
	queue< pair<int, int> > q;
	q.push(make_pair(1, 1));
	came[1] = came2[1] = 1;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		if (term[cur.first] != term2[cur.second]) {
			out << "NO";
			return 0;
		}
		for (int i = 0; i < 26; ++i) {
			int temp1 = dka[cur.first][i];
			int temp2 = dka2[cur.second][i];
			if ((!came[temp1] || !came2[temp2]) and (temp1 != 0 || temp2 != 0)) {
					q.push(make_pair(temp1, temp2));
					if (temp1 != 0) came[temp1] = 1;
					if (temp2 != 0) came2[temp2] = 1;
			}
		}
	}
	out << "YES";
	in.close();
	out.close();
}

#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector < vector <int> > dka;
vector <int> from[1010][26];
vector <bool> came;

void dfs(int ind) {
	came[ind] = 1;
	for (int i = 0; i < 26; ++i)
		if (!came[dka[ind][i]])
			dfs(dka[ind][i]);
}

int main() {
	ifstream in;
	in.open("minimization.in");
	ofstream out;
	out.open("minimization.out");
	int n, m, k;
	in >> n >> m >> k;
	vector <bool> term (1010, 0);
	for (int i = 0; i < k; ++i) {
		int trm;
		in >> trm;
		term[trm] = 1;
	}
	dka.resize(1010, vector <int> (26, 0));
	for (int i = 0; i < m; ++i) {
		int a, b;
		char c;
		in >> a >> b >> c;
		dka[a][c - 'a'] = b;
	}
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j < 26; ++j)
			from[dka[i][j]][j].push_back(i);
	came.resize(1010, 0);
	dfs(1);
	queue< pair<int, int> > search;
	vector < vector<bool> > checked (1010, vector <bool> (1010, 0));
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			if ((!checked[i][j]) and (term[i] != term[j])) {
				checked[i][j] = 1;
				checked[j][i] = 1;
				search.push({i, j});
			}
		}
	}
	while (!search.empty()) {
		pair <int, int> temp = search.front();
		search.pop();
		for (int c = 0; c < 26; ++c)
			for (int i = 0; i < from[temp.first][c].size(); ++i)
                for (int j = 0; j < from[temp.second][c].size(); ++j)
                    if (!checked[from[temp.first][c][i]][from[temp.second][c][j]]) {
                        checked[from[temp.first][c][i]][from[temp.second][c][j]] = 1;
                        checked[from[temp.second][c][j]][from[temp.first][c][i]] = 1;
                        search.push({from[temp.first][c][i], from[temp.second][c][j]});
                    }
	}
	vector <int> amount(1010, -1);
	for (int i = 0; i <= n; ++i) if (!checked[0][i]) amount[i] = 0;
	int n2 = 0, k2 = 0, m2 = 0;
	for (int i = 1; i <= n; ++i) {
		if (!came[i]) continue;
		if (amount[i] == -1) {
            ++n2;
            amount[i] = n2;
            for (int j = i + 1; j <= n; ++j) if (!checked[i][j]) amount[j] = n2;
        }
	}
	vector < vector <int> > dka2 (1010, vector <int> (26, 0));
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j < 26; ++j)
			if ((amount[i] > 0) and (amount[dka[i][j]] > 0) and (dka2[amount[i]][j] == 0)) {
				dka2[amount[i]][j] = amount[dka[i][j]];
				++m2;
			}
	vector <bool> term2 (1010, 0);
	for (int i = 0; i <= n; ++i) {
		if ((term[i]) and (amount[i] != -1) and (!term2[amount[i]])) {
			term2[amount[i]] = 1;
			++k2;
		}
	}
	if (term2[0]) --k2;
	out << n2 << ' ' << m2 << ' ' << k2 << '\n';
	for (int i = 1; i <= n2; ++i) if (term2[i]) out << i << ' ';
	out << '\n';
	for (int i = 1; i <= n2; ++i)
		for (int j = 0; j < 26; ++j)
			if (dka2[i][j] != 0) out << i << ' ' << dka2[i][j] << ' ' << (char)(j + 97) << '\n';
	in.close();
	out.close();
}

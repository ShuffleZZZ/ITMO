#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const long long neutral = 1e9 + 7;

vector<vector<int>> dka, from;
vector<bool> minim;
vector<int> color;
vector<int> order;

void dfs (int v) {
    minim[v] = 1;
    for (int i = 0; i < from[v].size(); ++i) {
        if (!minim[from[v][i]]) dfs(from[v][i]);
    }
}

bool check(int v) {
	color[v] = 2;
	for (int i = 0; i < dka[v].size(); ++i) {
		int temp = dka[v][i];
		if (color[temp] == 0) {
			if (check(temp)) return 1;
		} else if ((minim[temp]) and (color[temp] == 2)) return 1;
	}
	color[v] = 1;
	order.push_back(v);
	return 0;
}

int main() {
	ifstream in;
	in.open("problem3.in");
	ofstream out;
	out.open("problem3.out");
    int n, m, k;
    in >> n >> m >> k;
	vector <int> term;
    for (int i = 0; i < k; ++i) {
    	int trm;
        in >> trm;
        term.push_back(trm - 1);
    }
    dka.resize(n);
    from.resize(n);
    color.resize(n, 0);
    minim.resize(n, 0);
    for (int i = 0; i < m; ++i) {
    	int a, b;
    	char ch;
        in >> a >> b >> ch;
        dka[a - 1].push_back(b - 1);
        from[b - 1].push_back(a - 1);
    }
    for (int i = 0; i < k; ++i) dfs(term[i]);
    if (check(0)) {
        out << -1;
        in.close();
    	out.close();
        return 0;
    }
    vector<int> quantity(n, 0);
    quantity[0] = 1;
    int res = 0;
    reverse(order.begin(), order.end());
    for (int i = 0; i < order.size(); ++i) {
        int temp = order[i];
        for (int j = 0; j < from[temp].size(); ++j) quantity[temp] = (quantity[temp] + quantity[from[temp][j]]) % neutral;
    }
    for (int i = 0; i < term.size(); ++i) res = (res + quantity[term[i]]) % neutral;
    out << res;
    in.close();
    out.close();
}

#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <map>

using namespace std;

vector < vector <int> > dka;
vector <int> from[50100][26];
vector <bool> came;

void dfs(int ind) {
    came[ind] = 1;
    for (int i = 0; i < 26; ++i)
        if (!came[dka[ind][i]])
            dfs(dka[ind][i]);
}

int main() {
    ifstream in;
	in.open("fastminimization.in");
	ofstream out;
	out.open("fastminimization.out");
	int n, m, k;
	in >> n >> m >> k; 
    vector <bool> term (50100, 0);
    for (int i = 0; i < k; ++i) {
        int trm;
    	in >> trm;
        term[trm] = 1;
    }
    dka.resize(50100, vector <int> (26, 0));
    for (int i = 0; i < m; ++i) {
        int a, b;
        char c;
        in >> a >> b >> c;
        dka[a][c - 'a'] = b;
    }
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < 26; ++j)
            from[dka[i][j]][j].push_back(i);
    came.resize(50100, 0);
    dfs(1);
    int classs[50100];
	unordered_set <int> t;
	unordered_set <int> nt;
    for (int i = 0; i <= n; ++i)
        if (term[i]) {
            t.insert(i);
            classs[i] = 0;
        } else {
            nt.insert(i);
            classs[i] = 1;
        }
    vector < unordered_set <int> > p;
    vector < unordered_set <int> > sss;
    p.push_back(t);
    p.push_back(nt);
    sss.push_back(t);
    sss.push_back(nt);
    queue< pair <int, int> > search;
    for (int i = 0; i < 26; ++i) {
        search.push({0, i});
        search.push({1, i});
    }
    while (!search.empty()) {
        pair <int, int> temp = search.front();
        search.pop();
        map <int, vector <int> > inv;
        for (int search: sss[temp.first])
            for (int r: from[search][temp.second])
                inv[classs[r]].push_back(r);
        for (pair<int, vector<int>> x: inv) if (x.second.size() > 0) {
            if (inv[x.first].size() < p[x.first].size()) {
                unordered_set <int> tmp;
                p.push_back(tmp);
                for (int r: inv[x.first]) {
                    p[x.first].erase(r);
                    p[p.size() - 1].insert(r);
                }
                if (p[p.size() - 1].size() > p[x.first].size())
                    swap(p[x.first], p[p.size() - 1]);
                for (int r: p[p.size() - 1])
                    classs[r] = p.size() - 1;
                sss.push_back(p[p.size() - 1]);
                for (int i = 0; i < 26; i++)
                    search.push({sss.size() - 1, i});
            }
        }
    }
    int n2 = 0, m2 = 0, k2 = 0;
    vector <int> amount (50100, -1);
    for (const unordered_set<int>& i: p) {
        if (i.find(0) != i.end())
            for (int j: i) amount[j] = 0;
        if ((i.find(1) != i.end()) and (amount[1] == -1)) {
            ++n2;
            for (int j : i) amount[j] = 1;
        }
    }
    for (const unordered_set<int>& x: p) {
        int i = *x.begin();
        if (!came[i]) continue;
        if (amount[i] == -1) {
	        ++n2;
	        amount[i] = n2;
	        for (int j: x) amount[j] = n2;
	    }
    }
    vector < vector <int> > dka2 (50100, vector <int> (26, 0));
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < 26; ++j)
            if ((amount[i] > 0) and (amount[dka[i][j]] > 0) and (dka2[amount[i]][j] == 0)) {
                dka2[amount[i]][j] = amount[dka[i][j]];
                ++m2;
            }
    vector <bool> term2 (50100, 0);
    for (int i = 0; i <= n; ++i)
        if (term[i] and (amount[i] != -1) and (!term2[amount[i]])) {
            term2[amount[i]] = 1;
            ++k2;
        }
    if (term2[0]) --k2;
    out << n2 << ' ' << m2 << ' ' << k2 << '\n';
    for (int i = 1; i <= n/*2*/; ++i) if (term2[i]) out << i << ' ';
    out << '\n';
    for (int i = 1; i <= n/*2*/; ++i)
        for (int j = 0; j < 26; ++j)
            if (dka2[i][j] != 0) out << i << ' ' << dka2[i][j] << ' ' << (char)(j + 97) << '\n';
    in.close();
    out.close();
}

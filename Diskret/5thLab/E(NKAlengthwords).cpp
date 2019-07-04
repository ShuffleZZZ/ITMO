#include <fstream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int neutral = 1e9 + 7;
long long quantity[2000][10000];
vector <int> dka[10000][30], from[10000][30];
bool term[200];

int main() {
    ifstream in;
	in.open("problem5.in");
	ofstream out;
	out.open("problem5.out");
    int n, m, k, l;
    in >> n >> m >> k >> l;
    for (int i = 0; i < k; ++i) {
        int trm;
        in >> trm;
        term[trm] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        char c;
        in >> a >> b >> c;
        dka[a][c - 'a'].push_back(b);
    }
    queue <pair <vector <int>, int> > search;
    map <vector <int>, int> checker;
    vector <int> start, KAterm;
    int amount = 1;
    start.push_back(amount);
    search.push({start, amount});
    checker.insert({start, amount});
    if (term[amount]) {KAterm.push_back(amount);}
    while (!search.empty()) {
        vector <int> temp1 = search.front().first;
        int temp2 = search.front().second;
        search.pop();
        for (int i = 0; i < 26; ++i) {
            vector <int> cur;
            bool came[2000] = {};
            bool cameterm = 0;
            for (int j = 0; j < temp1.size(); ++j) {
                for (int k = 0; k < dka[temp1[j]][i].size(); ++k) {
                    if (term[dka[temp1[j]][i][k]]) {cameterm = 1;}
                    if (!came[dka[temp1[j]][i][k]]) {
                        cur.push_back(dka[temp1[j]][i][k]);
                        came[dka[temp1[j]][i][k]] = 1;
                    }
                }
            }
            if (cur.empty()) continue;
            if (checker.find(cur) == checker.end()) {
            	++amount;
                search.push({cur, amount});
                checker.insert({cur, amount});
                from[amount][i].push_back(temp2);
                if (cameterm) {KAterm.push_back(amount);}
            } else {from[checker.find(cur) -> second][i].push_back(temp2);}
        }
    }
    quantity[0][1] = 1;
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < amount; ++j) {
            for (int q = 0; q < 26; ++q) {
                vector <int> temp = from[j + 1][q];
                for (int x = 0; x < temp.size(); ++x) {
                    quantity[i + 1][j + 1] += quantity[i][temp[x]];
                    quantity[i + 1][j + 1] %= neutral;
                }
            }
        }
    }
    long long res = 0;
    for (int i = 0; i < KAterm.size(); ++i) {
        res += quantity[l][KAterm[i]];
        res %= neutral;
    }
    out << res;
    in.close();
    out.close();
}

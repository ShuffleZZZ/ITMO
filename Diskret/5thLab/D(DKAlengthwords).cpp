#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int neutral = 1e9 + 7;

int main() {
   	ifstream in;
	in.open("problem4.in");
	ofstream out;
	out.open("problem4.out");
    int n, m, k, l;
    in >> n >> m >> k >> l;
    vector <bool> term(n, 0);
    vector < vector <int> > dka = vector < vector <int> > (n, vector <int> (26, -1)), from(n);
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
        from[b - 1].push_back(a - 1);
    }   
    vector < vector <int> > quantity(n, vector <int> (l + 1, 0)), came;
    came = quantity;
    queue < pair <int, int> > search;
    for (int i = 0; i < n; i++) {
        if (term[i]) {
            search.push({i, 0});
            quantity[i][0] = 1;
        }
    }
    while(!search.empty()) {
        int temp1 = search.front().first;
        int temp2 = search.front().second;
        search.pop();
        if ((came[temp1][temp2]) or (temp2 == l)) continue;
        came[temp1][temp2] = 1;
        for (int i = 0; i < from[temp1].size(); ++i) {
            int cur = from[temp1][i];
            quantity[cur][temp2 + 1] = (quantity[cur][temp2 + 1] + quantity[temp1][temp2]) % neutral;
            search.push({cur, temp2 + 1});
        }
    }
    out << quantity[0][l];
    in.close();
    out.close();
}

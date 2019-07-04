#include <fstream>
#include <vector>

using namespace std;

vector <bool> came, term, came2, term2;
vector < vector <int> > dka, dka2;

bool check(int ind1, int ind2) {
    came[ind1] = 1;
    came2[ind2] = 1;
    if (term[ind1] != term2[ind2]) return 0;
    for (int i = 0; i < 26; ++i)
        if ((dka[ind1][i] != -1) and (dka2[ind2][i] != -1)) {
            if ((!came[dka[ind1][i]]) and (!came2[dka2[ind2][i]])) check(dka[ind1][i], dka2[ind2][i]);
            else if ((!came[dka[ind1][i]]) or (!came2[dka2[ind2][i]])) return 0;
        } else if ((dka[ind1][i] != -1) or (dka2[ind2][i] != -1)) return 0;
    return 1;
}

int main() {
    ifstream in;
	in.open("isomorphism.in");
	ofstream out;
	out.open("isomorphism.out");
    int n, m, k;
    in >> n >> m >> k;
    came.resize(n + 1, 0);
    dka.resize(n + 1, vector <int> (26, -1));
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
    if ((n != n2) or (m != m2) or (k != k2)) {
        out << "NO";
        in.close();
        out.close();
        return 0;
    }
    came2.resize(n2 + 1, 0);
    dka2.resize(n2 + 1, vector <int> (26, -1));
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
    if (check(1, 1)) out << "YES";
    else out << "NO";
    in.close();
    out.close();
}

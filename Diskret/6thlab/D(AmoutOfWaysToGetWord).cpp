#include <fstream>
#include <vector>

using namespace std;

const long neutral = 1e9 + 7;
unsigned long long d[26][100][100] = {};

int main() {
    ifstream in;
	in.open("nfc.in");
	ofstream out;
	out.open("nfc.out");
    short n;
    char S;
    in >> n >> S;
    vector < vector <string> > ks(26, vector<string>());
    for (short i = 0; i < n; ++i) {
    	char cur;
		string tr, next;
    	in >> cur >> tr >> next;
        ks[cur - 'A'].push_back(next);
    }
    string w;
    in >> w;
    for (short i = 0; i < 26; ++i)
        for (short j = 0; j < ks[i].size(); ++j)
            if (ks[i][j].size() == 1)
                for (short m = 0; m < w.size(); ++m)
                    if (w[m] == ks[i][j][0]) ++d[i][m][m];
    for (short i = 1; i < w.size(); ++i)
        for (short j = 0; j < 26; ++j)
            for (short k = 0; k < w.size() - i; ++k)
                for (short l = 0; l < ks[j].size(); ++l)
                    if (ks[j][l].size() == 2)
                        for (short m = k; m < k + i; ++m)
                            d[j][k][k + i] = (d[j][k][k + i]
							+ d[ks[j][l][0] - 'A'][k][m]
							* d[ks[j][l][1] - 'A'][m + 1][k + i])
							 % neutral;
    out << d[S - 'A'][0][w.size() - 1];
    in.close();
    out.close();
}

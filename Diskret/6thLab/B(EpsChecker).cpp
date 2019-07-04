#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream in;
	in.open("epsilon.in");
	ofstream out;
	out.open("epsilon.out");
    short n;
    char S;
    in >> n >> S;
    vector < pair <char, string> > ks;
    for (short i = 0; i < n; ++i) {
    	char cur;
        string tr, next;
        in >> cur >> tr;
        getline(in, next);
        if (!next.empty()) next.erase(next.begin());
        ks.push_back({cur, next});
    }
    bool eps[500] = {};
    bool eps_gen[500] = {};
	vector <char> res;
    bool togo = 1;
    while (togo) {
        bool checker = 0;
        for (int i = 0; i < n; ++i) {
            if (eps[i]) continue;
            bool next = 1;
            for (short j = 0; j < ks[i].second.size(); ++j)
                if (!eps_gen[ks[i].second[j]]) {
                    next = 0;
                    break;
                }
            if (!next) continue;
            res.push_back(ks[i].first);
            eps_gen[ks[i].first] = 1;
            eps[i] = 1;
            checker = 1;
        }
        togo = checker;
    }
    sort(res.begin(), res.end());
    for (short i = 0; i < res.size(); ++i) out << res[i] << ' ';
    in.close();
    out.close();
}

#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in;
	in.open("automaton.in");
	ofstream out;
	out.open("automaton.out");
    short n;
	char S;
    in >> n >> S;
    vector < vector < vector <int> > > ks (30, vector < vector <int> > (26, vector <int>()));
    for (short i = 0; i < n; ++i) {
    	char cur;
		string tr, next;
    	in >> cur >> tr >> next;
    	if (next.size() == 1) ks[cur - 'A'][next[0] - 'a'].push_back(26);
    	else ks[cur - 'A'][next[0] - 'a'].push_back(next[1] - 'A');
    }
    int m;
    in >> m;
    for (short i = 0; i < m; ++i) {
    	string w;
    	in >> w;
    	vector < vector <int> > res;
    	res.push_back(vector <int> (30, 0));
    	res[0][S - 'A'] = 1;
    	for (int j = 0; j < w.size(); ++j) {
    		res.push_back(vector <int> (30, 0));
    		for (short x = 0; x < 30; ++x)
    			if (res[j][x])
    				for (short y = 0; y < ks[x][w[j] - 'a'].size(); ++y) 
    					res[j + 1][ks[x][w[j] - 'a'][y]] = 1;
    	}
    	if (res[w.size()][26]) out << "yes" << '\n';
    	else out << "no" << '\n';
    }
    in.close();
    out.close();
}

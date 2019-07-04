#include <fstream>
#include <unordered_set>

using namespace std;

bool letter(char c, bool state) {
	if ((state) and (c >= 'A') and (c <= 'Z')) return 1;
	if ((!state) and (c >= 'a') and (c <= 'z')) return 1;
	return 0;
}

int main() {
	ifstream in;
	in.open("useless.in");
	ofstream out;
	out.open("useless.out");
	int n;
	char S;
	in >> n >> S;
	bool unterm[26] = {};
	unterm[S - 'A'] = 1;
	unordered_set<string> ks[26];
	for (int i = 0; i < n; ++i) {
		char cur;
        string tr, next;
		in >> cur >> tr;
        getline(in, next);
        if (!next.empty()) next.erase(next.begin());
		ks[cur - 'A'].insert(next);
		unterm[cur - 'A'] = 1;
		for (int j = 0; j < next.size(); ++j)
        	if (letter(next[j], 1)) 
				unterm[next[j] - 'A'] = 1;
	}
	bool gen[50] = {};
	for (int i = 0; i < 26; ++i)
		for (string const &str : ks[i]) {
			bool next = 1;
			for (int j = 0; j < str.size(); ++j)
				next &= letter(str[j], 0);
			if (next) {
				gen[i] = 1;
				break;
			}
		}
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < 26; ++j)
			if (!gen[j])
				for (string const &str : ks[j]) {
					bool next = 1;
					for (int j = 0; j < str.size(); ++j)
						next &= (letter(str[j], 0) or gen[str[j] - 'A']);
					if (next) {
						gen[j] = 1;
						break;
					}
				}
	for (int i = 0; i < 26; ++i)
		if (!gen[i]) ks[i].clear();
		else for (auto it = ks[i].begin(); it != ks[i].end();) {
			bool next = 1;
			for (char c : *it)
				next &= (letter(c, 0) or gen[c - 'A']);
			if (!next)
				it = ks[i].erase(it);
			else ++it;
		}
	bool reached[50] = {};
	reached[S - 'A'] = 1;
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < 26; ++j)
			if (reached[j])
				for (string const &str : ks[j])
					for (int j = 0; j < str.size(); ++j)
						if (!letter(str[j], 0))
							reached[str[j] - 'A'] = 1;
	for (int i = 0; i < 26; ++i)
		if (unterm[i] and (!gen[i] or !reached[i]))
			out << (char) (i + 'A') << ' ';
}

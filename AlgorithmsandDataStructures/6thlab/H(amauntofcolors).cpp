#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector <int> num, amount;
vector < vector <int> > sons;
vector < set <int> > bucket;

void dfs(int ind) {
  bucket[ind].insert(num[ind]);
  for(int i = 0; i < sons[ind].size(); ++i) {
    dfs(sons[ind][i]);
    if (bucket[ind].size() < bucket[sons[ind][i]].size()) bucket[ind].swap(bucket[sons[ind][i]]);
  	for(auto j : bucket[sons[ind][i]]) bucket[ind].insert(j);
  	bucket[sons[ind][i]].clear();
  }
  amount[ind] = bucket[ind].size();
}

int main() {
	int n;
	cin >> n;
	sons.resize(n + 1);
	num.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		int p, c;
  		cin >> p >> c;
  		sons[p].push_back(i);
  		num[i] = c;
	}
	amount.resize(n + 1);
	bucket.resize(n + 1);
	dfs(0);
	for (int i = 1; i <= n; ++i) cout << amount[i] << ' ';
}

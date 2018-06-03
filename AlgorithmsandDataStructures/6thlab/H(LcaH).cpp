#include <iostream>
#include <vector>
  
using namespace std;
 
vector < vector <int> > dp, sons;
vector <int> p, lvl, num, last, amount;
vector <bool> came;
int pow = 0;
  
void log(int n) {while ((1 << pow) < n) ++pow;}
 
int lca(int x, int y) {
    if (lvl[x] < lvl[y]) return lca(y, x);
    int dif = lvl[x] - lvl[y];
    int lift = 0;
    while (dif > 0) {
        if (dif & 1) x = dp[x][lift];
        dif >>= 1;
        ++lift;
    }
    for (int i = pow; i >= 0; --i) {
        if (dp[x][i] != dp[y][i]) {
            x = dp[x][i];
            y = dp[y][i];
        }
    }
    if (x != y) return p[x];
    else return x;
}
  
void levels(int ind) {
    lvl[ind] = lvl[p[ind]] + 1;
    for (auto i : sons[ind]) levels(i);
}
 
void count(int ind) {
    came[ind] = 1;
    for (auto i : sons[ind]) {
        if (!came[i]) count(i);
        amount[ind] += amount[i];
    }
    if (last[num[ind]] != -1) --amount[lca(ind, last[num[ind]])];
    last[num[ind]] = ind;
}
  
int main() {
    int n;
    cin >> n;
    p.resize(n + 1);
    num = lvl = p;
    sons.resize(n + 1);
    log(n);
    dp.resize(n + 1, vector <int> (pow + 1));
    dp[0][0] = p[0] = 0;
    lvl[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int pr, c;
        cin >> pr >> c;
        dp[i][0] = p[i] = pr;
        if (i < pow + 1) dp[0][i] = 0;
        num[i] = c;
        sons[pr].push_back(i);
    }
    levels(0);
    for (int j = 1; j <= pow; ++j)
    	for (int i = 1; i <= n; ++i)
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
    amount.resize(n + 1, 1);
    came.resize(n + 1, 0);
    last.resize(n + 1, -1);
    count(0);
    for (int i = 1; i <= n; ++i) cout << amount[i] << ' ';
}

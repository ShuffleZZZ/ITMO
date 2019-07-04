#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct diamond {
	int ind;
	long long w, v;
	bool operator < (const diamond& temp) const {
		return w < temp.w;
	}
};

diamond a[210000], b[210000];
diamond t;
int dp[210000][22];
long long cur;
int leftb, rightb;

int main() {
    ifstream in;
	in.open("dowry.in");
	ofstream out;
	out.open("dowry.out");
	int n;
	long long l, r;
    in >> n >> l >> r;
    long long w[n + 1], v[n + 1];
    for (int i = 0; i < n; ++i) in >> w[i] >> v[i];
    int asize = n >> 1, bsize = n - asize;
    int ashift = 1 << asize, bshift = 1 << bsize;
    for (int i = 0; i < ashift; ++i) {
    	long long wi = 0, vi = 0;
    	for (int j = 0; j < asize; ++j) 
			if (i & (1 << j)) {
	    		wi += w[j];
	    		vi += v[j];
	    	}
    	a[i].ind = i;
    	a[i].w = wi;
    	a[i].v = vi;
    }
    for (int i = 0; i < bshift; ++i) {
    	long long wi = 0, vi = 0;
    	for (int j = 0; j < bsize; ++j) 
			if (i & (1 << j)) {
	    		wi += w[j + asize];
	    		vi += v[j + asize];
    		}
    	b[i].ind = i;
    	b[i].w = wi;
    	b[i].v = vi;
    }
    sort(a, a + ashift);
    sort(b, b + bshift);
    for (int i = bshift - 1; i > -1; --i) {
    	dp[i][0] = i;
    	for (int j = 0; j < 16; ++j) {
    		if (b[dp[i][j]].v >= b[dp[i + (1 << j)][j]].v)
    			dp[i][j + 1] = dp[i][j];
    		else dp[i][j + 1] = dp[i + (1 << j)][j];
    	}
    }
    for (int i = 0; i < ashift; ++i) {
		t.w = l - a[i].w;
    	int p = lower_bound(b, b + bshift, t) - b;
    	if (p >= bshift) continue;
    	if (a[i].w + b[p].w > r) break;
    	int best = dp[p][0];
    	for (int carry = 0, j = 16; j > -1; --j)
    		if ((p + carry + (1 << j) < bshift) 
			and (a[i].w + b[p + carry + (1 << j)].w <= r)) {
    			if (b[dp[p + carry + 1][j]].v > b[best].v)
    				best = dp[p + carry + 1][j];
    			carry += (1 << j);
    		}
    	if (cur < b[best].v + a[i].v) {
    		cur = b[best].v + a[i].v;
    		leftb = a[i].ind;
    		rightb = b[best].ind;
    	}
    }
    vector<int> res;
    for (int i = 0; i < asize; ++i) 
		if (leftb & (1 << i)) res.push_back(i + 1);
    for (int i = 0; i < bsize; ++i) 
		if (rightb & (1 << i)) res.push_back(i + 1 + asize);
    out << res.size() << '\n';
    for (int i = 0; i < res.size(); ++i) out << res[i] << ' ';
	in.close();
	out.close();
}

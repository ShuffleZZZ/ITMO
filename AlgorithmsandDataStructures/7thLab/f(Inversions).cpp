#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool sortx(pair <int, int> fi, pair <int, int> se) {
	if (fi.first == se.first) return fi.second < se.second;
	return fi.first < se.first;
}

long long gather(int a[], int res[], int left, int mid, int r) {
	int l = left, m = mid, cur = left;
	long long amount = 0;
	while ((l <= mid - 1) and (m <= r))
		if (a[l] <= a[m]) res[cur++] = a[l++];
    	else {
      		res[cur++] = a[m++];
      		amount += (mid - l);
    	}
  	while (l <= mid - 1) res[cur++] = a[l++];
  	while (m <= r) res[cur++] = a[m++];
  	for (int i = left; i <= r; ++i) a[i] = res[i];
  	return amount;
}

long long  inv(int a[], int res[], int l, int r) {
  	long long amount = 0;
  	if (r > l) {
    	int m = (r + l) >> 1	;
    	amount = inv(a, res, l, m);
    	amount += inv(a, res, m + 1, r);
    	amount += gather(a, res, l, m + 1, r);
  	}
  	return amount;
}

int main() {
    ifstream in;
	in.open("john.in");
	ofstream out;
	out.open("john.out");
	int n;
    in >> n;
    pair <int, int> cards[n];
    for(int i = 0; i < n; i++) 
		in >> cards[i].first >> cards[i].second;
	sort(cards, cards + n, sortx);
	int a[n], res[n] = {};
	for(int i = 0; i < n; i++) a[i] = cards[i].second;
	out << inv(a, res, 0, n - 1);
	in.close();
	out.close();
}

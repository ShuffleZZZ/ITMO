#include <fstream>

using namespace std;

int ans = 0;
int eratosfen[168] = {2,3,5,7,11,13,17,19,23,29,31,37,
41,43,47,53,59,61,67,71,73,79,83,89,
97,101,103,107,109,113,127,131,137,139,149,151,
157,163,167,173,179,181,191,193,197,199,211,223,
227,229,233,239,241,251,257,263,269,271,277,281,
283,293,307,311,313,317,331,337,347,349,353,359,
367,373,379,383,389,397,401,409,419,421,431,433,
439,443,449,457,461,463,467,479,487,491,499,503,
509,521,523,541,547,557,563,569,571,577,587,593,
599,601,607,613,617,619,631,641,643,647,653,659,
661,673,677,683,691,701,709,719,727,733,739,743,
751,757,761,769,773,787,797,809,811,821,823,827,
829,839,853,857,859,863,877,881,883,887,907,911,
919,929,937,941,947,953,967,971,977,983,991,997};

bool permu(int *a, int n) {
  int j = n - 2;
  while ((j != -1) and (a[j] >= a[j + 1])) --j;
  if (j == -1) return 0;
  int k = n - 1;
  while (a[j] >= a[k]) --k;
  swap(a[j], a[k]);
  int l = j + 1, r = n - 1;
  while (l < r) swap(a[l++], a[r--]);
  return 1;
}

void check(int res) {
	if (res == 0) {
		++ans;
		return;
	}
	int amount = 1, i = 0, was = 1;
	while (res != 1) {
		if (res % eratosfen[i] == 0) {
			++amount;
			res /= eratosfen[i];
		} else {
			was *= amount;
			amount = 1;
			++i;
		}
	}
	was *= amount;
	if (was % 3 == 0) ++ans;
}

int main() {
	ifstream in;
	in.open("beautiful.in");
	ofstream out;
	out.open("beautiful.out");
	int n, r;
	in >> n >> r;
	int a[n];
	unsigned long long res = 0;
	for (int i = 0; i < n; i++) a[i] = i + 1;
	for (int i = 0; i < n - 1; ++i) res += a[i] * a[i + 1];
	res %= r;
	check(res);
	while(permu(a, n)) {
		res = 0;
		for (int i = 0; i < n - 1; ++i) res += a[i] * a[i + 1];
		res %= r;
		check(res);
	}
	out << ans;
	in.close();
	out.close();
}

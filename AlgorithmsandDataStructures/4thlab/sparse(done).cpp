#include <fstream>

using namespace std;

int log(int n) {
	int pow = 0;
	while ((1 << pow) <= n) {
		++pow;
	}
	return pow - 1;
}

int main() {
	ifstream in;
	in.open("sparse.in");
	ofstream out;
	out.open("sparse.out");
	int n, m, u, v;
	in >> n >> m;
	int pow = log(n);
	int tab[pow + 1][n];
	in >> tab[0][0];
	for (int i = 1; i < n; ++i) {
		tab[0][i] = (23 * tab[0][i - 1] + 21563) % 16714589;
	}
    for (int i = 1; i <= pow; ++i) {
    	for (int j = 0; j <= (n - (1 << i)); ++j) {
    		if (tab[i - 1][j] <= tab[i - 1][j + (1 << (i - 1))]) {
    			tab[i][j] = tab[i - 1][j];
    		} else {
    			tab[i][j] = tab[i - 1][j + (1 << (i - 1))];
    		}
    	}
    }
	in >> u >> v;
	int b;
	if (u == v) {
		b = tab[0][v - 1];
	} else {
		if (u > v) {
			int pow = log(u - v + 1);
			if (tab[pow][v - 1] <= tab[pow][u - (1 << pow)]) {
				b = tab[pow][v - 1];
			} else {
			  	b = tab[pow][u - (1 << pow)];
			}
		} else {
			int pow = log(v - u + 1);
			if (tab[pow][u - 1] <= tab[pow][v - (1 << pow)]) {
				b = tab[pow][u - 1];
			} else {
			    b = tab[pow][v - (1 << pow)];
			}
		}
	}
	for (int i = 1; i < m; ++i) {
		u = ((17 * u + 751 + b + 2 * i) % n) + 1;
		v = ((13 * v + 593 + b + 5 * i) % n) + 1;
		if (u == v) {
			b = tab[0][v - 1];
		} else {
			if (u > v) {
				int pow = log(u - v + 1);
				if (tab[pow][v - 1] <= tab[pow][u - (1 << pow)]) {
					b = tab[pow][v - 1];
				} else {
			    	b = tab[pow][u - (1 << pow)];
			    }
			} else {
			 int pow = log(v - u + 1);
				if (tab[pow][u - 1] <= tab[pow][v - (1 << pow)]) {
					b = tab[pow][u - 1];
				} else {
			    	b = tab[pow][v - (1 << pow)];
			    }
			}	   
		}
	}
	out << u << ' ' << v << ' ' << b;
	in.close();
	out.close();
}

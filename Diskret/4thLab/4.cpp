#include <fstream>
#include <vector>

using namespace std;

const int maxv = 101;
const double eps = 0.0001;
int n;
vector < vector<double> > a (maxv, vector<double> (maxv, 0));
vector < vector<double> > b (maxv, vector<double> (maxv, 0));

inline bool check() {
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (b[j][i] - b[j + 1][i] >= eps) {
                return false;
            }
        }
    }
    return true;
}
 
int main() {
	ifstream in;
	in.open("markchain.in");
	ofstream out;
	out.open("markchain.out");	
	out.precision(5);
	out.setf(ios::fixed);
	out.setf(ios::showpoint);
    in >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> a[i][j];
        }
    }
    b = a;
	while (!check()) {
		vector < vector<double> > c (n, vector<double> (n, 0));
        for (int i = 0; i < n; ++i) {
        	for (int j = 0; j < n; ++j) {
            	for (int k = 0; k < n; ++k) {
                	c[i][j] += b[i][k] * a[k][j];
            	}
        	}
    	}
    	a = c;
    	b = a;
    }
    for (int i = 0; i < n; ++i) {
        out << b[0][i] << '\n';
    }
	in.close();
	out.close();
}

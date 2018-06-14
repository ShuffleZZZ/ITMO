#include <fstream>
#include <vector>

using namespace std;

vector < vector <short> > b(4, vector <short> (4));
vector < vector <short> > res(4, vector <short> (4, 0));

void multiply (int num) {
	for (short i = 3; i >= 0; i--)
        for (short j = 3; j >= 0; j--) {
            b[i][j] = num & 1;
            num >>= 1;
        }
	for (short i = 0; i < 4; i++)
        for (short j = 0; j < 4; j++)
            for (short k = 0; k < 4; k++) {
                res[i][j] += (b[i][k] * b[k][j]) & 1;
                res[i][j] &= 1; 
            }
}

int main() {
	ifstream in;
	in.open("sqroot.in");
	ofstream out;
	out.open("sqroot.out");
	vector < vector <short> > a(4, vector <short> (4));
	for (short i = 0; i < 4; ++i) 
		for (short j = 0; j < 4; ++j)
			in >> a[i][j];
	for (int i = 0; i <= (1 << 16); ++i) {
		multiply(i);
		if (res == a) {
			for (short j = 0; j < 4; ++j) {
				for (short k = 0; k < 4; ++k)
					out << b[j][k] << ' ';
				out << '\n';
			}
			return 0;
		}
		res.assign(4, vector <short> (4, 0));
	}
	out << "NO SOLUTION";
	in.close();
	out.close();
}

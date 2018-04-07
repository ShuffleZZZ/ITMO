	#include <iostream>
	#include <fstream>
	using namespace std;

int main () {
	ifstream in;
	in.open("garland.in");
	ofstream out;
	out.open ("garland.out");
	int n;
	in>>n;
	double a[n];
	in>>a[0];
	double l=0;
	double r=a[0];
	double res = -1;
	while (true){
		double mid = (l+r) / 2;
		if ((mid==l) or (mid==r)){
			break;
		}
		double pr = a[0];
		double cr = mid;
		bool bol =cr > 0;
		for (int i=2;i<n;i++){
			double nx = 2*cr - pr +2;
			bol &= nx > 0;
			pr = cr;
			cr = nx;
		}
			if (bol){
				r=mid;
				res = cr;
			} else {
				l=mid;
			}
		}
	out << fixed;
	out.precision(2);
	out << res << endl;
	in.close();
	out.close();
}
		
		

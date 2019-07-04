 #include <fstream>
 #include <cmath>
 #include <vector>

 using namespace std;

int main() {
	ifstream in;
    in.open("telemetry.in");
    ofstream out;
    out.open("telemetry.out");
	int n,k,sz,key;
	in>>n>>k;
	sz=pow(k,n);
	int a[sz][n];
	key=k;
	for(int i=0;i<n;i++) {
		for(int j=0;j<sz;j++) {		
			a[j][i]=j%k/(k/key);
			if((j/k)%2!=0) {
				a[j][i]=key-a[j][i]-1;
			}
		}
		k*=key;
	}
	for(int i=0;i<sz;i++) {
		for(int j=0;j<n;j++) {
			out<<a[i][j];
		}
		out<<'\n';
	}
	in.close();
	out.close();
}

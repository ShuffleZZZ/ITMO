 #include <iostream>
 
 using namespace std;
 
int main() {
	int n;
	unsigned long long x=0;
	cin>>n;
	unsigned long long a[10][n];
	for (int i=0;i<10;i++) {
		a[i][0]=1;
	}
	a[0][0]=0;
	a[8][0]=0;
	for (int i=1;i<n;i++) {
		a[0][i]=a[4][i-1]+a[6][i-1];
		if (a[0][i]>1000000000) {
			a[0][i]%=1000000000;
		}
		a[1][i]=a[6][i-1]+a[8][i-1];
		if (a[1][i]>1000000000) {
			a[1][i]%=1000000000;
		}
		a[2][i]=a[7][i-1]+a[9][i-1];
		if (a[2][i]>1000000000) {
			a[2][i]%=1000000000;
		}
		a[3][i]=a[4][i-1]+a[8][i-1];
		if (a[3][i]>1000000000) {
			a[3][i]%=1000000000;
		}
		a[4][i]=a[3][i-1]+a[9][i-1]+a[0][i-1];
		if (a[4][i]>1000000000) {
			a[4][i]%=1000000000;
		}
		a[5][i]=0;
		a[6][i]=a[1][i-1]+a[7][i-1]+a[0][i-1];
		if (a[6][i]>1000000000) {
			a[6][i]%=1000000000;
		}
		a[7][i]=a[2][i-1]+a[6][i-1];
		if (a[7][i]>1000000000) {
			a[7][i]%=1000000000;
		}
		a[8][i]=a[1][i-1]+a[3][i-1];
		if (a[8][i]>1000000000) {
			a[8][i]%=1000000000;
		}
		a[9][i]=a[2][i-1]+a[4][i-1];
		if (a[9][i]>1000000000) {
			a[9][i]%=1000000000;
		}
	}
	for (int i=0;i<10;i++) {
		x+=a[i][n-1];
		if (x>=1000000000) {
			x%=1000000000;
		}
	}
	cout<<x;
}

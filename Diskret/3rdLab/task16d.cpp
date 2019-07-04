 #include <fstream>
 
 using namespace std;
 
int main() {
	ifstream in;
    in.open("choose2num.in");
    ofstream out;
    out.open("choose2num.out");
    int n,k,res=0;
    in>>n>>k;
    int a[k+1];
    a[0]=0;
    for (int i=1;i<=k;i++) {
    	in>>a[i];
    }
    long long c[n][n];
    for (int i=0;i<n;i++) {
    	for (int j=0;j<n;j++) {
    		c[i][j]=0;
    	}
    }
    c[0][0]=1;
    for (int i=1;i<n;i++) {
    	for (int j=0;j<n;j++) {
    		if (j==0) {
    			c[i][j]=c[i-1][j];
    		} else {
    			c[i][j]=c[i-1][j-1]+c[i-1][j];
    		}
    	}
    }
    for (int i=1;i<=k;i++) {
    	for (int j=a[i-1]+1;j<=a[i]-1;j++) {
    		res+=c[n-j][k-i];
    	}
    }
    out<<res;
    in.close();
    out.close();
}

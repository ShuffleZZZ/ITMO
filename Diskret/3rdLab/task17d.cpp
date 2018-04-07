 #include <fstream>
 #include <string>
 #include <vector>
 
 using namespace std;

int main() {
	ifstream in;
    in.open("num2brackets.in");
    ofstream out;
    out.open("num2brackets.out");
    int n,depth=0;
    long long k;
    string s="";
    in>>n>>k;
    k++;
    vector <vector <long long> > d;
    d.resize(2*n+1,vector <long long> (n+1,0));
    d[0][0]=1;
    for (int i=0;i<2*n;i++) {
    	for (int j=0;j<=n;j++) {
    		if (j>0) {
    			d[i+1][j-1]+=d[i][j];
    		}
    		if (j<n) {
    			d[i+1][j+1]+=d[i][j];
    		}
    	}
    }
    for (int i=0;i<2*n;i++) {
    	if ((d[2*n-1-i][depth+1]>=k) and (depth<n)) {
    		s+='(';
    		depth++;
    	} else {
    		if (depth<n) {
    			k-=d[2*n-1-i][depth+1];
    		}
    		s+=')';
    		depth--;
    	}
	}
	out<<s;
    in.close();
    out.close();
}

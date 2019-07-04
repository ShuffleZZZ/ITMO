 #include <iostream>
 #include <fstream>
 
 using namespace std;
 
int main() {
	ifstream in;
    in.open("perm2num.in");
    ofstream out;
    out.open("perm2num.out");
    int n;
    long long num=0;
    in>>n;
    int a[n+1];
    bool was[n+1];
    long long fact[n+1];
    for (int i=1;i<=n;i++) {
    	in>>a[i];
    	was[i]=false;
    }
    fact[0]=1;
	for (int i=1;i<n+1;i++) {
		fact[i]=i*fact[i-1];
	}
    for (int i=1;i<=n;i++) {
    	for (int j=1;j<=a[i]-1;j++) {
    		if (!was[j]) {
    			num+=fact[n-i];
    		}
    	}
    	was[a[i]]=true;
    }
    out<<num;
    in.close();
    out.close();
}

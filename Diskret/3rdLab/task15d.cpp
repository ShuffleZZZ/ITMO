 #include <fstream>
 #include <vector>
 #include <iostream>
 using namespace std;
 
 /*vector <long long> fact;
 
long long choose(int n,int k) {
	if (k==0) {
		return 1;
	} else {
	 	return (fact[n]/fact[k])/fact[n-k];
 	}
}*/

int main() {
	ifstream in;
    in.open("num2choose.in");
    ofstream out;
    out.open("num2choose.out");
    int n,k,nxt;
    vector <int> res;
    long long m,x;
    in>>n>>k>>m;
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
    //fact.resize(n);
    //fact[0]=1;
    //for (int i=1;i<n;i++) {
    //	fact[i]=fact[i-1]*i;
    //}
    nxt=1;
    while (k>0) {
    	x=c[n-1][k-1];
    	if (m<x) {
    		res.push_back(nxt);
    		k--;
    	} else {
    		m-=x;
    	}
    	n--;
    	nxt++;
    }
    for (int i=0;i<res.size();i++) {
    	out<<res[i]<<' ';
    }
    //for (int i=0;i<n;i++) {
    //	for (int j=0;j<n;j++) {
    //		cout<<c[i][j]<<' ';
    //	}
    //	cout<<'\n';
    //}
    in.close();
    out.close();
}

 #include <fstream>
 #include <cmath>
 //#include <iostream>
 
 using namespace std;
 
unsigned int sz;
 
int block(int x,int y) {
	int z=(x&y)&((x&y)*2);
	if (z!=0) {
		return 0;
	}
	z=((sz-1-x)&(sz-1-y))&(((sz-1-x)&(sz-1-y))*2);
	if (z!=0) {
		return 0;
	}
	return 1;
}
		
 
int main(){
	ifstream in;
	in.open("nice.in");
	ofstream out;
	out.open ("nice.out");
	unsigned int n,m;
	unsigned long long res=0;
	in>>n>>m;
	if (n>m) {
		swap(n,m);
	}
	sz=pow(2,n);
	unsigned int d[sz][sz];
	unsigned long long a[m][sz];
	for (unsigned int i=0;i<sz;i++) {
		for (unsigned int j=0;j<sz;j++) {
			if (block(i,j))  { 	// ((((i&j)&((i&j)*2))==0) or ((((~i)&(~j))&(((~i)&(~j))*2))==0) or ((((sz-1-i)&(sz-1-j))&(((sz-1-i)&(sz-1-j))*2))==0)) {	//~~~~
				d[i][j]=1;
			} else {
				d[i][j]=0;
			}
		}
	}
	/*for (unsigned int i=0;i<sz;i++) {
		for (unsigned int j=0;j<sz;j++) {
			cout<<d[i][j]<<' ';
		}
		cout<<'\n';
	}*/
	for (unsigned int i=0;i<sz;i++) {
		a[0][i]=1;
	}
	for (unsigned int i=0;i<sz;i++) {
		for (unsigned int j=1;j<m;j++) {
			a[j][i]=0;
		}
	}
	for (unsigned int k=1;k<m;k++) {
		for (unsigned int i=0;i<sz;i++) {
			for (unsigned int j=0;j<sz;j++) {
				//cout<<a[k][i]<<' '<<k<<' '<<i<<'\n';
				a[k][i]+=a[k-1][j]*d[j][i];
				//cout<<a[k][i]<<' '<<k<<' '<<i<<'\n';
			}
		}
	}
	/*for (unsigned int k=0;k<m;k++) {
		for (unsigned int i=0;i<sz;i++) {
			cout<<a[k][i]<<' ';
		}
		cout<<'\n';
	}*/
	for (unsigned int i=0;i<sz;i++) {
		res+=a[m-1][i];
	}
	out<<res;
	in.close();
	out.close();
}
	

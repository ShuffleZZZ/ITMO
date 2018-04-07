#include <fstream>
#include <algorithm>

using namespace std;

int main(){
	ifstream in;
	in.open("huffman.in");
	ofstream out;
	out.open ("huffman.out");
	unsigned long long n,ans,p;
	in>>n;
	int j=0;
	ans=0;
	unsigned long long a[n];
	for (int i=0;i<n;i++){
		in>>a[i];
	} 
	for (int j=0;j<n-1;j++){
		sort(a,a+n);
		p=a[j]+a[j+1];
		a[j+1]=p;
		ans+=p;
	}
	out<<ans;
	in.close();
	out.close();
}	

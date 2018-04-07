 #include <fstream>
 
 using namespace std;

int main() {
	ifstream in;
    in.open("num2perm.in");
    ofstream out;
    out.open("num2perm.out");
	int n,cur;
	long long k,been;
	in>>n>>k;
	int perm[n+1];
	bool was[n+1];
	for (int i=1;i<=n;i++) {
		perm[i]=0;
		was[i]=false;
	}
	long long fact[25];
	fact[0]=1;
	for (int i=1;i<25;i++) {
		fact[i]=i*fact[i-1];
	}
	for (int i=1;i<=n;i++) {
		been=k/fact[n-i];
		k%=fact[n-i];
		cur=0;
		for (int j=1;j<=n;j++) {
			if (!was[j]) {
				cur++;
				if (cur==been+1) {
					perm[i]=j;
					was[j]=true;
				}
			}
		}
	}
	for (int i=1;i<=n;i++) {
		out<<perm[i]<<" ";
	}
	in.close();
	out.close();
}

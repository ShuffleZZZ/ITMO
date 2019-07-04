 #include <fstream>

 using namespace std;
 
int main() {
	ifstream in;
    in.open("nextchoose.in");
    ofstream out;
    out.open("nextchoose.out");
    int n,k,c;
    long long a[10500];
	in>>n>>k;
	for (int i=0;i<k;i++) {
		in>>a[i];
	}
	c=-1;
	for (int i=k-1;i>=0;i--) {
		if (a[i]<n-k+i+1) {
			a[i]++;
			c=i+1;
			break;
		}
	}
	if (c==-1) {
		out<<-1;
	} else {
		for (int i=c;i<k;i++) {
			a[i]=a[i-1]+1;
		}
		for (int i=0;i<k;i++) {
			out<<a[i]<<' ';
		}
	}
	in.close();
	out.close();
}

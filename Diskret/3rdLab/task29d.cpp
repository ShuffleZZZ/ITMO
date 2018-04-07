#include <fstream>
using namespace std;

int main() {
	ifstream in;
    in.open("nextpartition.in");
    ofstream out;
    out.open("nextpartition.out");
	int n,i,prev,last;
	int a[250000];
	char s;
	i=0;
	in>>n>>s;
	while (in>>a[i]) {
		in>>s;
		i++;
	}
	if (i==1) {
		out<<"No solution";
	} else {
		out<<n<<"=";
		for (int j=0;j<i-2;j++) {
			out<<a[j]<<"+";
		}
		prev=a[i-2]+1;
		last=a[i-1]-1;
		if (prev>last) {	
			out<<prev+last;
		} else {
			out<<prev<<"+";
			for (int j=1;j<=last/prev-1;j++){
				out<<prev<<"+";
			}
			out<<last-prev*(last/prev-1);
		}
	}
	in.close();
	out.close();
}

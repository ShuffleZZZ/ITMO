 #include <fstream>
 #include <string>
 #include <algorithm>

using namespace std;

int main () {
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open ("output.txt");
	string a,s;
    in>>a>>s;
    int d[a.size()+1][s.size()+1];
    d[0][0]=0;
    for (int i=1;i<=s.size();i++) {
    	d[0][i]=d[0][i-1]+1;
    }
    for (int i=1;i<=a.size();i++) {
    	d[i][0]=d[i-1][0]+1;
    	for (int j=1;j<=s.size();j++) {
    		if (a[i-1]!=s[j-1]) {
				d[i][j]=min(min(d[i-1][j],d[i][j-1]),d[i-1][j-1])+1;
			} else {
				d[i][j]=d[i-1][j-1];
			}
		}
	}
    out<<d[a.size()][s.size()];
    in.close();
    out.close();
}

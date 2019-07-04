 #include <fstream>
 #include <algorithm>
 #include <string>

 using namespace std;

int main() {
    ifstream in;
	in.open("bwt.in");
	ofstream out;
	out.open ("bwt.out");
	string s,a[1000],b;
    in>>s;
    for(int i=0;i<s.size();i++){
        for(int j=0;j<s.size();j++){
            b+=s[(j+i)%s.size()];
        }
        a[i]=b;
        b.clear();
    }
    sort(a,a+s.size());
    for(int i=0;i<s.size();i++){
        out<<a[i][s.size()-1];
    }
    in.close();
    out.close();
}

 #include <fstream>
 #include <string>
 
 using namespace std;

ifstream in;
ofstream out;
int n,k;


int func(string s,int begin, int kol) { 
	string cur;
	if(kol==k) {
  		out<<s<<'\n';
  		return 1;
    } 
	for(int i=begin+1;i<=n;i++) {
       	if(i>=10) {
           	cur+=i/10+'0';
    	}
       	cur+=i%10+'0';
       	func(s+cur+' ',i,kol+1);
       	cur.clear();
	}
}
 
int main(){
    in.open("choose.in");
    out.open("choose.out");
    in>>n>>k;
    string a="";
    func(a,0,0);
    in.close();
    out.close();
}

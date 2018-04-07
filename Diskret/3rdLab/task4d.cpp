 #include <fstream>
 #include <set>
 #include <cmath>

 using namespace std;

int main(){
	ifstream in;
    in.open("chaincode.in");
    ofstream out;
    out.open("chaincode.out");
	int n,size,s; 
	in>>n;
	size=pow(2,n);
	set<int> was;
	s=0;
	for (int i=0;i<size;i++){
		was.insert(s);
		for (int i=n-1;i>=0;i--){
			out<<((s&1<<i)!=0);
		}
		out<<'\n';
		s*=2;
		s&=size-1;
		if (was.find(s|1)==was.end()){
			s|=1;
		} else if (was.find(s)!=was.end()){
		break;
		}
	}
	in.close();
	out.close();
}

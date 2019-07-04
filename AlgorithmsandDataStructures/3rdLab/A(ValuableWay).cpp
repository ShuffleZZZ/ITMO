 #include <fstream>
 #include <vector>
 
 using namespace std;
 
int n,k,cur,x,res=0;
bool first;
vector <int> a,b;
 
void func(int key) {
	if (a[key]>=0) {
		if (key<a.size()-1) {
			b.push_back(key);
			res+=a[key];
			key++;
			func(key);
		}
		return;
	}
	first=true;
	for (int j=1;j<=k;j++) {
		if (a[key+j]>=0) {
			if (key+j<a.size()-1) {
				b.push_back(key+j);
				res+=a[key+j];
				key+=j+1;
				func(key);
			}
			return;
		} else if ((a[key+j]>x) or (first=true)) {
			if (key<a.size()-1) {
				first=false;
				x=a[key+j];
				cur=key+j;
			} else {
				return;
			}
		}	
	}
	if (cur<a.size()-1) {
		b.push_back(cur);
		res+=x;
		key=cur+1;
		func(key);
	}
	return;
}

int main() {
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");
	in>>n>>k;
	a.resize(n-2);
	for (int i=0;i<n-2;i++) {
		in>>a[i];
	}
	a.push_back(10100);
	func(0);
	out<<res<<'\n'<<b.size()+1<<'\n'<<1<<' ';
	for (int j=0;j<b.size();j++) {
		out<<b[j]+2<<' ';
	}
	out<<n;
	in.close();
	out.close();
}
	
				
				

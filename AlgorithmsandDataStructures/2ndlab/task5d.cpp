 #include <fstream>
 #include <iostream>
 #include <string>
 using namespace std;
 
int p[1000000],size[1000000],mink[1000000],maxk[1000000];
 
void create(int x) {
	p[x]=x;
	size[x]=1;
	mink[x]=x;
	maxk[x]=x;
}

int get(int x) {
	if (p[x]==x) {
		return x;
	}
	return p[x]=get(p[x]);
}
 
void uni(int a, int b) {
	a =get(a);
	b =get(b);
	if (a!=b){
		if (size[a]<size[b]){
			swap(a,b);
		}
		p[b]=a;
		if (mink[a]>mink[b]){
			mink[a]=mink[b];
		}
		if (maxk[a]<maxk[b]){
			maxk[a]=maxk[b];
		}
		size[a]+=size[b];
	}
}

int main() {
	ifstream in;
	in.open("dsu.in");
	ofstream out;
	out.open("dsu.out");
	int n,s1,s2;
	string s;
	in>>n;
	for (int i=1;i<=n;i++){
		create(i);
	}
	if(in){
		while (in>>s){
			if (s=="union"){
				in>>s1;
				in>>s2;
				uni(s1,s2);
			}
			if (s=="get"){
				in>>s1;
				s2=get(s1);
				out<<mink[s2]<<' '<<maxk[s2]<<' '<<size[s2]<<'\n';
			}
		}
	}
	in.close();
	out.close();
}


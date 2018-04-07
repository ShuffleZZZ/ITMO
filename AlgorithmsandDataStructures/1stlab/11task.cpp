	#include <iostream>
	#include <fstream>
	using namespace std;
	
int f(int t[],int v[],int n,double x,double l){
	double y;
	y=0.00;
	int k;
	k=-2;
	int time;
	time=0.00;
	int tim;
	tim=0.00;
	for (int i=0;i<n;i++){
		time+=t[i];
		if ((x-l)>=time){
			y+=t[i]*v[i];
			k=i+1;
			tim=time;
		}
	}
	if ((k!=-2) and (k!=n)){
	y+=(x-l-tim)*v[k];
	}
	return y;
}

int main () {
	ifstream in;
	in.open("trains.in");
	ofstream out;
	out.open ("trains.out");
	int L;
	in>>L;
	int n;
	in>>n;
	int t[n];
	int v[n];
	int count;
	for (int i = 0;i<n;i++) {
		in>>t[i];
		in>>v[i];
		count+=t[i];
	}
	double l=0;
	double r=count;
 	double mid;
 	int jj;
 	while(r-l>5){
 		jj = (l+r) / 2;
 			if (f(t,v,n,jj,0)<L){
 				l=jj;
			} else {
			 	r=jj;
			}
 	}
	double res;
	res=jj;
 	for (int x=jj+1;x<=count;x++){
 			while(r-l>0.01){
 				mid = (l+r) / 2;
 				if ((f(t,v,n,x,0)-f(t,v,n,x,mid))<L){
 					l=mid;
			 	} else {
			 		r=mid;
			 	}
		 	}
		 	l=0;
		 	r=count;
		if (mid>res){
			res=mid;
		}
	 }
	out << fixed;
	out.precision(3);
	out << res << endl;
	in.close();
	out.close();
}

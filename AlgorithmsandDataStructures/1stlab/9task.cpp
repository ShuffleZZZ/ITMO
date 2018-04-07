#include <iostream>
#include <fstream>
using namespace std;
 
  int binsearchl  (int a[], int key, int n){ 
    	int l = -1;                
    	int r = n;    
    	while (l < r - 1){      
        	int m = (l + r) / 2;    
        	if (a[m] < key){
            	l = m;}
        	else {
            	r = m;}}
    	return r;}
    int binsearchr(int a[], int key, int n){ 
    	int l = -1;         
    	int r = n;    
    	while (l < r - 1){  
        	int m = (l + r) / 2;
        	if (a[m] <= key){
            	l = m;}
        	else {
            	r = m;}}
    	return l;}
int main() {
	ifstream in;
	in.open("binsearch.in");
	ofstream out;
	out.open ("binsearch.out");
	int n;
	in>>n;
	int a[n];
	for (int i = 0;i<n;i++) {
		in>>a[i];
	}
	int m;
	in>>m;
    int b[m];
    for (int i = 0;i<m;i++) {
		in>>b[i];
	}
    for (int i = 0; i < m; i++ ) {
		if ((binsearchl(a,b[i],n)+1)<=(binsearchr(a,b[i],n)+1)) {
    		out<<(binsearchl(a,b[i],n)+1)<<" "<<(binsearchr(a,b[i],n)+1)<<"\n";}
    	else{
    		out<<("-1 -1 \n");}
    	}
	in.close();
	out.close();
}


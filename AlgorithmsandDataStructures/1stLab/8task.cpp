#include <iostream> 
#include <fstream> 
#include <cstdlib> 
#include <cstdio> 

using namespace std; 

int a[30000001];

int random() { 
return (rand() + (rand()<<16)); 
}  

void quicksort(int k, int l, int r) { 
	if (l == r){
		return;}
	int i;
	i = l;
	int j;
	j = r; 
	int mid=a[l+random()%(r-l)]; 
	while (i<=j) { 
		while (a[i]<mid){
			i++;}
		while (a[j]>mid){
			j--;}
		if (i<=j){
			swap(a[i++],a[j--]);} 
	} 
	if ((k>j) and (k<i)){
			return;}
	if ((j>l) and (k<=j)){
		quicksort(k,l,j);}
	if ((i < r) and (k >= i)){
		quicksort(k,i,r);}
}

int main() { 
	fstream in;
	in.open("kth.in");
	ofstream out;
	out.open ("kth.out");
	int n;
	in>>n;
	int k;
	in>>k;
	int A;
	in>>A;
	int B;
	in>>B;
	int C;
	in>>C;
	in>>a[0];
	in>>a[1];
	for (int i = 2; i < n; i++) {
		a[i]=A*a[i-2]+B*a[i-1]+C; }
	quicksort(k-1,0,n-1); 
	out<<a[k-1]; 
}

	#include <iostream>
	#include <fstream>
	#include <string>
	using namespace std;
	
void quickSort(int a[], int l, int r) {
      int i = l, j = r;
      int mid = a[(l + r) / 2];
      while (i <= j) {
            while (a[i] < mid)
                  i++;
            while (a[j] > mid)
                  j--;
            if (i <= j) {
				swap(a[i],a[j]);
                  i++;
                  j--;
            }
      };
      if (l < j)
            quickSort(a, l, j);
      if (i < r)
            quickSort(a, i, r);
}

int max4(int a, int b, int c, int d) {
	int max;
	if ((a>=b) and (a>=c) and (a>=d)) {
		max=a;
	}
	if ((b>=a) and (b>=c) and (b>=d)) {
		max=b;
	}
	if ((c>=b) and (c>=a) and (c>=d)) {
		max=c;
	}
	if ((d>=b) and (d>=c) and (d>=a)){
		max=d;
	}
	return max;
}

int min4(int a, int b, int c, int d) {
	int min;
	if ((a<=b) and (a<=c) and (a<=d)) {
		min=a;
	}
	if ((b<=a) and (b<=c) and (b<=d)) {
		min=b;
	}
	if ((c<=b) and (c<=a) and (c<=d)) {
		min=c;
	}
	if ((d<=b) and (d<=c) and (d<=a)){
		min=d;
	}
	return min;
}

int main () {
	ifstream in;
	in.open("style.in");
	ofstream out;
	out.open ("style.out");
	int n1;
	in>>n1;
	int a[n1+1];
	for (int i = 0;i<n1;i++) {
		in>>a[i];
	}
	a[n1]=100001;
	quickSort(a, 0,n1);
	int n2;
	in>>n2;
	int b[n2+1];
	for (int i = 0;i<n2;i++) {
		in>>b[i];
	}
	b[n2]=100001;
	quickSort(b, 0,n2);
	int n3;
	in>>n3;
	int c[n3+1];
	for (int i = 0;i<n3;i++) {
		in>>c[i];
	}
	c[n3]=100001;
	quickSort(c, 0,n3);
	int n4;
	in>>n4;
	int d[n4+1];
	for (int i = 0;i<n4;i++) {
		in>>d[i];
	}
	d[n4]=100001;
	quickSort(d, 0,n4);
	int i=0, j=0, l=0,m=0;
	int k=4,k0=n1+1,k1=n2+1,k2=n3+1,k3=n4+1, min=-1;
	int dif[4];
	while ((i<n1) or (j<n2) or (l<n3) or (m<n4)){
		if (min4(a[i], b[j], c[l], d[m])==a[i]){
			k0=i;
			if ((k0!=n1+1)  and (k!=0) and (k1!=n2+1) and (k2!=n3+1) and (k3!=n4+1) and ((min>(max4(a[k0],b[k1],c[k2],d[k3])-min4(a[k0],b[k1],c[k2],d[k3]))) or (min==-1))) {
				min=max4(a[k0],b[k1],c[k2],d[k3])-min4(a[k0],b[k1],c[k2],d[k3]);	
				dif[0]=a[k0];
				dif[1]=b[k1];
				dif[2]=c[k2];
				dif[3]=d[k3];
			}
			i++;
			k=0;
		}
		if (min4(a[i], b[j], c[l], d[m])==b[j]){
			k1=j;
			if ((k0!=n1+1) and (k!=1) and (k1!=n2+1) and (k2!=n3+1) and (k3!=n4+1) and ((min>(max4(a[k0],b[k1],c[k2],d[k3])-min4(a[k0],b[k1],c[k2],d[k3]))) or (min==-1))) {
				min=max4(a[k0],b[k1],c[k2],d[k3])-min4(a[k0],b[k1],c[k2],d[k3]);
				dif[0]=a[k0];
				dif[1]=b[k1];
				dif[2]=c[k2];
				dif[3]=d[k3];
			}
			j++;
			k=1;
		}
		if (min4(a[i], b[j], c[l], d[m])==c[l]){
			k2=l;
			if ((k0!=n1+1)  and (k!=2) and (k1!=n2+1) and (k2!=n3+1) and (k3!=n4+1) and ((min>(max4(a[k0],b[k1],c[k2],d[k3])-min4(a[k0],b[k1],c[k2],d[k3]))) or (min==-1))) {
				min=max4(a[k0],b[k1],c[k2],d[k3])-min4(a[k0],b[k1],c[k2],d[k3]);
				dif[0]=a[k0];
				dif[1]=b[k1];
				dif[2]=c[k2];
				dif[3]=d[k3];
			}
			l++;
			k=2;
		}
		if (min4(a[i], b[j], c[l], d[m])==d[m]){
			k3=m;
			if ((k0!=n1+1) and (k!=3) and (k1!=n2+1) and (k2!=n3+1) and (k3!=n4+1) and ((min>(max4(a[k0],b[k1],c[k2],d[k3])-min4(a[k0],b[k1],c[k2],d[k3]))) or (min==-1))) {
				min=max4(a[k0],b[k1],c[k2],d[k3])-min4(a[k0],b[k1],c[k2],d[k3]);
				dif[0]=a[k0];
				dif[1]=b[k1];
				dif[2]=c[k2];
				dif[3]=d[k3];
			}
			m++;
			k=3;
		}
		
	}
	out<<dif[0]<<' '<<dif[1]<<' '<<dif[2]<<' '<<dif[3];
	in.close();
	out.close();
}

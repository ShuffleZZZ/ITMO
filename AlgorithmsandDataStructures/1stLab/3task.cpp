	#include <iostream>
	#include <fstream>
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

int main () {
	ifstream in;
	in.open("sort.in");
	ofstream out;
	out.open ("sort.out");
	int n;
	in>>n;
	int a[n];
	for (int i = 0;i<n;i++) {
		in>>a[i];
	}
	quickSort(a, 0,n-1);
	for (int i = 0;i<n;i++) {
		out<<a[i]<<' ';
	}
	in.close();
	out.close();
}

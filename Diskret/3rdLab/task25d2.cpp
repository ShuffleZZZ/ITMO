 #include <fstream>

 using namespace std;

int main () {
    ifstream in;
    in.open("nextchoose.in");
    ofstream out;
    out.open("nextchoose.out");
    int n,k,i;
    in>>n>>k;
    int a[k+1];
    for (int j=0;j<k;j++) {
        in>>a[j];
    }
    a[k]=n+1;
    i=k-1;
    while ((i>=0) and (a[i+1]-a[i]<2)) {
    	i--;
    }
    if (i>=0) {
    	a[i]++;
    	for (int j=i+1;j<k;j++) {
    		a[j]=a[j-1]+1;
    	}
    	for (int j=0;j<k;j++) {
    		out<<a[j]<<' ';
    	}
    } else {
    	out<<"-1";
    }
    in.close();
    out.close();
}

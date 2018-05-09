 #include <iostream>
 #include <vector>

using namespace std;

int main () {
	int n,cur=0;
	vector <int> res;
    cin>>n;
    int d[n],prev[n],a[n];
    for (int i=0;i<n;i++) {
        cin>>a[i];
    }
    for (int i=0;i<n;i++) {
        d[i]=1;
        prev[i]=-1;
        for (int j=0;j<i;j++) {
            if ((a[j]<a[i]) and (d[j]+1>d[i])) {
                d[i]=d[j]+1;
                prev[i]=j;    
            }
        }
    }
    for (int i=0;i<n;i++) {
        if (d[i]>d[cur]) {
            cur=i; 
        }
    }
    cout<<d[cur]<<"\n";
    while (cur!=-1) {
        res.push_back(a[cur]);
        cur=prev[cur];
    }
    for (int i=res.size()-1;i>=0;i--) {
        cout<<res[i]<<' ';
    }
}

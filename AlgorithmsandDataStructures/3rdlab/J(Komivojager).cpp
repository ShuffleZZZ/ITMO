 #include <iostream>
 #include <vector>
  
 using namespace std;
  
int n,sasha=0,res,maxim,vasya=0; 
vector < vector <int> > a,d;
vector <int> road;
 
int func(int i,int mask) {
    if (d[i][mask]!=1000100) {
        return d[i][mask];
    }
    for (int j=0;j<n;j++) {
        if (mask&(1<<j)) {
            d[i][mask]=min(d[i][mask],func(j,mask-(1<<j))+a[i][j]);
        }
    }
    return d[i][mask];
 }
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cin>>n;
    a.resize(n,vector <int> (n));
    d.resize(n,vector <int> (1<<n,1000100));
    d[0][0]=0;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cin>>a[i][j];
        }
    }
    if (n==1) {
    	cout<<a[0][0]<<'\n'<<1;
    	return 0;
    }
    int mask=(1<<n)-1;
    res=func(0,mask);
    int i=0;
    while (mask!=0) {
        for (int j=0;j<n;j++) {
            if ((mask&(1<<j)) and (d[i][mask]==d[j][mask-(1<<j)]+a[i][j])) {
            	road.push_back(j+1);
            	if (!sasha) {
            		maxim=a[i][j];
            	} else if (a[i][j]>maxim) {
            		maxim=a[i][j];
            		vasya=sasha;
            	}
            	sasha++;
                i=j;
               	mask-=1<<j;
               	continue;
            }
        }
    }
    /*for (int i=0;i<road.size();i++) {
    	cout<<road[i]<<' ';
    }
    cout<<'\n';
    for (int i=0;i<maxi.size();i++) {
    	cout<<maxi[i]<<' ';
    }
    cout<<'\n'<<maxim<<' '<<vasya;*/
    cout<<res-maxim<<'\n';
    for (int i=0;i<sasha;i++) {
    	cout<<road[(vasya+i)%sasha]<<' ';
    }
}
    
	

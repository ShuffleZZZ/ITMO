 #include <iostream>
 #include <vector>
  
 using namespace std;
  
int main() {
    int n,bon,k1=0,k2=0,cur=1000000;
    cin>>n;
    if (n==0) {
    	cout<<n<<'\n'<<n<<' '<<n;
    	return 0;
    }
    vector <int> day;
    int c[n],a[n+2][n+2],b[n+2][n+2];
    for (int i=0;i<n;i++) {
        cin>>c[i];
    }
    for (int i=0;i<=n+1;i++) {
        for (int j=0;j<=n+1;j++) {
            a[i][j]=-1000000;
            b[i][j]=-n;
        }
    }
    if (c[0]>100) {
        a[0][1]=c[0];
        bon=1;
    } else {
        a[0][0]=c[0];
        bon=0;
    }
    for (int i=1;i<n;i++) {
        if (c[i]>100) {
            bon++;
        }   
        for (int j=0;j<=bon;j++) {
            if(c[i]>100) {
                if (j>0) {
                    if ((a[i-1][j+1]<a[i-1][j-1]+c[i]) and (a[i-1][j+1]>=0)) {
                            a[i][j]=a[i-1][j+1];
                            b[i][j]=j+1;
                        } else {
                            if (a[i-1][j-1]>=0) {
                                a[i][j]=a[i-1][j-1]+c[i];
                                b[i][j]=j-1;
                            }
                        }
                } else {
                    if (a[i-1][j+1]>=0) {
                        a[i][j]=a[i-1][j+1];
                        b[i][j]=j+1;
                    }
                }
            } else {
                if (a[i-1][j]>=0) {
                    if ((a[i-1][j+1]<a[i-1][j]+c[i]) and (a[i-1][j+1]>=0)) {
                        a[i][j]=a[i-1][j+1];
                        b[i][j]=j+1;
                    } else {
                        if (a[i-1][j]>=0) {
                            a[i][j]=a[i-1][j]+c[i];
                            b[i][j]=j;
                        }
                    }
                } else {
                    if (a[i-1][j+1]>=0) {
                        a[i][j]=a[i-1][j+1];
                        b[i][j]=j+1;
                    }
                }
            }
        }
    }   
	for (int i=0;i<=n;i++) {
		if ((a[n-1][i]<=cur) and (a[n-1][i]>0)) {
			cur=a[n-1][i];
			k1=i;
		}
	}
	cout<<cur<<'\n';
    int i=n-1;
    bon=k1;
    while (bon>=0) {
		cur=bon;
		bon=b[i][bon];
		if (bon>cur) {
			day.push_back(i+1);
			k2++;
		}
		i--;
	}
    cout<<k1<<' '<<k2<<'\n';
    for (int i=day.size()-1;i>=0;i--) {
        cout<<day[i]<<'\n';
    }
}

	
	

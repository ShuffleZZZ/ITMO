 #include <iostream>
 #include <string>
 
 using namespace std;
 
string s;
int a[150][150],comp[150][150];	//({{}]) test
 
void func(int i,int j) {
    if (a[i][j]!=j-i+1) {
        if (a[i][j]==0) {
            for (int k=i;k<=j;k++) {
                cout<<s[k];
            }
            return;
        }
        if (comp[i][j]==-1) {
            cout<<s[i];
            func(i+1,j-1);
            cout<<s[j];
        } else {
            func(i,comp[i][j]);
            func(comp[i][j]+1,j);
        }
    }
    return;
}
  
int main() {
    cin>>s;
    for (int i=0;i<s.size();i++) {
        for (int j=0;j<s.size();j++) {
            if (i==j) {
                a[i][j]=1;
            } else {
                a[i][j]=0;
            }
        }
    }
    for (int j=0;j<s.size();j++) {
        for (int i=j;i>=0;i--) {
            if (i!=j) {
                int res=500,less=-1;
                if (((s[i]=='(') and (s[j]==')')) or ((s[i]=='[') and (s[j]==']')) or ((s[i]=='{') and (s[j]=='}'))) {
                   	res=a[i+1][j-1];
                }
                for (int mid=i;mid<j;mid++) {
                    int in=a[i][mid]+a[mid+1][j];
                    if (in<res) {
                        res=in;
                        less=mid;
                    }
                }
                //if ((comp[i-1][j+1]==-1) and (a[i-1][j+1]<a[i][j])) {
				//	a[i-1][j+1]==a[i+1][j-1];
				//}
                a[i][j]=res;
                comp[i][j]=less;
            }
        }
    }
    /*for (int i=0;i<s.size();i++) {
        for (int j=0;j<s.size();j++) {
        	cout<<a[i][j]<<' ';
        } 
        cout<<'\n';
    }
    for (int i=0;i<s.size();i++) {
        for (int j=0;j<s.size();j++) {
        	cout<<comp[i][j]<<' ';
        }
        cout<<'\n';
    }*/
    func(0,s.size()-1);
}

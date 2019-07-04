 #include <fstream>
 #include <string>
 #include <vector>
 #include <cmath>

 using namespace std;

long long n,k,cur,diff=0,x,a[45][45];
string s="";
vector <char> brack;

void func(char sk,int i) {
	if (diff<n) {
		x=a[i][diff+1]*pow(2,(i-diff-1)/2);
        cur=x;
	} else {
        cur=0;
    }
    if (cur>=k) {
    	brack.push_back(sk);
    	diff++;
        s+=sk;
    }
}

int main() {
    ifstream in;
    in.open("num2brackets2.in");
    ofstream out;
    out.open("num2brackets2.out");
    in>>n>>k;
    for (int i=0;i<45;i++) {
        for (int j=0;j<45;j++) {
        	if ((i==0) and (j==0)) {
        		a[i][j]=1;
        	} else {
            	a[i][j]=0;
            }
        }
    }
    for (int i=0;i<2*n;i++) {
        for (int j=0;j<=n;j++) {
            if (j<n) {
                a[i+1][j+1]+=a[i][j];
            }
            if (j>0) {
                a[i+1][j-1]+=a[i][j];
            }
        }
    }
    k++;
    for (int i=2*n-1;i>=0;i--) {
        func('(',i);
        if (cur<k) {
        	k-=cur;
        } else {
        	continue;
        }
        if ((brack.size()>0) and (brack[brack.size()-1]=='(') and (diff>0)) {
        	x=a[i][diff-1]*pow(2,(i-diff+1)/2);
            cur=x;
        } else {
            cur=0;
        }
        if (cur>=k) {
        	brack.pop_back();
        	diff--;
            s+=')';
            continue;
        }
        k-=cur;
        func('[',i);
        if (cur<k) {
        	k-=cur;
        } else {
        	continue;
        }
        brack.pop_back();
        diff--;
        s+=']';
    }
    out<<s;
    in.close();
    out.close();
}

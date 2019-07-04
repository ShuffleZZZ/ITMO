 #include <fstream>
 #include <vector>
 #include <algorithm>

 using namespace std;

int main () {
    ifstream in;
    in.open("nextperm.in");
    ofstream out;
    out.open("nextperm.out");
    int n,cur;
    in>>n;
	vector <int> a,b,c;
    for(int i=0;i<n;i++) {
        in>>cur;
        a.push_back(cur);
        b.push_back(cur);
        c.push_back(cur);
    }
    for(int i=n-2;i>=0;i--) {
        if(b[i]>b[i+1]) {
            cur=i+1;
            for(int j=i+1;j<n;j++) {
                if((b[cur]<b[j]) and (b[j]<b[i])) {
                    cur=j;
                }
            }
            swap(b[i],b[cur]);
            reverse(b.begin()+i+1,b.end());
            for(int k=0;k<b.size();k++) {
        		out<<b[k]<<' ';
    		}
    		break;
        }
    }
    if(a==b) {
    	for(int i=0;i<n;i++) {
        	out<<0<<' ';
        }
    }
    out<<"\n";
    for(int i =n-2;i>=0;i--) {
        if(c[i]<c[i+1]) {
            cur=i+1;
            for(int j=i+1;j<n;j++) {
                if((c[cur]>c[j]) and (c[j]>c[i])) {
                    cur=j;
                }
            }
            swap(c[i],c[cur]);
            reverse(c.begin()+i+1,c.end());
            for(int k=0;k<c.size();k++) {
        		out<<c[k]<<' ';
    		}
    		break;
        }
    }
    if(a==c) {
    	for(int i=0;i<n;i++) {
        	out<<0<<' ';
        }
    }
	in.close();
	out.close();
}

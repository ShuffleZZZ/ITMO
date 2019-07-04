 #include <fstream>
 
 using namespace std;

ifstream in;
ofstream out;
int n,a[50];

void func(int l,int sz) {
    if (sz==0) {
    	out<<a[1];
        for (int i=2;i<=l-1;i++) {
            out<<'+'<<a[i];
        }
        out<<'\n';
        return;
    }
    for (int i=a[l-1];i<=sz;i++) {
        a[l]=i;
        func(l+1,sz-i);
    }
}

int main() {
    in.open("partition.in");
    out.open("partition.out");
    in>>n;
    a[0]=1;
    func(1,n);
	in.close();
	out.close();
}
	/*vector<int> a[n];
    for (int i=0;i<n;i++){
    	a[i].push_back(1);
    }
    while (a[0].back()!=n){
    	for (int j=n;j>2;j--){
    		for (int i=0;i<j-2;i++){
    			a[i].push_back(a[i].back());
    		}
    		for (int i=j-2;i<n;i++){
    			a[i].push_back(0);
    		}
    		a[j-1].push_back(a[j].back()+a[j-1].back());
    	}
    	a[0].push_back(a[0].back()+1);
    	int i=1;
    	while (a[i-1].back()+a[0].back()<=n){
    		a[i].push_back(a[0].back());
    		i++;
    	}
    	for (int j=i;i<n;i++){
			a[i].push_back(0);
		}
	}
	for (int i=0;i<a[0].size();i++){
		for (int j=0;j<n;j++){
			if (!a[j].empty()){
				cout<<a[j][i];
			}
		}
		cout<<'\n';
	}*/
    		
    	

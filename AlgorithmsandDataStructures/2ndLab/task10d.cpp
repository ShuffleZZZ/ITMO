 #include <fstream>

 using namespace std;

int main(){
	ifstream in;
    in.open("bureaucracy.in");
    ofstream out;
    out.open("bureaucracy.out");
    int n,m,s,round;
    in>>n>>m;
    int a[n];
    for(int i=0;i<n;i++){
        in>>a[i];
    }
    while ((m>=n) and (n>0)){
        round=m/n;
        m=m%n;
        s=0;
        for(int i=0;i<n;i++){
            a[i]-=round;
            if(a[i]<0){
                m-=a[i];
            }
			if(a[i]>0){
                a[s++]=a[i];
            }
        }
        n=s;
    }
    s=0;
    if(n==0) {
        out<<"-1";
    } else {
	    for(int i=0;i<m;i++){
	    	a[i]-=1;
	        if(a[i]==0){
	            s++;
	        }
	    }
	    out<<n-s<<'\n';
	    for(int i=m;i<n+m;i++){
	    	round=i/n;
			s=i%n;
	        if(!round or (a[s]!=0)){
	            out<<a[s]<<' ';
	        }
	    }
	}
	in.close();
	out.close();
}

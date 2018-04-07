#include <fstream>

using namespace std;

int main() {
	ifstream in;
	in.open("hemoglobin.in");
	ofstream out;
	out.open("hemoglobin.out");
	int hem[100000],n,ind,s1;
	char s;
	unsigned long sum[100000];
	ind=0;
	in>>n;
    for(int i=0;i<n;i++){
    	in>>s;
        if(s=='+'){
            in>>s1;
            hem[ind]=s1;
            if(!ind){
            	sum[ind]=s1;
            } else {
            	sum[ind]=sum[ind-1]+s1;
            }
            ind++;
        }
		if(s=='?'){
            in>>s1;
            if (s1==ind){
            	out<<sum[ind-1]<<'\n';
            } else {
            	out<<sum[ind-1]-sum[ind-s1-1]<<'\n';
            }
        }
		if(s=='-'){
            out<<hem[--ind]<<'\n';
        }
    }
	in.close();
	out.close();
}

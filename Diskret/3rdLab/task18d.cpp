 #include <fstream>
 #include <string>
 #include <vector>
 
 using namespace std;

int main() {
	ifstream in;
    in.open("brackets2num.in");
    ofstream out;
    out.open("brackets2num.out");
    long long num=0,depth=0;
    string s;
    in>>s;
    vector <vector <long long> > d;
    d.resize(s.size()+1,vector <long long> (s.size()/2+1,0));
    d[0][0]=1;
    for (int i=0;i<s.size();i++) {
    	for (int j=0;j<=s.size()/2;j++) {
    		if (j>0) {
    			d[i+1][j-1]+=d[i][j];
    		}
    		if (j<s.size()/2) {
    			d[i+1][j+1]+=d[i][j];
    		}
    	}
    }
    for (int i=0;i<s.size();i++) {
    	if (s[i]=='(') {
    		depth++;
    	} else {
    		if (depth<s.size()/2) {
	    		num+=d[s.size()-1-i][depth+1];
	    	}
	    	depth--;
    	}
    }
    out<<num;
    in.close();
    out.close();
}

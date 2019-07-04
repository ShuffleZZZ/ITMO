 #include <fstream>
 #include <algorithm>
 #include <string>

 using namespace std;

int main() {
    ifstream in;
	in.open("mtf.in");
	ofstream out;
	out.open ("mtf.out");
	int alb[26],pos,c;
	string s;
    for (int i=0;i<26;i++){
    	alb[i]=i;
    }
    in>>s;
    for (int i=0;i<s.size();i++){
    	c=s[i]-'a';
    	if(alb[0]==c){
    		out<<1<<' ';
    		continue;
    	}
    	for (int j=1;j<26;j++){
    		if(alb[j]==c){
    			pos=j;
    			break;
    		}
    	}
    	copy(alb,alb+pos,alb+1);
    	alb[0]=c;
    	out<<pos+1<<' ';
    }
    in.close();
    out.close();
}

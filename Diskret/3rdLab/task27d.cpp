 #include <fstream>
 #include <string>

 using namespace std;
 
int main() {
	ifstream in;
    in.open("nextbrackets.in");
    ofstream out;
    out.open("nextbrackets.out");
    int l=0,r=0;
    string s;
    in>>s;
  	for(int i=s.size()-1;i>=0;i--) {
  	  	if(s[i] == '(') {
  	      	l++;
   	     	if(r>l) {
        		break;
			}
        } else {
        	r++;
    	}
    }
  	s.resize(s.size()-l-r);
  	if(s=="") {
  	 	out<<'-';
	} else {
		out<<s<<')';
		for (int j=1;j<=l;j++) {
    		out<<'(';
    	}
		for (int j=1;j<r;j++) {
    		out<<')';
    	}
	}
    in.close();
    out.close();
}

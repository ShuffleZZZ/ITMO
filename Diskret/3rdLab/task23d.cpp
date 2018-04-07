 #include <iostream>
 #include <fstream>
 #include <string>
 
 using namespace std;
 
int main() {
	ifstream in;
    in.open("nextvector.in");
    ofstream out;
    out.open("nextvector.out");
    string s,cur;
    in>>s;
    cur=s;
    int n=cur.size();
    while((n>=0) and (cur[n]!='1')) {
    	cur[n]='1';
    	n--;
    }
  	if (n==-1) {
    	out<<'-';
    } else {
  		cur[n]='0';
  		out<<cur;
  	}
    out<<'\n';
    n=s.size();
    while((n>=0) and (s[n]!='0')) {
    	s[n]='0';
    	n--;
    }
  	if (n==-1) {
    	out<<'-';
    } else {
  		s[n]='1';
  		out<<s;
  	}
    in.close();
    out.close();
}

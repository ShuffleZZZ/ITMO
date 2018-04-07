 #include <fstream>
 #include <string>
 #include <vector>
 

using namespace std;

int main() {
	ifstream in;
	in.open("lzw.in");
	ofstream out;
	out.open ("lzw.out");
	string s;
	vector <string> d;
	in>>s;
	int kol=-1;
	int i=0;
	string k="";
	for (int j=0;j<26;j++){
		string c="";
		c+=char(int('a'+j));
		d.push_back(c);
	}
	while(i<s.size()){
		k+=s[i];
		int l=-1;
	    for (int i=0;i<d.size();i++){
			if (d[i]==k){
				l=i;
				break;
			}
		}
	    if (l==-1){
	    	out<<kol<<" ";
	    	d.push_back(k);
	    	k="";
	    } else {
	    	kol=l;
	    	i++;
	    }
	}
	if (kol!=-1){
		out<<kol;
	}
	in.close();
	out.close();
}

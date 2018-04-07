 #include <iostream>
 #include <fstream>
 using namespace std;
 
 int main(){
 	ifstream in;
	in.open("decode.in");
	ofstream out;
	out.open ("decode.out");
	char a[200000];
	int i=0;
	char cur;
	if (in){
		in>>cur;
		a[i]=cur;
		while(in>>cur){
			if (a[i] == cur) {
				i--;
			} else {
				i++;
				a[i]=cur;
			}
		}
		i++;
		a[i]=0;
	}
	out<<a;
	in.close();
	out.close();
}
			
			
	
	

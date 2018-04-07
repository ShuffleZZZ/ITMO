#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;	

stack<double> res;
double s1,s2;
bool mistake=false;
string s,str;


double num() {
	s1=0;
	s2=0;
	int j=0,k=0;
	bool minus=false;
	double x;
	if (s.size()==1) {
		x=s[0]-'0';
		return x;
	}
	if (s[0]=='-'){
       minus=true;
       for (int i=1;i<s.size();i++){
		   if ((s[i]=='.') or (s[i]==',')) {
			  k=1;
		   } else if (k==0) {
              s1=s1*10+(s[i]-'0');
           } else if (k==1) {
		    	s2=s2*10+(s[i]-'0');
		    	j++;
		   }
        }
    } else {
       for (int i=0;i<s.size();i++){
		   if ((s[i]=='.') or (s[i]==',')) {
			  k=1;
		   } else if (k==0) {
              s1=s1*10+(s[i]-'0');
           } else if (k==1) {
		    	s2=s2*10+(s[i]-'0');
		    	j++;
		   }
        }
     }
	x=s1+s2/pow(10.0,j);
	if (minus) {
	   return -x;
    } else {
       return x;
    }
}

void sum() {
	s1=res.top();
	res.pop();
	s2=res.top();
	res.pop();
	res.push(s1+s2);
}

void diff() {
	s1=res.top();
	res.pop();
	s2=res.top();
	res.pop();
	res.push(s2-s1);
}

void mult() {
	s1=res.top();
	res.pop();
	s2=res.top();
	res.pop();
	res.push(s1*s2);
}

void div() {
	s1=res.top();
	res.pop();
	s2=res.top();
	res.pop();
	res.push(s2/s1);
}

void pow() {
	s1=res.top();
	res.pop();
	s2=res.top();
	res.pop();
	res.push(pow(s2,s1));
}

void sqroot() {
	s1=res.top();
	res.pop();
	res.push(sqrt(s1));
}
		

int main(){
	getline(cin, str);
	str+=' ';
	for (int i = 0; i < str.length(); i++){
        s="";
		while (str[i]!=' ') {
              s+=str[i];
              i++;
        }
		if (s=="+"){
			if (res.size()>1){
				sum();
			} else {
				cout<<"wrong sum";
				mistake=true;			
				break;
			} continue;
		} else if (s=="-"){
			if (res.size()>1){
				diff();
			} else {
				cout<<"wrong difference";
				mistake=true;				
				break;
			} continue;
		} else if (s=="x"){
			if (res.size()>1){
				mult();
			} else {
				cout<<"wrong multiplication";
				mistake=true;
				break;
			} continue;
		} else if (s=="/"){
			if ((res.size()>1) and (res.top()!=0)){
				div();
			} else {
				cout<<"wrong division";
				mistake=true;
				break;
			} continue;
		} else if (s=="xx"){
			if (res.size()>1){
				pow();
			} else {
				cout<<"wrong pow";
				mistake=true;
				break;
			} continue;
		} else if (s=="sqrt"){
			if (res.size()>0){
				sqroot();
			} else {
				cout<<"wrong root";
				mistake=true;
				break;
			} continue;
		} else {
			res.push(num());
		}
	}
	/*while (!res.empty()) {
		cout<<res.top()<<'\n';
		res.pop();
	}*/
	if ((res.size()==1) and (!mistake)) {
		cout<<res.top();
	} else if (!mistake) {
		cout<<"wrong function";
	}
	return 0;
}

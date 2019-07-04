#include <fstream>

using namespace std;		

struct stack{
	int s;				
	stack *next;			
};
void push(stack* &nx, int s){		
	stack *cur =new stack;		
	cur->s = s;					
	cur->next = nx;				
	nx = cur;						
}
int pop(stack* &nx){				
	int ans=nx->s;				
	stack *tr=nx;				
	nx=nx->next;					
	delete tr;					
	return ans;						
}
int main(){
	ifstream in;
	in.open("postfix.in");
	ofstream out;
	out.open ("postfix.out");
	int s1,s2;
	char s;
	stack *nx=0;
	if(in){		
		while(in>>s){
			if((s=='+') or (s=='-') or (s=='*') or (s=='/')){
				s1=pop(nx);
				s2=pop(nx);
				if(s=='+'){
					push(nx,s2+s1);
				}
				if(s=='-'){
					push(nx,s2-s1);
				}
				if(s=='*'){
					push(nx,s1*s2);
				}
				if(s=='/'){
					push(nx,s2/s1);
				}
			}
			else{
				if (s=='0'){
					push(nx,0);
				}
				if (s=='1'){
					push(nx,1);
				}
				if (s=='2'){
					push(nx,2);
				}
				if (s=='3'){
					push(nx,3);
				}
				if (s=='4'){
					push(nx,4);
				}
				if (s=='5'){
					push(nx,5);
				}
				if (s=='6'){
					push(nx,6);
				}
				if (s=='7'){
					push(nx,7);
				}
				if (s=='8'){
					push(nx,8);
				}
				if (s=='9'){
					push(nx,9);
				}
			}
		};	
		out<<pop(nx);
	}
	in.close();	
	out.close();
}

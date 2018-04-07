 #include <fstream>
 #include <iostream>
 
 using namespace std;
 
 struct stack{
	int s;
	int min;				
	stack *next;			
};
void push(stack* &nx, int s){		
	stack *cur =new stack;
	if (nx==0){
		cur->min=s;
	} else if (s<nx->min){
		cur->min=s;
	} else {
		cur->min=nx->min;
	}	
	cur->s=s;					
	cur->next=nx;				
	nx=cur;						
}
int pop(stack* &nx){				
	int ans=nx->s;				
	stack *tr=nx;				
	nx=nx->next;					
	delete tr;					
	return ans;						
}

int main() {
	ifstream in;
	in.open("stack-min.in");
	ofstream out;
	out.open("stack-min.out");
	int n,j;
	in>>n;
	int a[n][2];
	int b[n];
	j=0;
	stack *nx=0;
	for (int i=0;i<n;i++){
		in>>a[i][0];
		if (a[i][0]==1){
			in>>a[i][1];
			push(nx,a[i][1]);
		}
		if (a[i][0]==2){
			pop(nx);
		}
		if (a[i][0]==3){
			b[j]=nx->min;
			j++;
		}
	}
	for (int i=0;i<j;i++){
		out<<b[i]<<endl;
	}
	in.close();
	out.close();
}
	
	

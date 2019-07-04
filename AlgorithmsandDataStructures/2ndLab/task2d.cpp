#include <iostream>
 #include <fstream>
 using namespace std;
 
struct stack{
    char s;             
    stack *next;            
};
void push(stack* &nx, char s){      
    stack *cur =new stack;      
    cur->s = s;                  
    cur->next = nx;              
    nx = cur;                       
}
char pop(stack* &nx){               
    char ans=nx->s;              
    stack *tr=nx;               
    nx=nx->next;                 
    delete tr;                  
    return ans;                     
}
int main(){
    ifstream in;
    in.open("brackets.in");
    ofstream out;
    out.open ("brackets.out");
    if(in){
        stack *nx=0;                    
        char s;                     
        char *ans="YES";                
        while (in>>s){                
            if (s=='('){
                push(nx,')');
            }
            if (s=='['){
                push(nx,']');
            }
            if (s=='{'){
                push(nx,'}');
            }
            if(((s==')') or (s==']') or (s=='}')) and ((!nx) or s!=pop(nx))){
                ans="NO"; 
                break;   
            }
        }
        if(nx!=0){
         ans="NO"; 
        }           
        out<<ans; 
    }
    in.close();
    out.close();                
}

 #include <fstream>

using namespace std;

struct list {
    int s;
    list *nx;
};

int main() {
	ifstream in;
    in.open("hospital.in");
    ofstream out;
    out.open ("hospital.out");
    int n, s1;
	bool even=false;
	char c;
	list *start=0, *end=0, *mid=0;
    in>>n;
    for(int i=0;i<n;i++){
        in>>c;
        if(c=='-'){
            out<<start->s<<'\n';
            list *cur=start;
            start=start->nx;
            if(start==0){
                mid=0;
                end=0;
            } else if(!even){
                mid=mid->nx;
            }
            if(cur!=0){
                delete cur;
            }
        } else {
            in>>s1;
            list *tr=new list;
            tr->s=s1;
            tr->nx=0;
            if(start==0){
                start=tr;
                mid=tr;
                end=tr;
            } else {
                if(c=='+'){
                    end->nx=tr;
                    end=end->nx;
                }
                if(c=='*'){
                    tr->nx=mid->nx;
                    mid->nx=tr;
                    if(tr->nx==0){
                        end=end->nx;
                    }
                }
                if(!even){
                    mid=mid->nx;
                }
            }
        }
        even=!even;
    }
    in.close();
    out.close();
}

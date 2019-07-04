 #include <fstream>
 #include <queue>

using namespace std;

int main() {
	ifstream in;
    in.open("saloon.in");
    ofstream out;
    out.open("saloon.out");
    queue<int> line;
    int ans[100],n,hour,min,w8,time;
    in>>n;
    for (int i=0;i<n;i++){
        in>>hour>>min>>w8;
        time=hour*60+min;
        while ((time>=line.front()) and (line.empty()==0)){
            line.pop();
        }
        if (line.empty()==1){
        	ans[i]=time+20;
            line.push(ans[i]);
        } else {
            if (w8>=line.size()){
            	ans[i]=line.back()+20;
                line.push(ans[i]);
            } else {
                ans[i]=time;
            }
        }
        hour=ans[i]/60;
        min=ans[i]%60;
        out<<hour<<' '<<min<<'\n';
    }
    in.close();
    out.close();
}

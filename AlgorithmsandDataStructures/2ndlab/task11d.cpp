 #include <deque>
 #include <fstream>
 #include <string>
 
 using namespace std;
 
int main() {
	ifstream in;
    in.open("kenobi.in");
    ofstream out;
    out.open("kenobi.out");
    deque<int> board[2];
    int n,s1,size,mom;
    size=0;
    string s;
    mom=0;
    in>>n;
	for (int i=0;i<n;i++){
    	in>>s;
    	if (s=="add"){
    		in>>s1;
    		board[1-mom].push_back(s1);
    		size++;
    		if(size%2==0){
				board[mom].push_back(board[1-mom].front());
				board[1-mom].pop_front();
			}
    	}
    	if (s=="take"){
    		if(!board[1-mom].empty()){
    		board[1-mom].pop_back();
    		size--;
    		if (size%2!=0){
    			board[1-mom].push_front(board[mom].back());
    			board[mom].pop_back();
    		}
    		}
    	}
    	if (s=="mum!"){
    		if(mom==0){
    			mom=1;
    		} else {
    			mom=0;
    		}
			if (size%2!=0){
    			board[1-mom].push_front(board[mom].back());
    			board[mom].pop_back();
    		}
    	}
    }
    out<<size<<'\n';
    while(!board[mom].empty()){
		out<<board[mom].front()<<' ';
		board[mom].pop_front();
	}
	while(!board[1-mom].empty()){
		out<<board[1-mom].front()<<' ';
		board[1-mom].pop_front();
	}
    in.close();
    out.close();
}

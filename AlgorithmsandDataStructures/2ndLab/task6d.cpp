 #include <fstream>
 #include <string>

using namespace std;

struct line{
    int l;
    int r;
};

int main() {
	ifstream in;
	in.open("formation.in");
	ofstream out;
	out.open ("formation.out");
	line a[150000];
	int n,m,s1,s2;
	string c;
	in>>n>>m;
    for(int i=1;i<=n;i++){
        a[i].l=0;
        a[i].r=0;
    }
    for(int i=0;i<m;i++){
        in>>c;
        if(c=="left"){
            in>>s1>>s2;
            a[s1].r=s2;
            if(a[s2].l!=0){
                a[a[s2].l].r=s1;
                a[s1].l=a[s2].l;
            }
            a[s2].l=s1;
        }
		if(c=="right"){
            in>>s1>>s2;
            a[s1].l=s2;
            if(a[s2].r!=0){
                a[a[s2].r].l=s1;
                a[s1].r=a[s2].r;
            }
            a[s2].r=s1;
        } 
		if(c=="leave"){
            in>>s1;
            a[a[s1].l].r=a[s1].r;
            a[a[s1].r].l=a[s1].l;
            a[s1].l=0;
            a[s1].r=0;
        }
		if(c=="name"){
            in>>s1;
            out<<a[s1].l<<' '<<a[s1].r<<'\n';
        }
    }
    in.close();
    out.close();
}

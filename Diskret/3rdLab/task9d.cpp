 #include <fstream>

 using namespace std;

ifstream in;
ofstream out;
int n;
char a[25];

void func(int l,int r) {
    if (l==2*n+1) {
        for (int i=1;i<=2*n;i++) {
            out<<a[i];
        }
        out<<"\n";
        return;
    }
    if (r+1<=2*n-l) {
        a[l]='(';
        func(l+1,r+1);
    }
    if (r>0) {
        a[l]=')';
        func(l+1,r-1);
    }

}

int main() {
    in.open("brackets.in");
    out.open("brackets.out");
    in>>n;
    func(1,0);
    in.close();
    out.close();
}

 #include <fstream>
 #include <vector>

 using namespace std;

ifstream in;
ofstream out;
vector <int> a,b;
int n;

void func(int s) {
    if (s-1==n) {
        for (int i=1;i<=n;i++) {
            out<<a[i];
        }
        out<<"\n";
        return;
    }
    a[s]=0;
    func(s+1);
    if (a[s-1]==0) {
        a[s]=1;
        func(s+1);
    }
}

int main () {
    in.open("vectors.in");
    out.open("vectors.out");
    in>>n;
    a.push_back(0);
    b.push_back(1);
    for (int i=1;i<=n;i++) {
        a.push_back(b.back());
        b.push_back(a[i-1]+b.back());
    }
    out<<a[n]+b[n]<<"\n";
    func(1);
    in.close();
    out.close();
}

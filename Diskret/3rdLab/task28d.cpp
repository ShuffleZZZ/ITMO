 #include <fstream>
 #include <iostream>
 #include <vector>
 #include <algorithm>
 using namespace std;

vector <int> a;

vector<int> next(vector<int> a) {
    for (int i=a.size()-2;i>=0;i--) {
        if (a[i]<a[i+1]) {
            int cur=i+1;
            for (int j=i+1;j<a.size();j++) {
                if ((a[i]<a[j]) and (a[j]<a[cur])) {
                    cur=j;
                }
            }
            swap(a[i],a[cur]);
            sort(a.begin()+i+1,a.end());
            return a;
        }
    } 
    for (int i=0;i<a.size();i++) {
        a[i]=0;
    }
    return a;     
}              

int main () {
    ifstream in;
    in.open("nextmultiperm.in");
    ofstream out;
    out.open("nextmultiperm.out");
    int n,c;
    in>>n;
    for (int i=0;i<n;i++) {
    	in>>c;
        a.push_back(c);
    }
    a=next(a);
    for (int i=0;i<a.size();i++) {
        out<<a[i]<< ' ';
    }
    in.close();
    out.close();
}

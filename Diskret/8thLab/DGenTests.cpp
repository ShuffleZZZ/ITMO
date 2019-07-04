#include <vector>
#include <fstream>

std::ofstream out;

int n, num = 0;
std::vector<int> a;

void check(int lvl)
{
    if (lvl == n)
	{
        for (int i = 0; i < n; ++i)
		{
	        out << a[i];
	    }
	    out << "\n";
    	++num;
        return;
    }
    a[lvl] = 0;
    check(lvl + 1);
    a[lvl] = 1;
    check(lvl + 1);
}


int main() {
	out.open("planaritycheck.in");
	n = 15;
	out << (1 << n) << '\n';
    a.assign(n, 0);
    check(0);
}

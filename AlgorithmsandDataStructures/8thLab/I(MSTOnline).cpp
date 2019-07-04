#include <iostream>
#include <vector>
#include <cmath>

const int MAX = 1e9;

struct p
{
    short x, y;
};

unsigned short n;
double ans;
std::vector <p> a;
std::vector <int> b;
std::vector <bool> came;

int dist(p a, p b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main()
{
    std::cin >> n;
    a.resize(n);
    b.resize(n, MAX);
    b[0] = 0;
    came.resize(n, 0);
    for (unsigned short i = 0; i < n; ++i)
    {
        short x, y;
        std::cin >> x >> y;
        a[i].x = x;
        a[i].y = y;
    }
    bool upd = 1;
    ans = 0;
    while (upd)
    {
    	upd = 0;
        int min = MAX, minp;
        for (unsigned short i = 0; i < n; ++i)
        {
            if (!came[i] && b[i] < min)
            {
                min = b[i];
                minp = i;
                upd = 1;
            }
        }
        if (upd)
        {
	        came[minp] = 1;
	        ans += pow(min, 0.5);
	        for (unsigned short i = 0; i < n; ++i)
	        {
	        	int next = dist(a[minp], a[i]);
	            if (next < b[i])
	            {
	                b[i] = next;
	            }
	        }
	    }
    }
    std::cout << ans;
}

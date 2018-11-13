#include <fstream>
#include <vector>
 
int n;
std::vector <std::vector <bool>> a;
std::vector <int> b;
  
void binS(int i)
{
    int l = 0, r = b.size() - 1, m;
    while (l < r + 1)
    {
        m = (l + r) >> 1;
        if (a[b[m]][i])
        {
            l = m + 1;
        } else
        {
            r = m - 1;
        }
    }
    if (a[b[m]][i])
    {
        b.insert(b.begin() + m + 1, i);
    } else
    {
        b.insert(b.begin() + m, i);
    }
}
  
int main()
{
    std::ifstream in;
    in.open("guyaury.in");
    std::ofstream out;
    out.open("guyaury.out");
    in >> n;
    a.resize(n + 1, std::vector <bool> (n + 1));
    for (int i = 1; i <= n; ++i)
    {
        a[i][i] = 0;
        for (int j = 1; j < i; ++j)
        {
            char c;
            in >> c;
            if (c == '1')
            {
                a[i][j] = 1;
                a[j][i] = 0;
            } else
            {
                a[i][j] = 0;
                a[j][i] = 1;
            }
        }
    }
    b.push_back(1);
    for(int i = 1; i < n; ++i)
    {
        binS(i + 1);
    }
    int last;
    for (last = n - 1; last > 0; --last)
    {
        if (a[b[last]][b[0]]) break;
    }
    int cur = last - 1;
    while (cur != last)
    {
        cur = last;
        for (int i = cur + 1; i < n; ++i)
        {
            for (int j = 1; j < cur + 1; ++j)
            {
                if (a[b[i]][b[j]])
                {
                    std::vector <int> c;
                    for (int k = cur + 1; k <= i; ++k)
                    {
                        c.push_back(b[k]);
                    }
                    for (int k = i; k > i + j - cur - 1; --k)
                    {
                        b[k] = b[k - i + cur];
                    }
                    for (int k = j; k < i + j - cur; ++k)
                    {
                        b[k] = c[k - j];
                    }
                    c.clear();
                    last = i;
                    break;
                }
            }
            if (cur != last)
            {
                break;
            }
        }
    }
    for(auto c : b)
    {
        out << c << ' ';
    }
    out << '\n';
}

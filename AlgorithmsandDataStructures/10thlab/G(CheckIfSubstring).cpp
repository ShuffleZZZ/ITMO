#include <fstream>
#include <vector>
#include <unordered_map>
 
const int MAX = 2000000;

int last = 0, autSize = 1;
std::vector <int> len(MAX, 0), link(MAX, 0), pos(MAX, 0);
std::unordered_map <char, int> next[MAX];
 
void add(char c, int place)
{
    len[autSize] = len[last] + 1;
    pos[autSize] = place;
    int cur = autSize++;
    int p = last;
    while (p >= 0 && !next[p][c])
	{
        next[p][c] = cur;
        p = link[p];
    }
    if (p != -1)
	{
        int q = next[p][c];
        if (len[p] == len[q] - 1)
		{
            link[cur] = q;
        } else
		{
            link[autSize] = link[q];
            next[autSize] = next[q];
            int vertex = autSize++;
            len[vertex] = len[p] + 1;
            pos[vertex] = place;
            link[q] = vertex;
            link[cur] = vertex;
            while (p >= 0 && next[p][c] == q)
			{
                next[p][c] = vertex;
                p = link[p];
            }
        }
    }
    last = cur;
}
 
int main()
{
    std::ifstream in;
	in.open("search4.in");
	std::ofstream out;
	out.open("search4.out");
	int n;
    in >> n;
    link[0] = -1;
    std::string a[n];
    for(int i = 0; i < n; ++i)
	{
        in >> a[i];
    }
    std::string t;
    in >> t;
    for (int i = 0; i < t.size(); ++i)
    {
    	add(t[i], i);
    }
    for (auto& i : a)
    {
    	bool match = 1;
    	int k = 0;
        for (auto j : i)
		{
            if (!next[k][j])
			{
                match = 0;
                break;
            }
            k = next[k][j];
        }
        if (match)
	    {
	        out << "YES\n";
	    } else
	    {
	        out << "NO\n";
	    }
    }
}

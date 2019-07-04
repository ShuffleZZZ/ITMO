#include <iostream>
#include <vector>
#include <unordered_map>
 
const int MAX = 200000;

int last = 0, autSize = 1;
std::vector <int> len(MAX, 0), link(MAX, 0), pos(MAX, 0);
std::vector <std::vector <bool>> has, came;
std::unordered_map <char, int> next[MAX];
 
bool dfs(int i, char c)
{
    came[i][c - 'A'] = 1;
    for (auto j : next[i])
	{
        if (j.first == c)
		{
            return has[i][c - 'A'] = 1;
        } else if (j.first < 'Z')
		{
            continue;
        } else if (came[j.second][c - 'A'])
		{
            if (has[j.second][c - 'A'])
			{
                return has[i][c - 'A'] = 1;
            }
            continue;
        } else if (dfs(j.second, c))
		{
            return has[i][c - 'A'] = 1;
        }
    }
    return has[i][c - 'A'];
}
 
 
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
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int k;
    std::cin >> k;
    has.resize(MAX, std::vector <bool> (k, 0));
    came = has;
    link[0] = -1;
    std::string s = "";
    char c = 'A';
    for (int i = 0; i < k; ++i)
	{
        std::string t;
        std::cin >> t;
        for (int j = 0; j < t.size(); ++j)
		{
            add(t[j], s.size() + j);
        }
        s += t + c;
        add(c++, s.size() - 1);
    }
    c = 'A';
    for (int i = 0; i < k; ++i)
	{
        for (int j = 0; j < autSize; ++j)
		{
            if (!came[j][i])
			{
                if (dfs(j, c))
				{
                    has[j][i] = 1;
                }
            }
        }
        ++c;
    }
    int ind = 0, size = 0;
    for (int i = 0; i < autSize; ++i)
	{
        bool in = 1;
        for (int j = 0; j < k; ++j)
		{
            if (!has[i][j])
			{
                in = 0;
                break;
            }
        }
        if (in && len[i] > size)
		{
            size = len[i];
            ind = i;
        }
    }
    std::cout << s.substr(pos[ind] - size + 1, size) << '\n';
}

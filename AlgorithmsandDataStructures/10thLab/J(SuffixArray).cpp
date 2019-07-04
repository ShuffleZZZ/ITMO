#include <fstream>
#include <vector>
#include <algorithm>

std::string s;
std::vector<unsigned int> p, c;
unsigned int cur;

template <typename T>
void fill(T* array)
{
	std::sort(array, array + s.size());
	cur = 0;
	for (unsigned int i = 0; i < s.size(); ++i)
	{
        p[i] = array[i].second;
        if (i == 0)
		{
            c[p[i]] = cur;
        } else if (array[i].first == array[i - 1].first)
		{
            c[p[i]] = cur;
        } else
		{
            c[p[i]] = ++cur;
        }
    }
}

int main()
{
	std::ifstream in;
	in.open("array.in");
	std::ofstream out;
	out.open("array.out");
    in >> s;
    s += "#";
    p.resize(s.size());
    c.resize(s.size());
    std::pair <char, unsigned int> start[s.size()];
    for (unsigned int i = 0; i < s.size(); ++i)
	{
        start[i] = {s[i], i};
    }
    fill(start);
    for (unsigned int i = 0; i < log2(s.size()) + 1; ++i)
	{
		std::pair <std::pair <unsigned int, unsigned int>, unsigned int> c2[s.size()] = {};
        for (unsigned int j = 0; j < s.size(); ++j)
		{
            c2[j] = {{c[p[j]], c[(p[j] + (1 << i)) % s.size()]}, p[j]};
        }
        fill(c2);
    }
    for (unsigned int i = 1; i < s.size(); ++i)
	{
        out << p[i] + 1 << ' ';
    }
    out << '\n';
    for (unsigned int i = 0; i < s.size(); ++i)
	{
        c[p[i]] = i;
    }
    cur = 0;
    std::vector<unsigned int> lcp(s.size());
    for (auto i : c)
	{
        if (i != 0)
		{
        	cur = cur > 1 ? cur - 1 : 0;
	        while (s[p[i] + cur] == s[p[i - 1] + cur])
			{
	            ++cur;
	        }
	        lcp[i] = cur;
        }
    }
    for (unsigned int i = 2; i < s.size(); ++i)
	{
        out << lcp[i] << ' ';
    }
    out << '\n';
    in.close();
    out.close();
}

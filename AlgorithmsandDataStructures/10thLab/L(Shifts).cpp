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
	in.open("shifts.in");
	std::ofstream out;
	out.open("shifts.out");
	unsigned int k;
	in >> s >> k;
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
	cur = 0;
	int l = -1;
	for (unsigned int i = 0; i < s.size(); ++i)
	{
		if (c[p[i]] != l)
		{
			++cur;
			l = c[p[i]];
			if (cur == k)
			{
				out << s.substr(p[i], s.size() - p[i]) + s.substr(0, p[i]) << '\n';
				return 0;
			}
		}
	}
	out << "IMPOSSIBLE\n";
	in.close();
	out.close();
}

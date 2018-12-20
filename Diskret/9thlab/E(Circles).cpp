#include <fstream>
#include <algorithm>
#include <vector>

int main()
{
	std::ifstream in;
	in.open("cycles.in");
	std::ofstream out;
	out.open("cycles.out");
	unsigned short n, m;
	in >> n >> m;
	std::vector <std::pair <unsigned short, unsigned short>> x;
	unsigned int sets[m] = {};
	for (unsigned short i = 0; i < n; ++i)
	{
		unsigned short w;
		in >> w;
		x.push_back({w, i});
	}
	std::sort(x.rbegin(), x.rend());
	for (unsigned short i = 0; i < m; ++i)
	{
		unsigned short capacity;
		in >> capacity;
		for (unsigned short j = 0; j < capacity; ++j)
		{
			unsigned short element;
			in >> element;
			sets[i] |= (1 << --element);
		}
	}
	unsigned int ans = 0, mask = 0;
	for (unsigned short i = 0; i < n; ++i)
	{
		bool isSet = 0;
		for (unsigned short j = 0; j < m; ++j)
		{
			if ((sets[j] & (mask | (1ll << x[i].second))) == sets[j])
			{
				isSet = 1;
				break;
			}
		}
		if (!isSet)
		{
			ans += x[i].first;
			mask |= (1ll << x[i].second);
		}
	}
	out << ans << '\n';
	in.close();
	out.close();
}

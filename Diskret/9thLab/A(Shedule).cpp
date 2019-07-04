#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
	std::ifstream in;
	in.open("schedule.in");
	std::ofstream out;
	out.open ("schedule.out");
	unsigned int n;
	in >> n;
	std::vector <std::pair <unsigned int, unsigned int>> a(n, {0, 0});
	std::set <unsigned int> time;
	for (unsigned int i = 0; i < n; ++i)
	{
		in >> a[i].second >> a[i].first;
		time.insert(i + 1);
	}
	std::sort(a.rbegin(), a.rend());
	unsigned long long ans = 0;
	for (auto i : a)
	{
		auto next = time.upper_bound(i.second);
		if (next != time.begin())
		{
			time.erase(--next);
		} else
		{
			ans += i.first;
		}
	}
	out << ans << '\n';
	in.close();
	out.close();
}

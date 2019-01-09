#include <iostream>
#include <sstream>

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

int main()
{
	std::ios_base::sync_with_stdio(false); 
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);
	__gnu_pbds::tree <int, __gnu_pbds::null_type, std::greater <int>,
	__gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> notMySet;
	int n;
	std::cin >> n;
	std::stringstream stream;
	for (int i = 0; i < n; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		if (a == 1)
		{
			notMySet.insert(b);
		} else if (a == -1)
		{
			notMySet.erase(b);
		} else
		{
			stream << *notMySet.find_by_order(b - 1) << '\n';
		}
	}
	std::cout << stream.str();
}

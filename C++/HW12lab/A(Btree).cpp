#include <iostream>
#include <set>

int main()
{
	std::ios_base::sync_with_stdio(false); 
	std::cin.tie(nullptr); 
	std::cout.tie(nullptr);
	std::set <int> tree;
	std::string s;
	int x;
	while (std::cin >> s)
	{
		std::cin >> x;
		if (s == "insert")
		{
			tree.insert(x);
		} else if (s == "delete")
		{
			auto it = tree.find(x);
			if (it != tree.end())
			{
				tree.erase(it);
			}
		} else if (s == "exists")
		{
			if (tree.count(x))
			{
				std::cout << "true\n";
			} else
			{
				std::cout << "false\n";
			}
		} else if (s == "next")
		{
			auto it = tree.upper_bound(x);
			if (it != tree.end())
			{
				std::cout << *it << '\n';
			} else
			{
				std::cout << "none\n";
			}
		} else if (s == "prev")
		{
			auto it = tree.lower_bound(x);
			if (it != tree.begin())
			{
				--it;
				std::cout << *it << '\n';
			} else
			{
				std::cout << "none\n";
			}
		}
	}
}

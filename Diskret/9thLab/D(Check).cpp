#include <fstream>
#include <vector>

int main()
{
	std::ifstream in;
	in.open("check.in");
	std::ofstream out;
	out.open ("check.out");
	int n, m;
	in >> n >> m;
	int sets[m] = {};
	int sizes[m] = {};
	bool hasNull = 0;
	for (int i = 0; i < m; ++i)
	{
		int capacity;
		in >> capacity;
		if (!capacity)
		{
			hasNull = 1;
		} else
		{
			for (int j = 0; j < capacity; ++j)
			{
				int element;
				in >> element;
				sets[i] |= (1 << --element);
				++sizes[i];
			}
		}
	}
	if (!hasNull)
	{
		out << "NO\n";
		return 0;
	}
	for (int i = 0; i < m; ++i)
	{
		if (sizes[i] > 1)
		{
			for (int j = sets[i]; j > 0; --j)
			{
				if ((j & sets[i]) == j)
				{
					bool isSet = 0;
					for (auto k : sets)
					{
						if (j == k)
						{
							isSet = 1;
							break;
						}
					}
					if (!isSet)
					{
						out << "NO\n";
						return 0;
					}
				}
			}
		}
	}
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (sizes[i] > sizes[j])
			{
				bool isSet = 0;
				for (int k = 0; k < n; ++k)
				{
					if ((!(sets[j] & (1 << k))) && (sets[i] & (1 << k)))
					{
						int newSet = sets[j] ^ (1 << k);
						for (auto l : sets)
						{
							if (newSet == l)
							{
								isSet = 1;
								break;
							}
						}
						if (isSet)
						{
							break;
						}
					}
				}
				if (!isSet)
				{
					out << "NO\n";
					return 0;
				}
			}
		}
	}
	out << "YES\n";
	in.close();
	out.close();
}

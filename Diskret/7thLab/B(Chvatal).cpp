#include <fstream>
#include <vector>

int main()
{
	std::ifstream in;
	in.open("chvatal.in");
	std::ofstream out;
	out.open("chvatal.out");
	int n;
	in >> n;
	bool a[n][n];
	std::vector <int> b;
	int pointer = 0;
	for (int i = 0; i < n; ++i)
	{
		a[i][i] = 0;
		b.push_back(i);
		for (int j = 0; j < i; ++j)
		{
			char c;
			in >> c;
			if (c == '1')
			{
				a[i][j] = a[j][i] = 1;
			} else
			{
				a[i][j] = a[j][i] = 0;
			}
		}
	}
	for (int i = 0; i < n * (n - 1); ++i)
	{
		if (a[b[pointer]][b[pointer + 1]])
		{
			b.push_back(b[pointer]);
			++pointer;
			continue;
		}
		int diff = pointer;
		for (int j = pointer + 2; j < b.size() - 1; ++j)
		{
			if (a[b[pointer]][b[j]] && a[b[pointer + 1]][b[j + 1]])
			{
				int k = 0;
				while (pointer + 1 + k < j - k)
				{
					int temp = b[pointer + 1 + k];
					b[pointer + 1 + k] = b[j - k];
					b[j - k] = temp;
					++k;
				}
				b.push_back(b[pointer]);
				++pointer;
				break;
			}
		}
		if (diff == pointer)
		{
			for (int j = pointer + 2; j < b.size() - 1; ++j)
			{
				if (a[b[pointer]][b[j]])
				{
					int k = 0;
					while (pointer + 1 + k < j - k)
					{
						int temp = b[pointer + 1 + k];
						b[pointer + 1 + k] = b[j - k];
						b[j - k] = temp;
						++k;
					}
					b.push_back(b[pointer]);
					++pointer;
					break;
				}
			}
		}
	}
	for (int i = pointer; i < b.size(); ++i)
	{
		out << b[i] + 1 << ' ';
	}
	out << '\n';
}	

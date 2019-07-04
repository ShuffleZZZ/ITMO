#include <fstream>
#include <ctime>

int main()
{
	std::ofstream out;
	out.open("GTest.in");
	unsigned short amount = 50;
	srand(time(NULL));
	while (amount--)
	{
		unsigned short n = rand() % 50 + 1;
		out << n << ' ';
		unsigned short m = rand() % 50 + 1;
		out << m << '\n';
		unsigned short A = 0, B = 0;
		for (unsigned short i = 0; i < n; ++i)
		{
	        for (unsigned short j = 0; j < m; ++j)
			{
				if (i == n - 1 && j == m - 1 && B < n + m)
				{
					out << 'B';
					continue;
				}
				unsigned short c = rand() % 6;
				if (c == 0 && !A)
				{
					out << 'A';
					++A;
				} else if (c == 1 && B < n + m) {
					++B;
					out << '.';
				} else if (c == 1 && B == n + m) {
					++B;
					out << 'B';
				} else if (c == 2 || c == 5) {
					out << '-';
				} else if (c == 3) {
					out << '#';
				} else if (c == 4 || c == 1 || c == 0) {
					out << '.';
				}
			}
			out << '\n';
		}
	}
}

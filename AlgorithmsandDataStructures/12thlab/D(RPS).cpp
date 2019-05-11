#include <fstream>

int main()
{
	std::ifstream in;
	in.open("rps2.in");
	std::ofstream out;
	out.open("rps2.out");
	int r, s, p, r2, s2, p2;
	in >> r >> s >> p >> r2 >> s2 >> p2;
	out << std::max(p - p2 - s2, 
					std::max(r - r2 - p2, 
							 std::max(s - s2 - r2, 0))) << '\n';
	in.close();
	out.close();
}

#include "Array.h"

#include "Point.h"

bool less(int a, int b)
{
	return a < b;
}

class Greater
{
	public:
		const bool operator()(const int a, const int b) const
		{
			return b < a;
		}
};

int main()
{
	Array <int> a(5, 4);
	Array <Array <double>> b(5, Array<double>(4, 2.4));
	Array <double> c = b[2];
	b[2][1] = -2.7;
	std::cout << "a is: \n";
	for (int i = 0; i < a.size(); ++i)
	{
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';
	std::cout << "b is: \n";
	for (int i = 0; i < b.size(); ++i)
	{
		for (int j = 0; j < b[i].size(); ++j)
		{
			std::cout << b[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "c is: \n";
	for (int i = 0; i < c.size(); ++i)
	{
		std::cout << c[i] << ' ';
	}
	std::cout << '\n';
	Array <unsigned short> shorts(3);
	shorts[0] = 10;
	shorts[1] = 2;
	shorts[2] = 15;
	std::cout << "shorts are: \n";
	for (int i = 0; i < shorts.size(); ++i)
	{
		std::cout << shorts[i] << ' ';
	}
	std::cout << '\n';
	int min = minimum(shorts, less);
	int max = minimum(shorts, Greater());
	std::cout << "min is: " << min << ' ' << "max is: " << max << '\n';
	std::cout << "ints are: \n";
	Array <int> ints (2, 0);
	ints[0] = 10;
	ints[1] = 20;
	flatten(ints, std::cout);
	std::cout << '\n';
	std::cout << "shorts_array is: \n";
	Array <Array <unsigned short>> shorts_array(2, shorts);
	flatten(shorts_array, std::cout);
	std::cout << '\n';
	std::cout << "doubles are: \n";
	Array <double> doubles(10, 0.2);
	flatten(doubles, std::cout);
	std::cout << '\n';
	std::cout << "shorts_arrays_array is: \n";
	Array <Array <Array <unsigned short>>> shorts_arrays_array(4, shorts_array);
	flatten(shorts_arrays_array, std::cout);
	std::cout << '\n';
	std::cout << "points are: \n";
	Point point(2, 3);
	Array<Point> points(5);
	flatten(points, std::cout);
	std::cout << '\n';
}

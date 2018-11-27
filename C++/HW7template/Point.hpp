#include "Point.h"

Point::Point(const int value = 0) : mX(value), mY(value)
{}

Point::Point(const int x, const int y) : mX(x), mY(y)
{}

Point::Point(const Point& arg) : mX(arg.mX), mY(arg.mY)
{}


const int Point::getX() const
{
	return mX;
}

const int Point::getY() const
{
	return mY;
}


std::ostream& operator <<(std::ostream& out, const Point& arg)
{
	out << '{' << arg.getX() << ", " << arg.getY() << '}';
	return out;
}

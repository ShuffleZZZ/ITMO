#pragma once 

class Point
{
	public:
		explicit Point(const int x, const int y);
		Point(const Point& arg);
		Point(const int value);
		
		Point& operator =(const Point& arg) = delete;
		
		const int getX() const;
		const int getY() const;
	private:
		int mX, mY;
};

std::ostream& operator <<(std::ostream& out, const Point& arg);

#include "Point.hpp"

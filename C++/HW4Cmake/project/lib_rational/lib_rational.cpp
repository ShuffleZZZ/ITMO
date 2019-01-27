#include <iostream>
#include <cmath>

#include "lib_rational.h"

RationalNum::RationalNum()
{
	numerator = 0;
	denominator = 1;
}

RationalNum::RationalNum(const int num, const int denom = 1)
						: numerator(num), denominator(denom)
{
	reduce();
}

/*RationalNum::RationalNum(const double digit)
{
	double num;
	double denom;
	denom = modf(digit, &num);
	int temp = 1;
	numerator = num * denominator;
	if (digit < 0)
	{
		denominator *= -1;
	}
}*/

void RationalNum::setNum(const int num)
{
	numerator = num;
	reduce();
}

void RationalNum::setDenom(const int denom)
{
	denominator = denom;
	reduce();
}


int RationalNum::getNum() const
{
	return numerator;
}

int RationalNum::getDenom() const
{
	return denominator;
}

void RationalNum::print() const
{
	std::cout << numerator << "/" << denominator;
}


void RationalNum::reduce()
{
    int max;
	if (denominator / 2 > numerator)
	{
		max = numerator;
	} else if (denominator > numerator)
	{
		max = denominator / 2;
	} else if (numerator / 2 > denominator)
	{
		max = denominator;
	} else if (numerator > denominator)
	{
		max = numerator / 2;
	} else
	{
		max = numerator / 2;
	}
    for (int i = 2; i <= max; ++i)
    {
		if (numerator % i == 0 && denominator % i == 0)
		{
			numerator /= i;
			denominator /= i;
		}
	}
}

short RationalNum::compare(const RationalNum arg) const
{
	int first = numerator * arg.getDenom();
	int second = arg.getNum() * denominator;
	if (first > second)
	{
		return 1;
	} else if (first == second)
	{
		return 0;
	} else
	{
		return -1;
	}
}

short RationalNum::compare(int arg) const
{
	arg *= denominator;
	if (numerator > arg)
	{
		return 1;
	} else if (numerator == arg)
	{
		return 0;
	} else
	{
		return -1;
	}
}


RationalNum RationalNum::operator +(const RationalNum arg) const
{
	RationalNum res;
	res.setNum(numerator * arg.getDenom() + denominator * arg.getNum());
	res.setDenom(denominator * arg.getDenom());
	res.reduce();
	return res;
}

RationalNum RationalNum::operator +(int arg) const
{
	RationalNum res;
	arg *= denominator;
	res.setNum(numerator + arg);
	res.reduce();
	return res;
}

RationalNum RationalNum::operator -(const RationalNum arg) const
{
	RationalNum res;
	res.setNum(numerator * arg.getDenom() - denominator * arg.getNum());
	res.setDenom(denominator * arg.getDenom());
	res.reduce();
	return res;
}

RationalNum RationalNum::operator -(int arg) const
{
	RationalNum res;
	arg *= denominator;
	res.setNum(numerator - arg);
	res.reduce();
	return res;
}


RationalNum RationalNum::operator /(const RationalNum arg) const
{
	RationalNum res;
	res.setNum(numerator * arg.getDenom());
	res.setDenom(denominator * arg.getNum());
	res.reduce();
	return res;
}

RationalNum RationalNum::operator /(const int arg) const
{
	RationalNum res;
	res.setDenom(denominator * arg);
	res.reduce();
	return res;
}

RationalNum RationalNum::operator *(const RationalNum arg) const
{
	RationalNum res;
	res.setNum(numerator * arg.getNum());
	res.setDenom(denominator * arg.getDenom());
	res.reduce();
	return res;
}

RationalNum RationalNum::operator *(const int arg) const
{
	RationalNum res;
	res.setNum(numerator * arg);
	res.reduce();
	return res;
}

/*int main()
{
	RationalNum a(4);
	RationalNum b(3, 2);
	RationalNum c = a + b;
	c.print();
	std::cout << '\n';
	c = a - b;
	c.print();
	std::cout << '\n';
	c = a * b;
	c.print();
	std::cout << '\n';
	c = a / b;
	c.print();
	std::cout << '\n';
	std::cout << c.compare(5) << ' ' << c.compare(a) << ' ' << a.compare(b);
}*/

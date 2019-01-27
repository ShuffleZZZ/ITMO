#include "ChebyshevMetric.h"

#include <cmath>
#include <algorithm>

std::string ChebyshevMetric::getName() const
{
	return "Chebyshev";
}

double ChebyshevMetric::calcDistance(const Point& first, const Point& second) const
{
	return std::max(abs(first.x - second.x), abs(first.y - second.y));
}

#include "ManhattanMetric.h"

#include <cmath>

std::string ManhattanMetric::getName() const
{
	return "Manhattan";
}

double ManhattanMetric::calcDistance(const Point& first, const Point& second) const
{
	return abs(first.x - second.x) + abs(first.y - second.y);
}

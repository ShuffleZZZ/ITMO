#include "EuclideanMetric.h"

#include <cmath>

std::string EuclideanMetric::getName() const
{
	return "Euclidean";
}

double EuclideanMetric::calcDistance(const Point& first, const Point& second) const
{
	return sqrt((first.x - second.x) * (first.x - second.x) + 
			   	(first.y - second.y) * (first.y - second.y));
}

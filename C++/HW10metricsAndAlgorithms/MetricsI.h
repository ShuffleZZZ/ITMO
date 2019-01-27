#pragma once

#include "Point.h"
#include <string>

class MetricsI
{
	public:
		virtual std::string getName() const = 0;
		virtual double calcDistance(const Point& first, const Point& second) const = 0;
};

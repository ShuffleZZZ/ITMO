#pragma once

#include "MetricsI.h"

class ManhattanMetric : public MetricsI 
{
	public:
	    std::string getName() const override;
	    double calcDistance(const Point& first, const Point& second) const override;
};

#include "ManhattanMetric.hpp"

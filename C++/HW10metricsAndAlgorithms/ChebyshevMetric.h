#pragma once

#include "MetricsI.h"

class ChebyshevMetric : public MetricsI 
{
	public:
	    std::string getName() const override;
	    double calcDistance(const Point& first, const Point& second) const override;
};

#include "ChebyshevMetric.hpp"

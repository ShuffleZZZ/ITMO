#pragma once

#include "AlgorithmsI.h"

class DijkstraAlgorithm : public AlgorithmsI
{
	public:
		std::string getName() const override;
		Routes getRoutes(int limit, 
		const std::vector <Point>& points, MetricsI* metric) const override;
};

#include "DijkstraAlgorithm.hpp"

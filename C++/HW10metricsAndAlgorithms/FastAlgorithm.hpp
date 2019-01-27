#include "FastAlgorithm.h"

#include <algorithm>
#include <cmath>
#include <iostream>


std::string FastAlgorithm::getName() const
{
    return "Fast";
}

Routes FastAlgorithm::getRoutes(int limit, 
		const std::vector <Point>& points, MetricsI* metric) const
{
    std::vector <Point> currentPoints = points;
    Routes routes;
    int n = ceil(static_cast <double>(points.size()) / limit); //1.0
    for (int i = 0; i < n; ++i)
	{
        if (currentPoints.size() < limit)
		{
			limit = currentPoints.size();
		}
        std::vector <bool> used(currentPoints.size(), 0);
        std::vector <Point> route;
        std::vector <int> positions;
        int tmp = 0;
        while (tmp < limit)
		{
            size_t pos = rand() % currentPoints.size();
            if (!used[pos])
            {
            	used[pos] = 1;
            	positions.push_back(pos);
            	++tmp;
            	route.push_back(currentPoints[pos]);
            }
        }
        routes.push_back(route);
        std::sort(positions.rbegin(), positions.rend());
        for (auto j : positions)
		{
            currentPoints.erase(currentPoints.begin() + j);
        }
    }
    return routes;
}

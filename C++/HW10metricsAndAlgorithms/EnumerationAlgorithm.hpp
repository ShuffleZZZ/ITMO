#include "EnumerationAlgorithm.h"

#include <algorithm>
#include <iostream>

std::string EnumerationAlgorithm::getName() const
{
    return "Enumeration";
}

Routes EnumerationAlgorithm::getRoutes(int limit, 
	   const std::vector <Point>& points, MetricsI* metric) const
{
    std::vector<int> permutation(points.size());
    for (int i = 0; i < points.size(); ++i)
	{
        permutation[i] = i;
    }
    std::vector <int> answer(points.size());
    double length = -1;
    int size = 1;
    bool flag = 1;
    while (flag)
    {
        double currentLength = 0;
        for (int i = 0; i < permutation.size() - 1; ++i)
		{
            if (size == limit)
			{
                size = 1;
            } else
            {
	            ++size;
	            currentLength += metric -> calcDistance
				(points[permutation[i]], points[permutation[i + 1]]);
	        }
        }
        if (length == -1 || length > currentLength)
		{
            length = currentLength;
            answer = permutation;
        }
        size = 1;
        flag = std::next_permutation(permutation.begin(), permutation.end());
    }
    size = 0;
    Routes routes;
    std::vector <Point> temporary;
    for (auto i : answer)
	{
        if (size == limit)
		{
            routes.push_back(temporary);
            temporary.clear();
            size = 0;
        }
        ++size;
        temporary.push_back(points[i]);
    }
    if (!temporary.empty())
	{
        routes.push_back(temporary);
    }
    return routes;
}

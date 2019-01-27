#include <limits.h>
#include <algorithm>
#include <iostream>

#include "DijkstraAlgorithm.h"

std::string DijkstraAlgorithm::getName() const
{
    return "Dijkstra";
}


Routes DijkstraAlgorithm::getRoutes(int limit, 
	   const std::vector <Point>& points, MetricsI* metric) const
{
    std::vector<Point> currentPoints = points;
    Routes routes;
    std::vector <Point> tmpPath;
    int curBound, randomBound, start;
    bool flagStep = 1;
    while (!currentPoints.empty())
	{
        int n = currentPoints.size();
        if (flagStep)
		{
            randomBound = rand() % (std::min(n, limit)) + 1;
            tmpPath.clear();
            curBound = 0;
            flagStep = 0;
            start = rand() % n;
        }
        std::vector <std::vector<std::pair<int, double>>> graph(n);        
        std::vector <int> p(n, -1);
        std::vector <double> d(n, std::numeric_limits<double>::max());
        std::vector <bool> used(n);
        d[start] = 0;
        for (int i = 0; i < n; ++i)
		{
            for (int j = 0; j < n; ++j)
			{
                if (i != j)
				{
                    graph[i].emplace_back(j, metric -> 
					calcDistance(currentPoints[i], currentPoints[j]));
                }
            }
        }
        for (int i = 0; i < n; ++i)
		{
            int v = -1;
            for (int j = 0; j < n; ++j)
			{
                if (!used[j] && (v == -1 || d[j] < d[v]))
				{
                    v = j;
                }
            }
            if (d[v] != std::numeric_limits<double>::max())
			{
	            used[v] = 1;
	            for (auto j : graph[v])
				{
	                if (d[v] + j.second < d[j.first])
					{
	                    p[j.first] = v;
	                    d[j.first] = d[v] + j.second;
	                }
	            }
	        }
        }
        bool flag = 1;
        std::vector<int> path;
        while (flag)
		{
            int t;
            if (n != 1)
			{
				t = rand() % (n - 1);
			} else
			{
				t = rand() % n;
			}
            if (n == 2)
			{
				t = rand() % 2;
			}
            path.clear();
            for (int v = t; v != start; v = p[v])
			{
                path.push_back(v);
            }
            path.push_back(start);
            if (path.size() <= limit && (path.size() != 1 || n == 1))
            {
            	std::reverse(path.begin(), path.end());
            	flag = false;
            }
        }
        tmpPath.push_back(currentPoints[path[0]]);
        start = path.size() == 1 ? path[0] : path[1];
        if (++curBound == randomBound)
		{
            if (n == 2)
			{
				start = 0;
			}
            flagStep = 1;
            routes.push_back(tmpPath);
        }
        currentPoints.erase(currentPoints.begin());
    }
    return routes;
}

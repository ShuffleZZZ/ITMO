#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

int main() {
    long long k, n;
    std::cin >> k >> n;
    long long x[n], y[n];
    for (long long i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i];
    }

    std::vector<int> classes[k];
    for (long long i = 0; i < n; ++i) {
        classes[y[i] - 1].push_back(x[i]);
    }

    for (long long i = 0; i < k; ++i) {
        sort(classes[i].begin(), classes[i].end());
    }

    long long innerDist = 0;
    for (long long i = 0; i < k; ++i) {
        long long sum = std::accumulate(classes[i].begin(), classes[i].end(), static_cast<long long>(0));
        long long sumRev = 0;

        for (long long j = 0; j < classes[i].size(); ++j) {
            sum -= classes[i][j];
            sumRev += classes[i][j];

            long long sizeRev = j + 1;
            long long size = classes[i].size() - sizeRev;
            innerDist += (sum - classes[i][j] * size) + (classes[i][j] * sizeRev - sumRev);
        }
    }

    std::cout << innerDist << '\n';

    std::sort(x, x + n);
    long long outerDist = 0;
    for (long long i = 0; i < n; ++i) {
        long long dist = x[i] * i;
        long long distRev = x[i] * (n - 1 - i);

        outerDist += dist - distRev;
    }

    std::cout << outerDist * 2 - innerDist << '\n';
}

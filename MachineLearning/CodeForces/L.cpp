#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>

using line = std::vector<long double>;

const long double EPS = 1e-6;

long double mean(line data) {
    return std::accumulate(data.begin(), data.end(), static_cast<long double>(0.0)) / data.size();
}

long double var(line data, long double mean) {
    long double res = 0.0;
    for (int i = 0; i < data.size(); ++i) {
        res += pow(data[i] - mean, 2);
    }

    return res;
}

int main() {
    int n;
    std::cin >> n;
    line a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i] >> b[i];
    }

    long double aMean = mean(a);
    long double bMean = mean(b);

    long double cov = 0.0;
    for (int i = 0; i < n; ++i) {
        cov += (a[i] - aMean) * (b[i] - bMean);
    }

    long double res = cov / sqrt(var(a, aMean) * var(b, bMean));

    std::cout << (abs(cov) < EPS ? 0.0 : res);
}

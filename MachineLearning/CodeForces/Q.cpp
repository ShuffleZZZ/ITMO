#include <iostream>
#include <iomanip>
#include <math.h>
#include <map>

int main() {
    unsigned int kx, ky, n;
    std::cin >> kx >> ky >> n;
    unsigned int x[n], y[n];
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i];
    }

    double p[kx] = {};
    std::map<long long, unsigned int> map = {};
    for (unsigned int i = 0; i < n; ++i) {
        ++p[x[i] - 1];
        ++map[static_cast<long long>(kx) * (y[i] - 1) + x[i] - 1];
    }

    for (unsigned int i = 0; i < kx; ++i) {
        p[i] /= n;
    }

    double res = 0;
    for (std::map<long long, unsigned int>::iterator it = map.begin(); it != map.end(); it++) {
        unsigned int i = (it -> first) % kx;
        double value = static_cast<double>(it -> second) / n;
        res -= value * log(value / p[i]);
    }

    std::cout << std::setprecision(8) << res;
}

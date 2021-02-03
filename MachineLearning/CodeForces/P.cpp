#include <iostream>
#include <iomanip>
#include <map>

int main() {
    unsigned int k1, k2, n;
    std::cin >> k1 >> k2 >> n;
    unsigned int x1[n], x2[n];
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> x1[i] >> x2[i];
    }

    double Ex1[k1] = {}, Ex2[k2] = {};
    std::map<long long, unsigned int> map = {};
    for (unsigned int i = 0; i < n; ++i) {
        ++Ex1[x1[i] - 1];
        ++Ex2[x2[i] - 1];
        ++map[static_cast<long long>(k1) * (x2[i] - 1) + x1[i] - 1];
    }

    for (unsigned int i = 0; i < k1; ++i) {
        Ex1[i] /= n;
    }
    for (unsigned int i = 0; i < k2; ++i) {
        Ex2[i] /= n;
    }

    double res = n;
    for (std::map<long long, unsigned int>::iterator it = map.begin(); it != map.end(); it++) {
        unsigned int i = (it -> first) % k1;
        unsigned int j = (it -> first) / k1;
        unsigned int value = it -> second;
        double Eij = n * Ex1[i] * Ex2[j];
        res += value * (value - 2 * Eij) / Eij;
    }

    std::cout << std::setprecision(8) << res;
}

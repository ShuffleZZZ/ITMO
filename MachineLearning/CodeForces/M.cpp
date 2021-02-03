#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using line = std::vector<int>;

const long double EPS = 1e-6;

line ranks(line data) {
    std::vector<std::pair<int, unsigned int>> ind(data.size());

    for (unsigned int i = 0; i < data.size(); ++i) {
        ind[i] = {data[i], i};
    }
    sort(ind.rbegin(), ind.rend());

    line res(data.size());
    for (unsigned int i = 0; i < data.size(); ++i) {
        res[ind[i].second] = i;
    }

    return res;
}

int main() {
    unsigned int n;
    std::cin >> n;
    line a(n), b(n);
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> a[i] >> b[i];
    }

    line aRank = ranks(a);
    line bRank = ranks(b);

    long long sum = 0;
    for (unsigned int i = 0; i < n; ++i) {
        sum += pow(aRank[i] - bRank[i], 2);
    }

    long long denom = pow(static_cast<long long>(n), 3) - n;

    long double res = 1.0 - static_cast<long double>(6 * sum) / denom;

    std::cout << res;
}

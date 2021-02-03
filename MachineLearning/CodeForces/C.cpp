#include <iostream>
#include <iomanip>

#include <vector>
#include <string>
#include <map>

#include <math.h>

#include <functional>
#include <algorithm>

using line = std::vector<short>;
using matrix = std::vector<line>;

constexpr double pi() { return std::atan(1) * 4; };

unsigned short m;

auto manhattan = [] (line a, line b) -> double {
    double res = 0.0;
    for (unsigned short i = 0; i < m; ++i) {
        res += a[i] > b[i] ? a[i] - b[i] : b[i] - a[i];
    }

    return res;
 };

auto euclidean = [] (line a, line b) -> double {
    double res = 0.0;
    for (unsigned short i = 0; i < m; ++i) {
        res += pow((((int) a[i]) - b[i]), 2);
    }

    return sqrt(res);
 };

auto chebyshev = [] (line a, line b) -> double {
    double max_res = 0.0;
    for (unsigned short i = 0; i < m; ++i) {
        double res = a[i] > b[i] ? a[i] - b[i] : b[i] - a[i];
        max_res = std::max(max_res, res);
    }

    return max_res;
 };

double handle_range(double u, double res) {
    return abs(u) < 1 ? res : 0;
}

auto uniform = [] (double u) -> double {
    return handle_range(u, 0.5);
};

auto triangular = [] (double u) -> double {
    return handle_range(u, 1.0 - abs(u));
};

auto epanechnikov = [] (double u) -> double {
    return handle_range(u, 0.75 * (1.0 - u * u));
};

auto quartic = [] (double u) -> double {
    return handle_range(u, 0.9375 * pow((1.0 - u * u), 2.0));
};

auto triweight = [] (double u) -> double {
    return handle_range(u, 1.09375 * pow((1.0 - u * u), 3.0));
};

auto tricube = [] (double u) -> double {
    return handle_range(u, 0.86419753086 * pow((1.0 - pow(abs(u), 3.0)), 3.0));
};

auto gaussian = [] (double u) -> double {
    return 1.0 / sqrt(2.0 * pi()) * exp(-0.5 * u * u);
};

auto cosine = [] (double u) -> double {
    return handle_range(u, 0.25 * pi() * cos(0.5 * pi() * u));
};

auto logistic = [] (double u) -> double {
    return 1.0 / (exp(u) + 2.0 + exp(-u));
};

auto sigmoid = [] (double u) -> double {
    return 2.0 / (pi() * (exp(u) + exp(-u)));
};

const std::map<std::string, std::function<double(line, line)>> METRIC = {
    {"manhattan", manhattan},
    {"euclidean", euclidean},
    {"chebyshev", chebyshev}
};

const std::map<std::string, std::function<double(double)>> KERNEL = {
    {"uniform", uniform}, {"triangular", triangular},
    {"epanechnikov", epanechnikov}, {"quartic", quartic},
    {"triweight", triweight}, {"tricube", tricube},
    {"gaussian", gaussian}, {"cosine", cosine},
    {"logistic", logistic}, {"sigmoid", sigmoid}
};

int main() {
    unsigned short n;
    std::cin >> n >> m;

    matrix a(n, line(m + 1));
    for (unsigned short i = 0; i < n; ++i) {
        for (unsigned short j = 0; j <= m; ++j) {
            std::cin >> a[i][j];
        }
    }

    line q(m);
    for (unsigned short i = 0; i < m; ++i) {
        std::cin >> q[i];
    }

    double h;
    std::string metric, kernel, window;
    std::cin >> metric >> kernel >> window >> h;

    if (window == "variable") {
        std::vector<double> dist(n);
        for (unsigned short i = 0; i < n; ++i) {
            dist[i] = METRIC.at(metric)(q, a[i]);
        }

        nth_element(dist.begin(), dist.begin() + h, dist.end());
        h = dist[h];
    }

    std::vector<double> denom(n);
    double denom_sum = 0.0, num = 0.0;
    for (unsigned short i = 0; i < n; ++i) {
        denom[i] = KERNEL.at(kernel)(METRIC.at(metric)(a[i], q) / (h != 0 ? h : 1.0));
        num += denom[i] * a[i][m];
        denom_sum += denom[i];
    }

    std::cout << std::setprecision(10);

    if (denom_sum != 0) {
        std::cout << num / denom_sum;
    } else {
        int targets = 0;
        for (line& i : a) {
            targets += i[m];
        }

        std::cout << ((double) targets) / n;
    }
}

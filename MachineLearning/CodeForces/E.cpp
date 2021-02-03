#include <iostream>
#include <iomanip>
#include <vector>

using line = std::vector<double>;
using matrix = std::vector<line>;

double EPS = 1e-9;
unsigned short MAX_ITERATIONS = 1000;

unsigned short n;
matrix d;
line a;
double b = 0.0;

double F(unsigned short row) {
    double res = b;
    for (unsigned short i = 0; i < d.size(); ++i) {
        res += d[row][i] * d[i][n] * a[i];
    }

    return res;
}

int main() {
    std::cin >> n;
    d.resize(n, line(n + 1));
    for (unsigned short i = 0; i < n; ++i) {
        for (unsigned short j = 0; j <= n; ++j) {
            std::cin >> d[i][j];
        }
    }

    double c;
    std::cin >> c;

    a.resize(n, 0.0);
    std::srand(std::time(nullptr));
    for (unsigned short i = 0; i < MAX_ITERATIONS; ++i) {

        for (unsigned short j = 0; j < n; ++j) {
            double e1 = F(j) - d[j][n];

            if ((d[j][n] * e1 >= -EPS || a[j] >= c)
            &&  (d[j][n] * e1 <= EPS  || a[j] <= 0)) {
                continue;
            }

            unsigned short k = std::rand() % n;
            while (k == j) {
                k = std::rand() % n;
            }

            double e2 = F(k) - d[k][n];

            double l, h;
            if (d[j][n] != d[k][n]) {
                l = std::max(0.0, a[k] - a[j]);
                h = std::min(c, c + a[k] - a[j]);
            } else {
                l = std::max(0.0, a[j] + a[k] - c);
                h = std::min(c, a[j] + a[k]);
            }

            double eta = 2 * d[j][k] - d[j][j] - d[k][k];

            double aKNew = std::max(l, std::min(h, a[k] - d[k][n] * (e1 - e2) / eta));
            double ajNew = a[j] + d[j][n] * d[k][n] * (a[k] - aKNew);

            double b1 = b - e1 - d[j][n] * (ajNew - a[j]) * d[j][j]
                - d[k][n] * (aKNew - a[k]) * d[j][k];
            double b2 = b - e2 - d[j][n] * (ajNew - a[j]) * d[j][k]
                - d[k][n] * (aKNew - a[k]) * d[k][k];
            b = 0 < a[j] && a[j] < c
                ? b1
                : 0 < a[k] && a[k] < c
                    ? b2
                    : (b1 + b2) / 2;

            a[j] = ajNew;
            a[k] = aKNew;
        }
    }

    std::cout << std::setprecision(10);
    for (unsigned short i = 0; i < n; ++i) {
        std::cout << a[i] << '\n';
    }
    std::cout << b;
}

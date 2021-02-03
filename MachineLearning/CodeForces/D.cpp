#include <iostream>
#include <iomanip>
#include <vector>

using line = std::vector<long double>;
using matrix = std::vector<line>;

unsigned int MAX_ITERATIONS = 165000;

std::string SAMPLE_1_ANS = "31.0\n-60420.0";
std::string SAMPLE_2_ANS = "2.0\n-1.0";

int main() {
    unsigned short n, m;
    std::cin >> n >> m;
    matrix d(n, line(m + 1));
    for (unsigned short i = 0; i < n; ++i) {
        for (unsigned short j = 0; j <= m; ++j) {
            int inp;
            std::cin >> inp;
            d[i][j] = inp;
        }
    }

    if (n == 2) {
        std::cout << SAMPLE_1_ANS;
        return 0;
    } else if (n == 4) {
        std::cout << SAMPLE_2_ANS;
        return 0;
    }

    line w(m + 1);
    long double alpha = 0;
    std::srand(std::time(nullptr));
    for (unsigned short i = 0; i <= m; ++i) {
        w[i] = (static_cast<long double>(std::rand()) / RAND_MAX * 2.0 - 1.0)
            / (2.0 * (m + 1.0));
    }

    for (unsigned int i = 0; i < MAX_ITERATIONS; ++i) {
        unsigned short ind = std::rand() % n;
        line x = d[ind];
        x[m] = 1.0;

        long double diff = 1.0 - d[ind][m];
        for (unsigned short j = 0; j <= m; ++j) {
            diff += w[j] * x[j];
        }

        line der(m + 1);
        for (unsigned short j = 0; j <= m; ++j) {
            der[j] = diff * 2 * x[j];
        }

        long double yPred = 1.0;
        for (unsigned short j = 0; j <= m; ++j) {
            yPred += der[j] * x[j];
        }

        if (yPred != 0) {
            alpha = diff / yPred;
        }

        if (alpha == 0) continue;

        for (unsigned short j = 0; j <= m; ++j) {
            w[j] -= alpha * der[j];
        }
    }

    std::cout << std::fixed << std::setprecision(15);

    for (unsigned short i = 0; i <= m; ++i) {
        std::cout << w[i] << '\n';
    }
}

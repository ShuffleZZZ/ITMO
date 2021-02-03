#include <iostream>
#include <vector>
#include <iomanip>

using line = std::vector<unsigned short>;
using matrix = std::vector<line>;

long double f(long double r, long double p) {
    return (p + r) == 0 ? 0 : 2 * p * r / (p + r);
}

int main() {
    unsigned short k;
    std::cin >> k;
    matrix a(k, line(k));
    for (unsigned short i = 0; i < k; ++i) {
        for (unsigned short j = 0; j < k; ++j) {
            std::cin >> a[i][j];
        }
    }

    line column(k, 0), row(k, 0);
    unsigned short trace = 0, sum = 0;
    for (unsigned short i = 0; i < k; ++i) {
        for (unsigned short j = 0; j < k; ++j) {
            column[i] += a[i][j];
            row[i] += a[j][i];
        }
        sum += column[i];
        trace += a[i][i];
    }

    long double p = 0, r = 0, s = 0;
    for (unsigned short i = 0; i < k; ++i) {
        long double p_temp = column[i] == 0 ? 0 : ((long double) a[i][i]) / column[i];
        long double r_temp = row[i] == 0 ? 0 : ((long double) a[i][i]) / row[i];

        p += p_temp * column[i];
        r += r_temp * column[i];
        s += f(r_temp, p_temp) * column[i];
    }

    std::cout << std::setprecision(8) <<  f(r, p) / sum << '\n' << s / sum;
}

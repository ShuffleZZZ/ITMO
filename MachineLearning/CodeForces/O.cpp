#include <iostream>
#include <iomanip>

int main() {
    unsigned int k, n;
    std::cin >> k >> n;
    int x[n], y[n];
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i];
    }

    double Ey2 = 0;
    for (unsigned int i = 0; i < n; ++i) {
        Ey2 += static_cast<double>(y[i] * y[i]) / n;
    }

    double px[k] = {}, Eylx[k] = {};
    for (unsigned int i = 0; i < n; ++i) {
        px[x[i] - 1] += 1.0 / n;
        Eylx[x[i] - 1] += static_cast<double>(y[i]) / n;
    }

    double EEylx2 = 0;
    for (unsigned int i = 0; i < k; ++i) {
        if (px[i]) EEylx2 += Eylx[i] * Eylx[i] / px[i];
    }

    std::cout << std::setprecision(8) << Ey2 - EEylx2;
}

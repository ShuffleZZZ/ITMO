#include <iostream>
#include <cmath>

int main() {
    unsigned short m;
    std::cin >> m;
    unsigned short size = std::pow(2, m);
    bool values[size];
    unsigned short sum = 0;
    for (unsigned short i = 0; i < size; ++i) {
        std::cin >> values[i];
        sum += values[i];
    }

    if (sum == 0) {
        std::cout << '1' << '\n' << '1' << '\n';
        for (unsigned short i = 0; i < m; ++i) {
            std::cout << '0' << ' ';
        }
    } else {
        std::cout << '2' << '\n';
        std::cout << sum << ' ' << '1' << '\n';
        for (unsigned short i = 0; i < size; ++i) {
            if (!values[i]) {
                continue;
            }

            bool bytes[m];
            unsigned short byte = i;
            unsigned short sumBytes = 0;
            for (unsigned short j = 0; j < m; ++j) {
                bytes[j] = byte & 1;
                sumBytes += bytes[j];

                std::cout << (bytes[j] ? "1" : "-1") << ' ';

                byte >>= 1;
            }

            std::cout << 0.5 - sumBytes << '\n';
        }

        for (unsigned short i = 0; i < sum; ++i) {
            std::cout << '1' << ' ';
        }
    }

    std::cout << "-0.5";
}

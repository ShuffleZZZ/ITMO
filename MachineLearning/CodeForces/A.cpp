#include <iostream>
#include <vector>
#include <exception>

using line = std::vector<unsigned int>;
using matrix = std::vector<line>;

int main() {
    unsigned int n, m, k;
    std::cin >> n >> m >> k;
    matrix a(m, line());
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int b;
        std::cin >> b;
        a[b - 1].push_back(i + 1);
    }
    // for (unsigned int i = 0; i < m; ++i) {
    //     for (unsigned int j = 0; j < a[i].size(); ++j) {
    //         std::cout << a[i][j] << " ";
    //     }
    //     std::cout << '\n';
    // }
    unsigned int cnt = 0;
    matrix res(k, line());
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < a[i].size(); ++j) {
            res[cnt++].push_back(a[i][j]);
            cnt = cnt == k ? 0 : cnt;
        }
    }

    for (unsigned int i = 0; i < k; ++i) {
        std::cout << res[i].size() << " ";
        for (unsigned int j = 0; j < res[i].size(); ++j) {
            std::cout << res[i][j] << " ";
        }
        std::cout << '\n';
    }
}

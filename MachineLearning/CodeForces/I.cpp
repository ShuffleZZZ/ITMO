#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using line = std::vector<double>;
using matrix = std::vector<line>;

matrix operator *(const matrix& a, const matrix& b) {
    matrix res(a.size(), line(b[0].size()));
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            res[i][j] = 0.0;
            for (int l = 0; l < b.size(); ++l) {
                res[i][j] += a[i][l] * b[l][j];
            }
        }
    }

    return res;
}

matrix operator &(const matrix& a, const matrix& b) {
    matrix res(a.size(), line(a[0].size()));
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            res[i][j] = a[i][j] * b[i][j];
        }
    }

    return res;
}

matrix operator +(const matrix& a, const matrix& b) {
    matrix res(a.size(), line(a[0].size()));
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }

    return res;
}

matrix transpose(const matrix& a) {
    matrix res(a[0].size(), line(a.size()));
    for (int i = 0; i < res[0].size(); ++i) {
        for (int j = 0; j < res.size(); ++j) {
            res[j][i] = a[i][j];
        }
    }

    return res;
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::string vertices[n];
    std::vector<int> vectors[n];
    std::pair<int, int> scalars[n];
    for (int i = 0; i < n; ++i) {
        std::string type;
        std::cin >> type;
        vertices[i] = type;

        if (vertices[i] == "var") {
            int r, c;
            std::cin >> r >> c;
            scalars[i] = {r, c};
        } else if (vertices[i] == "tnh") {
            int x;
            std::cin >> x;
            scalars[i] = {x - 1, 0};
        } else if (vertices[i] == "rlu") {
            int a, x;
            std::cin >> a >> x;
            scalars[i] = {a, x - 1};
        } else if (vertices[i] == "mul") {
            int a, b;
            std::cin >> a >> b;
            scalars[i] = {a - 1, b - 1};
        } else {
            int l;
            std::cin >> l;

            vectors[i].resize(l);
            for (int j = 0; j < l; ++j) {
                int u;
                std::cin >> u;
                vectors[i][j] = u - 1;
            }
        }
    }

    matrix input[n];
    for (int i = 0; i < m; ++i) {
        input[i].resize(scalars[i].first, line(scalars[i].second));

        for (int j = 0; j < input[i].size(); ++j) {
            for (int l = 0; l < input[i][j].size(); ++l) {
                int value;
                std::cin >> value;
                input[i][j][l] = value;
            }
        }
    }

    for (int i = m; i < n; ++i) {
        if (vertices[i] == "tnh") {
            input[i] = input[scalars[i].first];

            for (int j = 0; j < input[i].size(); ++j) {
                for (int l = 0; l < input[i][j].size(); ++l) {
                    input[i][j][l] = std::tanh(input[i][j][l]);
                }
            }
        } else if (vertices[i] == "rlu") {
            input[i] = input[scalars[i].second];

            for (int j = 0; j < input[i].size(); ++j) {
                for (int l = 0; l < input[i][j].size(); ++l) {
                    if (input[i][j][l] < 0) {
                        input[i][j][l] *= 1.0 / scalars[i].first;
                    }
                }
            }
        } else if (vertices[i] == "mul") {
            input[i] = input[scalars[i].first] * input[scalars[i].second];
        } else if (vertices[i] == "sum") {
            input[i] = input[vectors[i][0]];

            for (int j = 1; j < vectors[i].size(); ++j) {
                input[i] = input[i] + input[vectors[i][j]];
            }
        } else if (vertices[i] == "had") {
            input[i] = input[vectors[i][0]];

            for (int j = 1; j < vectors[i].size(); ++j) {
                input[i] = input[i] & input[vectors[i][j]];
            }
        }
    }

    matrix deriv[n];
    for (int i = n - k; i < n; ++i) {
        deriv[i].resize(input[i].size(), line(input[i][0].size()));

        for (int j = 0; j < deriv[i].size(); ++j) {
            for (int l = 0; l < deriv[i][j].size(); ++l) {
                int value;
                std::cin >> value;
                deriv[i][j][l] = value;
            }
        }
    }

    for (int i = 0; i < n - k; ++i) {
        deriv[i].resize(input[i].size(), line(input[i][0].size(), 0.0));
    }

    for (int i = n - 1; i > 0; --i) {
        if (deriv[i].empty()) {
            continue;
        }

        if (vertices[i] == "tnh") {
            if (deriv[scalars[i].first].empty()) {
                deriv[scalars[i].first].resize(deriv[i].size(),
                    line(deriv[i][0].size(), 0.0));
            }

            for (int j = 0; j < deriv[scalars[i].first].size(); ++j) {
                for (int l = 0; l < deriv[scalars[i].first][j].size(); ++l) {
                    double prevValue = input[scalars[i].first][j][l];
                    deriv[scalars[i].first][j][l] += (std::pow(std::cosh(prevValue), 2)
                        - std::pow(std::sinh(prevValue), 2))
                            / std::pow(std::cosh(prevValue), 2)
                            * deriv[i][j][l];
                }
            }
        } else if (vertices[i] == "rlu") {
            if (deriv[scalars[i].second].empty()) {
                deriv[scalars[i].second].resize(deriv[i].size(),
                    line(deriv[i][0].size(), 0.0));
            }

            for (int j = 0; j < deriv[scalars[i].second].size(); ++j) {
                for (int l = 0; l < deriv[scalars[i].second][j].size(); ++l) {
                    double prevValue = input[scalars[i].second][j][l];
                    deriv[scalars[i].second][j][l] += prevValue < 0
                        ? 1.0 / scalars[i].first * deriv[i][j][l]
                        : deriv[i][j][l];
                }
            }
        } else if (vertices[i] == "mul") {
            if (deriv[scalars[i].first].empty()) {
                deriv[scalars[i].first] = transpose(input[scalars[i].second] * transpose(deriv[i]));
            } else {
                deriv[scalars[i].first] = deriv[scalars[i].first]
                    + transpose(input[scalars[i].second] * transpose(deriv[i]));
            }

            if (deriv[scalars[i].second].empty()) {
                deriv[scalars[i].second] = transpose(input[scalars[i].first]) * deriv[i];
            } else {
                deriv[scalars[i].second] = deriv[scalars[i].second]
                    + transpose(input[scalars[i].first]) * deriv[i];
            }
        } else if (vertices[i] == "sum") {
            for (int j = 0; j < vectors[i].size(); ++j) {
                if (deriv[vectors[i][j]].empty()) {
                    deriv[vectors[i][j]].resize(deriv[i].size(),
                        line(deriv[i][0].size(), 0.0));
                }

                deriv[vectors[i][j]] = deriv[vectors[i][j]] + deriv[i];
            }
        } else if (vertices[i] == "had") {
            for (int j = 0; j < vectors[i].size(); ++j) {
                if (deriv[vectors[i][j]].empty()) {
                    deriv[vectors[i][j]].resize(deriv[i].size(),
                        line(deriv[i][0].size(), 0.0));
                }

                for (int l = 0; l < deriv[vectors[i][j]].size(); ++l) {
                    for (int p = 0; p < deriv[vectors[i][j]][l].size(); ++p) {
                        double value = 1.0;
                        for (int q = 0; q < vectors[i].size(); ++q) {
                            if (q == j) {
                                continue;
                            }

                            value *= input[vectors[i][q]][l][p];
                        }

                        deriv[vectors[i][j]][l][p] += value * deriv[i][l][p];
                    }
                }
            }
        }
    }

    std::cout.precision(10);

    for (int i = n - k; i < n; ++i) {
        for (int j = 0; j < input[i].size(); ++j) {
            for (int l = 0; l < input[i][j].size(); ++l) {
                std::cout << input[i][j][l] << ' ';
            }
            std::cout << '\n';
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < deriv[i].size(); ++j) {
            for (int l = 0; l < deriv[i][j].size(); ++l) {
                std::cout << deriv[i][j][l] << ' ';
            }
            std::cout << '\n';
        }
    }
}

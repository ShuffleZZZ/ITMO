#include <iostream>
#include <iomanip>

#include <algorithm>
#include <vector>
#include <cmath>

#include <unordered_set>
#include <unordered_map>

using keyValueType = std::pair<const std::string, long double>&;

int main() {
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

    int k;
    std::cin >> k;
    long double lambda[k];
    for (int i = 0; i < k; ++i) {
        std::cin >> lambda[i];
    }

    int n;
    long double alpha;
    std::cin >> alpha >> n;
    int classCountSum = 0;
    int classCount[k] = {};
    std::unordered_set<std::string> allWords;
    std::unordered_map<std::string, long double> trainData[k];
    for (int i = 0; i < n; ++i) {
        int c, l;
        std::cin >> c >> l;

        ++classCount[--c];
        ++classCountSum;
        std::unordered_set<std::string> words;
        for (int j = 0; j < l; ++j) {
            std::string word;
            std::cin >> word;

            if (!words.insert(word).second) {
                continue;
            }
            allWords.insert(word);
            ++trainData[c][word];
        }
    }

    for (const std::string& word : allWords) {
        for (int i = 0; i < k; ++i) {
            trainData[i][word] = (alpha + trainData[i][word]) / (2.0 * alpha + classCount[i]);
        }
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int l;
        std::cin >> l;

        std::unordered_set<std::string> words;
        for (int j = 0; j < l; ++j) {
            std::string word;
            std::cin >> word;

            words.insert(word);
        }

        long double probSum = 0.0;
        long double classProb[k] = {};
        for (int j = 0; j < k; ++j) {
            classProb[j] = std::log(lambda[j] * classCount[j] / classCountSum);

            for (keyValueType wordProbability : trainData[j]) {
                classProb[j] += std::log(
                    words.find(wordProbability.first) != words.end()
                    ? wordProbability.second
                    : 1.0 - wordProbability.second
                );
            }

            classProb[j] = std::exp(classProb[j]);
            probSum += classProb[j];
        }

        std::cout << std::setprecision(10);
        for (int j = 0; j < k; ++j) {
            std::cout << classProb[j] / probSum << ' ';
        }
        std::cout << '\n';
    }
}

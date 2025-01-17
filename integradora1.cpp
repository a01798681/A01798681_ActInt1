#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::pair<bool, size_t> contains(const std::string& text, const std::string& pattern) {
    size_t pos = text.find(pattern);
    return {pos != std::string::npos, pos};
}

std::pair<std::pair<size_t, size_t>, std::string> longestPalindrome(const std::string& text) {
    size_t n = text.size();
    size_t start = 0, maxLength = 1;

    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));

    for (size_t i = 0; i < n; ++i) dp[i][i] = true;

    for (size_t i = 0; i < n - 1; ++i) {
        if (text[i] == text[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    for (size_t len = 3; len <= n; ++len) {
        for (size_t i = 0; i < n - len + 1; ++i) {
            size_t j = i + len - 1;
            if (text[i] == text[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                start = i;
                maxLength = len;
            }
        }
    }

    std::string palindrome = text.substr(start, maxLength);
    return {{start + 1, start + maxLength}, palindrome}; 
}

std::tuple<size_t, size_t, std::string> longestCommonSubstring(const std::string& text1, const std::string& text2) {
    size_t n1 = text1.size(), n2 = text2.size();
    size_t maxLength = 0, endIdx = 0;

    std::vector<std::vector<size_t>> dp(n1 + 1, std::vector<size_t>(n2 + 1, 0));

    for (size_t i = 1; i <= n1; ++i) {
        for (size_t j = 1; j <= n2; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIdx = i - 1;
                }
            }
        }
    }

    std::string substring = text1.substr(endIdx - maxLength + 1, maxLength);
    return {endIdx - maxLength + 2, endIdx + 1, substring}; 
}

int main() {
    std::string transmission1 = readFile("transmission1.txt");
    std::string transmission2 = readFile("transmission2.txt");
    std::vector<std::string> mcodeFiles = {
        readFile("mcode1.txt"),
        readFile("mcode2.txt"),
        readFile("mcode3.txt")
    };

    std::cout << "Parte 1:" << std::endl;
    for (size_t i = 0; i < mcodeFiles.size(); ++i) {
        auto [found1, pos1] = contains(transmission1, mcodeFiles[i]);
        auto [found2, pos2] = contains(transmission2, mcodeFiles[i]);
        std::cout << (found1 ? "true " + std::to_string(pos1 + 1) : "false") << std::endl;
        std::cout << (found2 ? "true " + std::to_string(pos2 + 1) : "false") << std::endl;
    }

    std::cout << "Parte 2:" << std::endl;
    auto [range1, palindrome1] = longestPalindrome(transmission1);
    auto [range2, palindrome2] = longestPalindrome(transmission2);
    std::cout << range1.first << " " << range1.second << " " << palindrome1 << std::endl;
    std::cout << range2.first << " " << range2.second << " " << palindrome2 << std::endl;

    std::cout << "Parte 3:" << std::endl;
    auto [startCommon, endCommon, commonSubstring] = longestCommonSubstring(transmission1, transmission2);
    std::cout << startCommon << " " << endCommon << " " << commonSubstring << std::endl;

    return 0;
}

zfunction

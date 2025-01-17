#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Función para leer el contenido de un archivo
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Función para buscar si una secuencia está contenida en otra
std::pair<bool, size_t> contains(const std::string& text, const std::string& pattern) {
    size_t pos = text.find(pattern);
    return {pos != std::string::npos, pos};
}

// Función para encontrar el palíndromo más largo en un texto
std::pair<size_t, size_t> longestPalindrome(const std::string& text) {
    size_t n = text.size();
    size_t start = 0, maxLength = 1;

    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));

    // Cada carácter es un palíndromo
    for (size_t i = 0; i < n; ++i) dp[i][i] = true;

    // Palíndromos de longitud 2
    for (size_t i = 0; i < n - 1; ++i) {
        if (text[i] == text[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Palíndromos de longitud mayor a 2
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

    return {start + 1, start + maxLength}; // Posiciones iniciando desde 1
}

// Función para encontrar el substring más largo común entre dos textos
std::pair<size_t, size_t> longestCommonSubstring(const std::string& text1, const std::string& text2) {
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

    return {endIdx - maxLength + 2, endIdx + 1}; // Posiciones iniciando desde 1
}

int main() {
    // Leer los archivos
    std::string transmission1 = readFile("transmission1.txt");
    std::string transmission2 = readFile("transmission2.txt");
    std::vector<std::string> mcodeFiles = {
        readFile("mcode1.txt"),
        readFile("mcode2.txt"),
        readFile("mcode3.txt")
    };

    // Parte 1: Verificar códigos maliciosos en transmisiones
    std::cout << "Parte 1:" << std::endl;
    for (size_t i = 0; i < mcodeFiles.size(); ++i) {
        auto [found1, pos1] = contains(transmission1, mcodeFiles[i]);
        auto [found2, pos2] = contains(transmission2, mcodeFiles[i]);
        std::cout << (found1 ? "true " + std::to_string(pos1 + 1) : "false") << std::endl;
        std::cout << (found2 ? "true " + std::to_string(pos2 + 1) : "false") << std::endl;
    }

    // Parte 2: Buscar palíndromos más largos
    std::cout << "Parte 2:" << std::endl;
    auto [start1, end1] = longestPalindrome(transmission1);
    auto [start2, end2] = longestPalindrome(transmission2);
    std::cout << start1 << " " << end1 << std::endl;
    std::cout << start2 << " " << end2 << std::endl;

    // Parte 3: Substring común más largo
    std::cout << "Parte 3:" << std::endl;
    auto [startCommon, endCommon] = longestCommonSubstring(transmission1, transmission2);
    std::cout << startCommon << " " << endCommon << std::endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string readFile(const string& filename){
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

pair<bool, size_t> contains(const string& text, const string& pattern){
    size_t pos = text.find(pattern);
    return {pos != string::npos, pos};
}

pair<pair<size_t, size_t>, string> longestPalindrome(const string& text){
    size_t n = text.size();
    size_t start = 0, maxLength = 1;
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    for (size_t i = 0; i < n; ++i) dp[i][i] = true;
    for (size_t i = 0; i < n - 1; ++i){
        if (text[i] == text[i + 1]){
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }
    for (size_t len = 3; len <= n; ++len){
        for (size_t i = 0; i < n - len + 1; ++i){
            size_t j = i + len - 1;
            if (text[i] == text[j] && dp[i + 1][j - 1]){
                dp[i][j] = true;
                start = i;
                maxLength = len;
            }
        }
    }
    string palindrome = text.substr(start, maxLength);
    return {{start + 1, start + maxLength}, palindrome}; 
}

tuple<size_t, size_t, string> longestCommonSubstring(const string& text1, const string& text2){
    size_t n1 = text1.size(), n2 = text2.size();
    size_t maxLength = 0, endIdx = 0;
    vector<vector<size_t>> dp(n1 + 1, vector<size_t>(n2 + 1, 0));
    for (size_t i = 1; i <= n1; ++i){
        for (size_t j = 1; j <= n2; ++j){
            if (text1[i - 1] == text2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength){
                    maxLength = dp[i][j];
                    endIdx = i - 1;
                }
            }
        }
    }
    string substring = text1.substr(endIdx - maxLength + 1, maxLength);
    return {endIdx - maxLength + 2, endIdx + 1, substring}; 
}

int main(){
    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");
    vector<string> mcodeFiles = {
        readFile("mcode1.txt"),
        readFile("mcode2.txt"),
        readFile("mcode3.txt")
    };

    cout << "Parte 1:" << endl;
    for (size_t i = 0; i < mcodeFiles.size(); ++i) {
        auto [found1, pos1] = contains(transmission1, mcodeFiles[i]);
        auto [found2, pos2] = contains(transmission2, mcodeFiles[i]);
        cout << (found1 ? "true " + to_string(pos1 + 1) : "false") << endl;
        cout << (found2 ? "true " + to_string(pos2 + 1) : "false") << endl;
    }

    cout << "Parte 2:" << endl;
    auto [range1, palindrome1] = longestPalindrome(transmission1);
    auto [range2, palindrome2] = longestPalindrome(transmission2);
    cout << range1.first << " " << range1.second << " " << palindrome1 << endl;
    cout << range2.first << " " << range2.second << " " << palindrome2 << endl;

    cout << "Parte 3:" << endl;
    auto [startCommon, endCommon, commonSubstring] = longestCommonSubstring(transmission1, transmission2);
    cout << startCommon << " " << endCommon << " " << commonSubstring << endl;
    return 0;
}
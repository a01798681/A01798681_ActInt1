
/*
Activicdad Integradora 1
 * Programa de análisis de patrones, identificar palindromos y comparar los datos en archivos de texto.
 * Autores:
 *   - Andrés Cabrera Alvarado - A01798681
 *   - José Eduardo Rosas Poncio - A01784461
 *   - Yael Octavio Pérez Méndez - A01799842
 * Fecha de creación: 23/01/25
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * @brief lee el archivo y lo devuelve como un string.
 * @param nombre del archivo a leer.
 * @return contenido del archivo como string.
 */
string read_file(const string& filename){
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

/*
 * @brief verifica si un texto contiene un patrón específico.
 * @param texto que buscará el patrón.
 * @param patrón a buscar.
 * @return par con un booleano que indica si se encontró el patrón y su posición.
 */
pair<bool, size_t> contiene(const string& text, const string& pattern){
    size_t pos = text.find(pattern);
    return {pos != string::npos, pos};
}

/*
 * @brief encuentra el palíndromo más largo en un texto.
 * @param texto que buscará el palíndromo.
 * @return par con el rango del palíndromo y el texto del palíndromo.
 */
pair<pair<size_t, size_t>, string> largo_palindromo(const string& text){
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

/*
 * @brief encuentra la subcadena común más larga entre dos textos.
 * @param primer texto.
 * @param segundo texto.
 * @return tupla con los índices de la subcadena y el texto de la subcadena.
 */
tuple<size_t, size_t, string> largo_substring(const string& text1, const string& text2){
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

/*
 * @brief lee los archivos y ejecuta el análisis de las transmisiones.
 * @return ejecución de las 3 partes.
 */
int main(){
    string transmission1 = read_file("transmission1.txt");
    string transmission2 = read_file("transmission2.txt");
    vector<string> mcodeFiles = {
        read_file("mcode1.txt"),
        read_file("mcode2.txt"),
        read_file("mcode3.txt")
    };

    //parte1: verifica que los códigos mcode estén en las transmisiones
    cout << "Parte 1:" << endl;
    for (size_t i = 0; i < mcodeFiles.size(); ++i) {
        auto [found1, pos1] = contiene(transmission1, mcodeFiles[i]);
        auto [found2, pos2] = contiene(transmission2, mcodeFiles[i]);
        cout << (found1 ? "true " + to_string(pos1 + 1) : "false") << endl;
        cout << (found2 ? "true " + to_string(pos2 + 1) : "false") << endl;
    }

    //parte2: posición inicial y final del palíndromo más largo
    cout << "Parte 2:" << endl;
    auto [range1, palindrome1] = largo_palindromo(transmission1);
    auto [range2, palindrome2] = largo_palindromo(transmission2);
    cout << range1.first << " " << range1.second << " " << palindrome1 << endl;
    cout << range2.first << " " << range2.second << " " << palindrome2 << endl;

    //parte3: posición inicial y final del substring comun más largo entre os archivos de transmisión
    cout << "Parte 3:" << endl;
    auto [startCommon, endCommon, commonSubstring] = largo_substring(transmission1, transmission2);
    cout << startCommon << " " << endCommon << " " << commonSubstring << endl;
    return 0;
}
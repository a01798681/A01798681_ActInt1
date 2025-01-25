#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Función que calcula la función Z para una cadena dada
vector<int> funcion_z(const string& s) {
    int n = s.length();
    vector<int> Z(n); // Vector para almacenar los valores Z
    int L = 0, R = 0; // Inicializamos los límites de la ventana [L, R]

    // Iteramos a través de la cadena, comenzando desde el segundo carácter
    for (int i = 1; i < n; ++i) {
        if (i <= R) {
            // Si i está dentro de la ventana [L, R], usamos los valores ya calculados
            Z[i] = min(R - i + 1, Z[i - L]);
        }

        // Comparación manual de caracteres después de la posición i
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
            Z[i]++;
        }

        // Si la coincidencia encontrada se extiende más allá de R, actualizamos L y R
        if (i + Z[i] - 1 > R) {
            L = i;
            R = i + Z[i] - 1;
        }
    }
    return Z; // Retornamos el vector Z con todos los valores
}

/*
 * @brief verifica si un texto contiene un patrón específico.
 * @param vector z de la string
 * @param tamaño del patron a buscar
 * @return par con un booleano que indica si se encontró el patrón y su posición.
 */
pair<string, int> parte1(vector<int>& Z, const int tam_patron) {
    for (int j = tam_patron + 1; j < Z.size(); ++j) {
        if (Z[j] == tam_patron) {
            return {": true", (j - tam_patron)};
            break;
        }
    }
    return {": false", -1};
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
 * @return no retorna nada pero imprime la información de la posicion inicial, final y el patron en común
 */
void parte3(const string& s1, const string& s2) {
    int maxLen = 0;         // Longitud máxima del patrón común
    string bestPattern;     // El patrón más largo encontrado

    for (size_t start = 0; start < s1.size(); ++start) {
        // Eliminamos los primeros indices conforme vamos recorriendo el arreglo para encontrar el patron
        string combined = s1.substr(start) + "$" + s2;
        vector<int> z = funcion_z(combined);

        // Recorrer la parte del vector Z correspondiente a s2 (después del separador $)
        for (size_t i = s1.size() - start + 1; i < combined.size(); ++i) {
            if (z[i] > maxLen) {
                maxLen = z[i];
                bestPattern = s1.substr(start, maxLen);
            }
        }
    }
    string cadena = bestPattern + "$" + s1;
    vector<int> Z = funcion_z(cadena); // Volvemos a calcular el vector z de la transmision1
    pair<string, int> posicion = parte1(Z, maxLen); // encontramos la posición inicial  del patron
    cout << posicion.second << " " << posicion.second + maxLen - 1 << " " << bestPattern << endl;
}

// Función para leer un archivo y devolver su contenido como string
string read_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

/*
 * @brief lee los archivos y ejecuta el análisis de las transmisiones.
 * @return ejecución de las 3 partes.
 */
int main() {
    // Leer los archivos de las transmisiones y los patrones
    string transmission1 = read_file("transmission1.txt");
    string transmission2 = read_file("transmission2.txt");
    vector<string> mcodeFiles = {
        read_file("mcode1.txt"),
        read_file("mcode2.txt"),
        read_file("mcode3.txt")
    };

    cout << "Parte 1" << endl;
    for (size_t i = 0; i < mcodeFiles.size(); ++i) {
        string concatenated1 = mcodeFiles[i] + "$" + transmission1;
        string concatenated2 = mcodeFiles[i] + "$" + transmission2;

        vector<int> Z1 = funcion_z(concatenated1);
        vector<int> Z2 = funcion_z(concatenated2);

        pair<string, int> res_t1 = parte1(Z1, mcodeFiles[i].length());
        cout << "Transmision 1 mcode " << (i + 1) << res_t1.first + " " + ((res_t1.second != -1) ? to_string(res_t1.second) : " ") << endl;

        pair<string, int> res_t2 = parte1(Z2, mcodeFiles[i].length());
        cout << "Transmision 2 mcode " << (i + 1) << res_t2.first + " " + ((res_t2.second != -1) ? to_string(res_t2.second) : " ") << endl;
    }

    cout << "\nParte 2:" << endl;
    auto [range1, palindrome1] = largo_palindromo(transmission1);
    auto [range2, palindrome2] = largo_palindromo(transmission2);
    cout << range1.first << " " << range1.second << " " << palindrome1 << endl;
    cout << range2.first << " " << range2.second << " " << palindrome2 << endl;

    cout << "Parte 3" << endl;
    parte3(transmission1, transmission2);

    return 0;
}

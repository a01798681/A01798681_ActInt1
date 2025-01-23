
/*
Actividad Integradora 1
 * Programa de análisis de patrones, identificar palindromos y comparar los datos en archivos de texto
   por medio del algoritmo de funcion Z.
 * Autores:
 *   - Andrés Cabrera Alvarado - A01798681
 *   - José Eduardo Rosas Poncio - A01784461
 *   - Yael Octavio Pérez Méndez - A01799842
 * Fecha de creación: 23/01/25
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

vector<int> funcion_z(const string &s){
    vector<int> Z(s.length()); //Vector para almacenar los valores de Z
    int L = 0, R = 0; // Límites para la memorización

    for (int i = 0; i < s.length(); i++){
      if (i <= R) {
        Z[i] = min(R - i + 1, Z[i - L]);
      }

      while (i + Z[i] < s.length() && s[Z[i]] == s[i + Z[i]]){
        Z[i]++;
      }

      if (i + Z[i] - 1 > R ){
        L = i;
        R = i + Z[i] - 1;
      }
    }

    return Z;
}

// Función para mostrar un vector (útil para ver los resultados)
void printVector(const vector<int>& v) {
  for (int val : v) {
    cout << val << " ";
  }
  cout << endl;
}

int main(){

    string patron = "abc";
    string texto = "xabcyabc";

    //concatenacion del patron con caracter especial $
    string concatenada = patron + "$" + texto;

    vector<int> Z = funcion_z(concatenada);

    // Mostramos los valores Z calculados
    cout << "Valores Z: ";
    printVector(Z);

    // Interpretamos los valores Z
    cout << "Posiciones donde el patrón coincide en el texto original: ";
    for (int i = patron.length() + 1; i < Z.size(); ++i) {
        // Si Z[i] es igual a la longitud del patrón, encontramos una coincidencia
        if (Z[i] == patron.length()) {
            cout << (i - patron.length() - 1) << " "; // Restamos el offset para obtener la posición en el texto
        }
    }
    cout << endl;

  return 0;
}

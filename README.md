# Actividad Integradora 1: Análisis de patrones y comparación de archivos

## Descripción

Este proyecto incluye dos programas que analizan archivos de texto para realizar tareas específicas como:
1. Verificar la presencia de patrones en archivos de texto.
2. Identificar el palíndromo más largo en un archivo de texto.
3. Encontrar la subcadena común más larga entre dos archivos.
4. Implementar el algoritmo de la función Z para búsqueda eficiente de patrones.

El propósito de implementar dos algoritmos diferentes en este proyecto fue evaluar cual de los dos mostraba 
una eficiencia mayor y de esta manera evaluar su complejidad espacial y computacional.

**Fecha de creación:** 21/01/2025

---

## Archivos
### 1. `Integradora1.cpp`
Este archivo realiza tres análisis principales:
- **Parte 1:** Verifica si ciertos patrones (`mcode`) están presentes en las transmisiones (`transmission1.txt` y `transmission2.txt`), indicando su posición si se encuentran.
- **Parte 2:** Encuentra el palíndromo más largo en las transmisiones y muestra su posición inicial, final y el texto.
- **Parte 3:** Encuentra la subcadena común más larga entre dos transmisiones y muestra su posición inicial, final y el texto.

#### Funciones principales:
- `read_file`: Lee un archivo y devuelve su contenido como una cadena.
- `contiene`: Verifica si un texto contiene un patrón y devuelve su posición.
- `largo_palindromo`: Encuentra el palíndromo más largo en un texto.
- `largo_substring`: Encuentra la subcadena común más larga entre dos textos.

#### Uso:
El programa requiere archivos de entrada (`transmission1.txt`, `transmission2.txt`, `mcode1.txt`, `mcode2.txt`, `mcode3.txt`) en el mismo directorio para ejecutar correctamente. 

### 2. `Int_FunZ.cpp`
Este archivo implementa el algoritmo de la función Z para encontrar todas las ocurrencias de un patrón en un texto.

### Funciones principales:
- `funcion_z`: Calcula el vector Z para un texto concatenado (patrón + $ + texto).
- `parte1`: Esta función muestra si existe un patrón en la cadena y regresa la posición inicial del patrón.
- `largo_palindromo`: Encuentra el palíndromo más largo en un texto.
- `parte3`: Encuentra el patrón más largo que aparece en ambos textos y regresa su posición inicial, final y el patrón.
- `read_file`: Lee un archivo y devuelve su contenido como una cadena.

### Uso:
El programa requiere archivos de entrada (`transmission1.txt`, `transmission2.txt`, `mcode1.txt`, `mcode2.txt`, `mcode3.txt`) en el mismo directorio para ejecutar correctamente.

##Requerimientos
- Compilador C++ (compatible con C++11 o superior).

- Archivos de texto en el mismo directorio que los ejecutables.

##Autores
- Andrés Cabrera Alvarado A01798681
- José Eduardo Rosas Poncio A01784461
- Yael Octavio Pérez Méndez A01799842

---

## Contribuciones
- **Andrés Cabrera Alvarado (A01798681):**
  - Implementación de la función `largo_palindromo` y análisis del palíndromo más largo en `integradora1.cpp`.
  - Desarrollo de la lógica para verificar patrones en transmisiones (Parte 1).
  - Implementación de la lógica para interpretar los valores Z en `Int_funZ.cpp`.
  - Creación de la función `parte3` en `Int_funZ.cpp`.

- **José Eduardo Rosas Poncio (A01784461):**
  - Implementación de las funciones `read_file` y `contiene` en `integradora1.cpp `.
  - Desarrollo de la lógica principal de la Parte 2 en `integradora1.cpp `.
  - Apoyo en la creación de la función `parte3` y pruebas del algoritmo Z en `Int_funZ.cpp`.
  - Apoyo en la creación de la función `parte1` y pruebas del algoritmo Z en `Int_funZ.cpp`.

- **Yael Octavio Pérez Méndez (A01799842):**
  - Implementación de la función `largo_substring` para identificar la subcadena común más larga en `integradora1.cpp`.
  - Desarrollo de la lógica principal de la Parte 3 en `integradora1.cpp`.
  - Implementación de la función `funcion_z` en `Int_funZ.cpp` y configuración inicial de las pruebas.
  - Creación de la función `parte3` en `Int_funZ.cpp`.

Ejecuta el programa con:
```bash
g++ integradora1.cpp -o main
./main

g++ Int_FunZ.cpp -o main
./main
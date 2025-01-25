# Actividad Integradora 1: Análisis de patrones y comparación de archivos

## Descripción
Este proyecto incluye dos programas que analizan archivos de texto para realizar tareas específicas como:
1. Verificar la presencia de patrones en archivos de texto.
2. Identificar el palíndromo más largo en un archivo de texto.
3. Encontrar la subcadena común más larga entre dos archivos.
4. Implementar el algoritmo de la función Z para búsqueda eficiente de patrones.

**Autores:**
- Andrés Cabrera Alvarado - A01798681  
- José Eduardo Rosas Poncio - A01784461  
- Yael Octavio Pérez Méndez - A01799842  

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

Ejecuta el programa con:
```bash
g++ integradora1.cpp -o main
./main

### 2. `int_funZ.cpp`
Este archivo implementa el algoritmo de la función Z para encontrar todas las ocurrencias de un patrón en un texto.

### Funciones principales:
- `funcion_z`: Calcula el vector Z para un texto concatenado (patrón + $ + texto).
- `printVector`: Muestra el contenido de un vector.

### Uso:
El programa tiene valores predeterminados (patron = "abc" y texto = "xabcyabc") que pueden ser modificados directamente en el código y requiere los mismos archivos que el archivo 1

##Requerimientos
- Compilador C++ (compatible con C++11 o superior).

- Archivos de texto en el mismo directorio que los ejecutables.

##Autores
- Andrés Cabrera Alvarado A01798681
- José Eduardo Rosas Poncio A01784461
- Yael Octavio Pérez Méndez A01799842
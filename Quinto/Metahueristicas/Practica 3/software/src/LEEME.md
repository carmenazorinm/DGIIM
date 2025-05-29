# Proyecto Metaheurísticas - Técnicas de Búsqueda Basadas en Trayectorias Individuales

Este proyecto sigue la estructura de la plantilla proporcionada por el profesor disponible en [https://github.com/dmolina/template_mh](https://github.com/dmolina/template_mh).

## Estructura del Proyecto

- **`build/`**  
  Esta carpeta se genera automáticamente al compilar el proyecto (usando `cmake` y `make`). Contiene los archivos binarios generados y los resultados de las ejecuciones, como `resultados_conjuntoDatos.txt`.

- **`inc/snimp_problem.h`**  
  Contiene la clase `Snimp`, que hereda de `Problem` y define el problema SNIMP. Implementa la generación de soluciones aleatorias, cálculo de fitness y heurísticas por nodo.

- **`inc/graph.h`** y **`src/graph.cpp`**  
  Implementan la clase `Graph`, que se encarga de cargar los grafos desde archivo y construir las listas de adyacencia.

- **Algoritmos anteriores (`inc/` y `src/`):**
  - **Greedy**: `greedy.h` / `greedy.cpp`
  - **RandomSearch**: `randomsearch.h` / `randomsearch.cpp`
  - **BLsmall** y **LSall**: Definidos en `blsmall.h` / `lsall.h` y centralizados en `localsearch.cpp`

- **Nuevos Algoritmos Basados en Trayectorias (`inc/` y `src/`):**
  - **`ES.h` / `ES.cpp`**: Implementa el algoritmo de Enfriamiento Simulado (Simulated Annealing), usando esquema de Cauchy modificado.
  - **`BMB.h` / `BMB.cpp`**: Búsqueda Multiarranque Básica, reinicia desde soluciones aleatorias aplicando búsqueda local.
  - **`ILS.h` / `ILS.cpp`**: Búsqueda Local Iterada con mutación leve y reinicio desde soluciones mejoradas.
  - **`ILS_ES.h` / `ILS_ES.cpp`**: Variante combinada de ILS con Enfriamiento Simulado como búsqueda local.
  - **`GRASP_NOBL.h` / `GRASP_NOBL.cpp` / `GRASP_SIBL.h` / `GRASP_SIBL.cpp``**: Algoritmo GRASP con versión sin búsqueda local (`GRASP_NOBL`) y con búsqueda local (`GRASP_SIBL`), usando listas restringidas de candidatos.

- **`src/localsearch.cpp`**  
  Centraliza la implementación de la búsqueda local utilizada por varios algoritmos, incluyendo la exploración de vecinos y el refinamiento.

- **`main.cpp`**  
  Punto de entrada principal del proyecto. Permite lanzar los distintos algoritmos sobre el conjunto de datos especificado.

- **`script.sh`**  
  Script auxiliar que compila y ejecuta el proyecto de forma automatizada. Se puede lanzar con o sin parámetro de semilla para experimentos reproducibles.

## Compilación y Ejecución

Para compilar y ejecutar el proyecto, basta con usar el script:

```bash
./script.sh [semilla]


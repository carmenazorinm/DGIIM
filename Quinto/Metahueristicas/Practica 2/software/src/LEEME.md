# Proyecto Metaheurísticas - Algoritmos Genéticos y Meméticos

Este proyecto sigue la estructura de la plantilla proporcionada por el profesor disponible en [https://github.com/dmolina/template_mh](https://github.com/dmolina/template_mh).

## Estructura del Proyecto

- **`build/`**  
  Esta carpeta se genera automáticamente al compilar el proyecto (usando `cmake` y `make`). Contiene los archivos binarios generados y también los resultados de las ejecuciones en archivos como `resultados_conjuntoDatos.txt`.

- **`inc/snimp_problem.h`**  
  Contiene la clase `Snimp`, que hereda de la clase base `Problem`. Define los métodos para crear soluciones aleatorias, calcular el fitness y aplicar heurísticas por nodo.

- **`inc/graph.h`** y **`src/graph.cpp`**  
  Implementan la clase `Graph`, que se encarga de leer archivos de texto con las aristas del grafo y convertirlos en listas de adyacencia (vecinos por nodo).

- **`inc/greedy.h`**, **`src/greedy.cpp`**  
  Implementan el algoritmo `GreedySearch`.

- **`inc/randomsearch.h`**, **`src/randomsearch.cpp`**  
  Implementan el algoritmo `RandomSearch`.

- **`inc/blsmall.h`** y **`inc/lsall.h`**  
  Definen los algoritmos de búsqueda local `BLsmall` y `LSall`. La implementación se encuentra en `src/localsearch.cpp`, junto con la función auxiliar `buscar_vecinos_aleatorios`.

  - En esta práctica, la clase `BLsmall` se ha modificado para heredar de `MHTrayectory`, permitiendo aplicar búsqueda local desde soluciones completas.

- **Algoritmos Genéticos y Meméticos (`inc/`)**:
  - `AGG1.h`: AGG sin orden (cruce 2 puntos + reparación)
  - `AGG2.h`: AGG con orden
  - `AGE1.h`: AGE con orden
  - `AGE2.h`: AGE sin orden
  - `AM1.h`, `AM2.h`, `AM3.h`: tres variantes de algoritmos meméticos

- **`src/`**  
  Contiene las implementaciones `.cpp` correspondientes a los algoritmos definidos en `inc/`.

- **`main.cpp`**  
  Archivo principal que inicializa los algoritmos y los ejecuta sobre los datos.

- **`script.sh`**  
  Script que automatiza la compilación y ejecución del programa. Puede usarse con o sin parámetro de semilla.

## Compilación y Ejecución

El script `script.sh` automatiza el flujo completo:

### Variables

```bash
BUILD_DIR=~/Documentos/Quinto-DGIIM/MH/template_mh/build
OUTPUT_FILE=resultados_p2p-Gnutella25.txt
```


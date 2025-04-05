# Estructura del código

El código está estructurado como la plantilla proporcionada por el profesor en [https://github.com/dmolina/template_mh](https://github.com/dmolina/template_mh). A continuación se describe la estructura general del proyecto:

- **Carpeta `build/`**: Se genera cuando se ejecuta el script de compilación (usando `cmake` y `make`), y contiene los archivos compilados necesarios para ejecutar el programa. Además, ahí se guardan los archivos resultados de cada ejecución
- **Archivo `inc/snimp_problem.h`**: Contiene la declaración de la clase `Snimp`, que es una subclase de la clase `Problem`. Esta clase define los métodos de creación de soluciones aleatorias, la evaluación del fitness y la heurística de cada nodo.
- **Archivos `inc/graph.h` y `src/graph.cpp`**: Contienen la declaración e implementación de la clase `Graph`. Esta clase se encarga de leer el archivo de texto que contiene las aristas del grafo y convertirlo a listas de adyacencia, donde cada nodo se asocia con un vector de sus nodos vecinos.
- **Archivos `inc/greedy.h` y `inc/randomsearch.h`**: Definen las clases `GreedySearch` y `RandomSearch`, que implementan los algoritmos correspondientes. Las clases se implementan en los archivos `src/greedy.cpp` y `src/randomsearch.cpp`.
- **Archivos `inc/blsmall.h` y `inc/lsall.h`**: Definen las clases `BLsmall` y `LSall`, que implementan los algoritmos de búsqueda local. Las funciones `optimize` de ambas clases se implementan en el archivo `src/localsearch.cpp`, junto a la función auxiliar `buscar_vecinos_aleatorios` para generar soluciones vecinas aleatorias.
- **Archivo `main.cpp`**: Se inicializan los objetos de los diferentes algoritmos y se ejecutan.
- **Archivo `script.sh`**: Automatiza el proceso de compilación y ejecución del programa. Se le puede llamar con o sin parámetro de semilla.

Cabe destacar que si se quiere ejecutar un conjunto de datos concreto, como `p2p\-Gnutella25.txt`, debemos cambiar el nombre del archivo en el `main.cpp`. Además, para guardar los resultados en el archivo de salida correspondiente, en el script debemos indicar el `OUTPUT\_FILE` al nombre que se le quiera dar. El archivo de salida se guardará en la carpeta autogenerada `build`.

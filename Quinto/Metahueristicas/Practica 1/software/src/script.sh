#!/bin/bash

# Variables
BUILD_DIR=~/Documentos/Quinto-DGIIM/MH/template_mh/build
OUTPUT_FILE=resultados_ca-GrQc.txt

# Comprobar si el usuario proporcionó una semilla como argumento
if [ -n "$1" ]; then
  SEED=$1
else
  SEED=42  # Valor por defecto
fi

echo "Usando semilla inicial: $SEED"

# Ir al directorio de build
cd "$BUILD_DIR" || exit 1

# Compilar
cmake -DCMAKE_BUILD_TYPE=Debug .
make

# Archivo de salida
echo "seed algoritmo best_solution best_fitness evaluations time_ms" > "$OUTPUT_FILE"

# Ejecutar y guardar resultados
contador_algoritmos=0

./main "$SEED" | while read -r line; do
  # Si detectamos un algoritmo
  if [[ "$line" == RandomSearch* || "$line" == Greedy* || "$line" == LSall* || "$line" == BLsmall* ]]; then
    algoritmo=$line
    read -r sol_line
    read -r fitness_line
    read -r evals_line
    read -r time_line

    # Parsear los valores de la solución, fitness, evaluaciones y tiempo
    best_solution=$(echo "$sol_line" | cut -d':' -f2 | xargs)
    best_fitness=$(echo "$fitness_line" | cut -d':' -f2 | xargs)
    evaluations=$(echo "$evals_line" | cut -d':' -f2 | xargs)
    time_ms=$(echo "$time_line" | cut -d':' -f2 | xargs | sed 's/ ms//')  # Eliminar " ms" del tiempo

    # Guardar línea en el archivo
    echo "$SEED $algoritmo \"$best_solution\" $best_fitness $evaluations $time_ms" >> "$OUTPUT_FILE"

    # Aumentar contador y semilla cada 4 algoritmos
    ((contador_algoritmos++))
    if (( contador_algoritmos % 4 == 0 )); then
      ((SEED++))
    fi
  fi
done

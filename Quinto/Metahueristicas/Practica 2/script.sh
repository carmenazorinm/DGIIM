#!/bin/bash

BUILD_DIR=~/Documentos/Quinto-DGIIM/MH/template_mh/build
OUTPUT_FILE=resultados_ca-GrQc.txt

if [ -n "$1" ]; then
  SEED=$1
else
  SEED=42
fi

echo "Usando semilla inicial: $SEED"

cd "$BUILD_DIR" || exit 1
cmake -DCMAKE_BUILD_TYPE=Debug .
make

echo "seed algoritmo ejecucion best_solution best_fitness evaluations time_ms" > "$OUTPUT_FILE"

./main "$SEED" | while read -r line; do
  if [[ "$line" == Algoritmo:* ]]; then
    algoritmo=$(echo "$line" | cut -d':' -f2 | cut -d',' -f1 | xargs)
    ejecucion=$(echo "$line" | grep -oP 'Ejecución: \K[0-9]+')
    semilla=$(echo "$line" | grep -oP 'Semilla: \K[0-9]+')

    read -r sol_line
    read -r fitness_line
    read -r evals_line
    read -r time_line

    best_solution=$(echo "$sol_line" | cut -d':' -f2 | xargs)
    best_fitness=$(echo "$fitness_line" | cut -d':' -f2 | xargs)
    evaluations=$(echo "$evals_line" | cut -d':' -f2 | xargs)
    time_ms=$(echo "$time_line" | cut -d':' -f2 | xargs | sed 's/ ms//')

    echo "$semilla $algoritmo $ejecucion \"$best_solution\" $best_fitness $evaluations $time_ms" >> "$OUTPUT_FILE"
  fi
done

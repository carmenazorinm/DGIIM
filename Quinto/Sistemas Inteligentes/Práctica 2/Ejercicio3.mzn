include "globals.mzn";

% deifniciones generales
set of int: FILAS = 1..12;
set of int: COLS = 1..12;
int: k = 6;

% definicion de las variables
array[FILAS,COLS] of var 0..1: matriz;

% matriz inicial
constraint matriz[1,2] = 1;
constraint matriz[1,3] = 0;
constraint matriz[1,8] = 0;
constraint matriz[1,11] = 0;
constraint matriz[2,2] = 1;
constraint matriz[2,3] =1;
constraint matriz[2,6] = 1;
constraint matriz[3,9] = 1;
constraint matriz[3,12] = 0;
constraint matriz[4,3] = 0;
constraint matriz[4,4] = 0;
constraint matriz[4,12] = 0;
constraint matriz[5,7] = 1;
constraint matriz[5,8] = 1;
constraint matriz[5,10] = 0;
constraint matriz[6,2] = 1;
constraint matriz[6,4] = 0;
constraint matriz[6,6] = 1;
constraint matriz[6,7] = 1;
constraint matriz[6,11] = 1;
constraint matriz[7,9] = 1;
constraint matriz[8,1] = 1;
constraint matriz[8,4] = 1;
constraint matriz[8,11] = 0;
constraint matriz[9,2] = 1;
constraint matriz[9,9] = 0;
constraint matriz[10,8] = 0;
constraint matriz[11,1] = 1;
constraint matriz[11,12] = 1;
constraint matriz[12,2] = 1;
constraint matriz[12,4] = 1;
constraint matriz[12,10] = 0;
constraint matriz[12,11] = 0;

% Cada fila y cada columna debe contener el mismo número de ceros que de unos.
constraint forall(i in FILAS)(sum(j in COLS)(matriz[i,j])==k);
constraint forall(j in COLS)(sum(i in FILAS)(matriz[i,j])==k);

% Ninguna fila puede ser idéntica a ninguna otra fila, ni ninguna columna puede ser idéntica a ninguna otra columna.
constraint forall(f1,f2 in FILAS where f1<f2)(exists(j in COLS)(matriz[f1,j] != matriz[f2,j]));

constraint forall(c1,c2 in COLS where c1<c2)(exists(i in FILAS)(matriz[i,c1] != matriz[i,c2]));

% Ninguna fila contiene 3 o más valores consecutivos iguales.
constraint forall(f in FILAS)(forall(c in 1..10)(matriz[f,c]!=matriz[f,c+1] \/ matriz[f,c+1]!=matriz[f,c+2] \/ matriz[f,c]!=matriz[f,c+2])); 

constraint forall(c in COLS)(forall(f in 1..10)(matriz[f,c]!=matriz[f+1,c] \/ matriz[f+1,c]!=matriz[f+2,c] \/ matriz[f,c]!=matriz[f+2,c])); 

% resolvemos
solve satisfy;

% output propuesto por chatgpt
output [
  if c = 1 then "\n" else " " endif ++
  show(matriz[r,c])
  | r in FILAS, c in COLS
];

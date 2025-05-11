include "globals.mzn";

% definiciones generales
int: x=120;
set of int: valores = 1..x-1;

% definicion de variables
array[valores] of var 0..1: S;

% definicion de numero perfecto
constraint sum(i in valores)(S[i]*i*i)=x*x;

% definicion de cardinalidad
var int: cardinalidad = sum(i in valores)(S[i]);

% resolvemos
solve maximize cardinalidad;

% output propuesto por chatgpt
output [
  "x = ", show(x), "\n",
  "S = {", 
  concat([if fix(S[i]) == 1 then show(i) ++ ", " else "" endif | i in valores]),
  "}\n",
  "Cardinalidad = ", show(cardinalidad)
];
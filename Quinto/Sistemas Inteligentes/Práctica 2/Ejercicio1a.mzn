include "globals.mzn";

% definicion de monedas y cantidad de monedas
array[1..9] of int: monedas = [1,3,5,10,25,50,100,200,500];
array[1..9] of var int: solucion;
int: importe = 527; % importe en centimos

% las monedas deben sumar el importe
constraint sum(i in 1..9)(solucion[i]*monedas[i]) == importe;

% la cantidad de monedas es positiva
constraint forall(i in 1..9)(solucion[i]>-1);

% definición de la cantidad de monedas totales
var int: total_monedas = sum(i in 1..9)(solucion[i]);

% resolvemos
solve satisfy;

% salida
output [
  "monedas = ", show(solucion), "\n",
  "total monedas = ", show(total_monedas)
];
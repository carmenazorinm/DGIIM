include "globals.mzn";

% deifnimos las monedas y la cantidad de monedas como valores flotantes
array[1..9] of float: monedas = [1,3,5,10,25,50,100,200,500];
array[1..9] of var float: solucion;
float: importe = 13;

% la suma de las monedas debe dar el importe
constraint sum(i in 1..9)(solucion[i]*monedas[i]) == importe;

% la cantidad de monedas debe ser positiva
constraint forall(i in 1..9)(solucion[i]>=0);

% cantidad de monedas totales
var float: total_monedas = sum(i in 1..9)(solucion[i]);

% resolvemos
solve satisfy;

% salida
output [
  "monedas = ", show(solucion), "\n",
  "total monedas = ", show(total_monedas)
];
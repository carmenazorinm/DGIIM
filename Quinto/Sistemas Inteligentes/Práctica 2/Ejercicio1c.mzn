include "globals.mzn";

% definicion de monedas y cantidad de monedas
array[1..9] of int: monedas = [1,3,5,10,25,50,100,200,500];
array[1..9] of var int: solucion;
int: importe = 299; %importe en centimos

% forzar que la parte entera se asigne a monedas de >= 100
constraint importe-monedas[7]*solucion[7]-monedas[8]*solucion[8]-monedas[9]*solucion[9] < 100;

% las monedas deben sumar el importe
constraint sum(i in 1..9)(solucion[i]*monedas[i]) == importe;

% la cantidad de monedas debe ser positivo o cero
constraint forall(i in 1..9)(solucion[i]>-1);

% cantidad de monedas totales
var int: total_monedas = sum(i in 1..9)(solucion[i]);

% minimizamos el total de monedas
solve minimize total_monedas;

% salida
output [
  "monedas = ", show(solucion), "\n",
  "total monedas = ", show(total_monedas)
];
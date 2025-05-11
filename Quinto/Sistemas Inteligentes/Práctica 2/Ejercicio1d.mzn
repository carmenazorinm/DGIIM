include "globals.mzn";

% definicion de monedas y cantidad de monedas
array[1..9] of int: monedas = [1,3,5,10,25,50,100,200,500];
array[1..9] of var int: solucion;
int: importe = 122233367; % importe en centimos

constraint solucion[1]<monedas[2]; % no puede haber más de 2 monedas de 1 -> se pone moneda de 3
constraint solucion[3]<2; % no puede haber más de 1 monedas de 5 -> se pone moneda de 10
constraint solucion[5]<2; % no puede haber más de 1 moneda de 25 -> se pone moneda de 50

% calculamos la cantidad de monedas de 500
constraint floor(importe / monedas[9]) = solucion[9];

% la parte entera se paga con monedas de unidad
constraint importe-monedas[7]*solucion[7]-monedas[8]*solucion[8]-monedas[9]*solucion[9] < 100;

% la suma de monedas debe ser el importe
constraint sum(i in 1..9)(solucion[i]*monedas[i]) == importe;

% la cantidad de monedas debe ser positiva o cero
constraint forall(i in 1..9)(solucion[i]>-1);

% cantidad de monedas totales
var int: total_monedas = sum(i in 1..9)(solucion[i]);

% resolvemos
solve satisfy;

% salida
output [
  "monedas = ", show(solucion), "\n",
  "total monedas = ", show(total_monedas)
];
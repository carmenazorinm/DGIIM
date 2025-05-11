include "globals.mzn";

% definicion de las ciudades y las parejas
enum CIUDAD = {Madrid, Barcelona, Sevilla, Lyon, Parma};
enum P1 = {Lucia, Sofia, Juan, Cristina, Claudia};
enum P2 = {Pablo, Marcos, Jose, Marta, Pedro};
set of int: ANIOS = {5, 10, 15, 20, 25, 30};  % Seis posibles años -> Propuesta de chatgpt

% variables a calcular
array[P1] of var ANIOS: orden_parejas1;
array[P2] of var ANIOS: orden_parejas2;
array[CIUDAD] of var ANIOS: orden_ciudades;

% restricciones generales
constraint all_different(orden_parejas1);
constraint all_different(orden_parejas2);
constraint all_different(orden_ciudades);

% Sofía no lleva casada tanto tiempo como José o los de Barcelona, pero sí más que
% Marcos o los Madrid.
constraint orden_parejas1[Sofia] < orden_parejas2[Jose];
constraint orden_parejas1[Sofia] < orden_ciudades[Barcelona];
constraint orden_parejas1[Sofia] > orden_parejas2[Marcos];
constraint orden_parejas1[Sofia] > orden_ciudades[Madrid];
 
% Cristina lleva casada el doble de tiempo que los de Sevilla, pero solo la mitad que
% Pablo.
constraint orden_parejas1[Cristina] == 2*orden_ciudades[Sevilla];
constraint orden_parejas1[Cristina] == orden_parejas2[Pablo]/2;

% Los de Parma llevan casados diez años más que Marta y diez años menos que Juan.
constraint orden_ciudades[Parma] == 10 + orden_parejas2[Marta];
constraint orden_ciudades[Parma] == orden_parejas1[Juan] - 10;

% Marcos y Claudia llevan 25 años menos de casados que los de Lyon, quienes, con 30
% años de casados, son la pareja que lleva más tiempo casada.
constraint orden_parejas2[Marcos] == orden_parejas1[Claudia];
constraint orden_parejas2[Marcos] == orden_ciudades[Lyon] - 25;
constraint orden_ciudades[Lyon] == 30;
constraint forall(ciudad in CIUDAD)(orden_ciudades[ciudad] <= orden_ciudades[Lyon]);

% Ni Lucía ni los de Madrid son los que llevan casados menos tiempo.
constraint exists(pareja in P1)(orden_parejas1[Lucia]>orden_parejas1[pareja]);
constraint exists(ciudad in CIUDAD)(orden_ciudades[Madrid] > orden_ciudades[ciudad]);

% Pedro lleva 25 años casado.
constraint orden_parejas2[Pedro] == 25;

% los números deben coincidir
constraint forall(p1 in P1)(exists (p2 in P2)(orden_parejas1[p1]==orden_parejas2[p2]));
constraint forall(p1 in P1)(exists (c in CIUDAD)(orden_parejas1[p1]==orden_ciudades[c]));

% resolvemos
solve satisfy;

% output pedido a chatgpt aunque con retoques propios como el fix()
output [
  if fix(orden_parejas1[p1]) == fix(orden_parejas2[p2]) /\ fix(orden_parejas1[p1]) == fix(orden_ciudades[c]) then
    show(c)++ ": " ++ show(p1) ++ " y " ++ show(p2) ++ " " ++ show(orden_parejas1[p1]) ++ " años\n"
  else ""
  endif
  | p1 in P1, p2 in P2, c in CIUDAD
];

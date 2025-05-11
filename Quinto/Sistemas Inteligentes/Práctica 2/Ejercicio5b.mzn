include "globals.mzn";

% definiciones generales
int: tiempo_minimo = 27; % numero sacado del apartado a
enum Tarea = {A,B,C,D,E,F,G,H,I,J};
enum Trabajadores = {Marty, Doc, Biff};

array [Tarea] of set of Tarea:
  Predecesoras = [{},{A},{B},{A,C},{C},{C,D,E},{C,D},{G},{F,H},{G,I}];

% duracion de las tareas por cada trabajador
array[Tarea] of int: duracion_marty = [10,1,4,15,14,13,7,3,2,4];
array[Tarea] of int: duracion_doc = [16,2,3,5,3,5,6,4,2,2];

% definicion de variables
array[Tarea] of var 1..100: inicio;
array[Tarea] of var 1..100: fin;
array[Tarea] of var 0..1: asignacion_marty; %1 si marty, 0 si doc
array[Tarea] of var 0..1: conBiff; % 1 si apoya Biff, 0 si no

% Restriccion de tiempos de finalizacion
constraint forall(t in Tarea) (
  fin[t] = inicio[t] + 
    if asignacion_marty[t]=1 then
      if conBiff[t] = 1 then 
        if duracion_marty[t] >= 3 then 
          duracion_marty[t] - (if t in {A,C,H} then 2 else 1 endif) 
        else duracion_marty[t] 
        endif
      else
        duracion_marty[t]
      endif
    else
      if conBiff[t] = 1 then
        if duracion_doc[t] >= 3 then
          duracion_doc[t] - (if t in {A,C,H} then 2 else 1 endif)
        else duracion_doc[t]
        endif
      else 
        duracion_doc[t]
      endif
    endif    
);

% la tarea tiene que terminar antes que su predecesora
constraint forall(t in Tarea, p in Predecesoras[t]) (fin[p] <= inicio[t]);

% maximo 4 tareas con biff y no simultaneas
constraint sum(t in Tarea)(conBiff[t]) <= 4;
constraint forall(i,j in Tarea where i < j /\ conBiff[i] = 1 /\ conBiff[j]=1) (fin[i] <= inicio[j] \/ fin[j] <= inicio[i]);

% marty y doc no pueden hacer tareas simultaneaente
constraint forall(i,j in Tarea where i < j)
  (if asignacion_marty[i] = asignacion_marty[j] then
    fin[i] <= inicio[j] \/ fin[j] <= inicio[i] endif);
    
% minimizamos el tiempo total -> idea propuesta por chatgpt
constraint max([fin[t] | t in Tarea]) = tiempo_minimo;
solve satisfy;

% Salida
array[Tarea] of string: nombres_completos = [
    "Montar chasis",
    "Instalar ruedas",
    "Cableado eléctrico",
    "Motor de fusión nuclear",
    "Tablero de control",
    "Instalación y configuración del condensador de fluzo",
    "Ajuste aerodinámico",
    "Instalación de puertas de ala de gaviota",
    "Panel de tiempo",
    "Implementación y validación de algoritmos de búsqueda heurística"
];

% Output formateado
output [
    "Tiempo total: ", show(tiempo_minimo), " días\n",
    "Asignación de tareas:\n",
    concat([
        "\"" ++ nombres_completos[t] ++ "\" inicio día " ++ show(inicio[t]) ++ 
        " fin día " ++ show(fin[t]) ++ ". Asignada a " ++ 
        (if fix(asignacion_marty[t]) = 1 then "Marty" else "Doc" endif) ++ 
        (if fix(conBiff[t]) = 1 then " con apoyo de Biff" else "" endif) ++ "\n"
        | t in Tarea
    ])
];

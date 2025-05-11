include "globals.mzn";

% definicion de dias y profesores
enum dias = {lunes, martes, miercoles, jueves, viernes};
set of int: profesores = 1..9;
set of int: tfgs = 1..10;

% departamentos
set of int: DECSAI = 1..3;
set of int: LSI = 4..6;
set of int: ICAR = 7..9;

% agenda de disponibilidad
array[profesores] of set of dias: agenda =[{martes},{lunes, miercoles, viernes},
{lunes, miercoles, viernes}, {miercoles,jueves}, {lunes, jueves}, {lunes, martes, miercoles, jueves, viernes}, {viernes}, {miercoles, jueves}, {jueves}];

% tfgs supervisados
array[profesores] of set of tfgs: supervisados = [{},{1,10},{8,7},{6,4},{2},{3},{3},{4,7},{}];

% variables de decision
array[profesores] of var 0..1: tribunal1;
array[profesores] of var 0..1: tribunal2;
var dias: diaTribunal1;
var dias: diaTribunal2;
array[tfgs] of var 0..1: evaluaTribunal1;
array[tfgs] of var 0..1: evaluaTribunal2;

% cada tfg debe estar asignado a un tribunal
constraint forall(t in tfgs)(evaluaTribunal1[t] + evaluaTribunal2[t] = 1);

% 5 tfgs por tribunal -> hay 10 tfgs y 2 tribunales
constraint sum(t in tfgs)(evaluaTribunal1[t]) = 5;
constraint sum(t in tfgs)(evaluaTribunal2[t]) = 5;

% un profe no puede estar en dos tribunales, pero sí puede no estar en ninguno
constraint forall(profe in profesores)(tribunal1[profe] + tribunal2[profe] <= 1);

% cada tribunal debe tener un profesor de cada departamento
constraint sum(p in DECSAI)(tribunal1[p]) = 1 /\ sum(p in DECSAI)(tribunal2[p]) = 1;
constraint sum(p in LSI)(tribunal1[p]) = 1 /\ sum(p in LSI)(tribunal2[p]) = 1;
constraint sum(p in ICAR)(tribunal1[p]) = 1 /\ sum(p in ICAR)(tribunal2[p]) = 1;

% disponibilidad de profesores
constraint forall(profe in profesores where tribunal1[profe] =1)(diaTribunal1 in agenda[profe]);

constraint forall(profe in profesores where tribunal2[profe] =1)(diaTribunal2 in agenda[profe]);

% tfgs supervisados
constraint forall(profe in profesores)(
    tribunal1[profe] = 1 -> forall(tfg in supervisados[profe])(
        evaluaTribunal1[tfg] = 0
    )
);
constraint forall(profe in profesores)(
    tribunal2[profe] = 1 -> forall(tfg in supervisados[profe])(
        evaluaTribunal2[tfg] = 0
    )
);
% el mismo dia no puede haber dos tribunales ejerciendo
constraint diaTribunal1 != diaTribunal2;

% para que no haya simetrias -> que el tribunal1 tenga el indice del tfg mas bajo
constraint min([t | t in tfgs where evaluaTribunal1[t] = 1]) < min([t | t in tfgs where evaluaTribunal2[t] = 1]); 

% resolver
solve satisfy;

% output propuesto por chatgpt
function string: get_depto(int: p) =
    if p in DECSAI then "DECSAI"
    elseif p in LSI then "LSI"
    else "ICAR"
    endif;

output [
    "Tribunal 1: " ++ 
    concat([show(p) ++ "(" ++ get_depto(p) ++ "), " | p in profesores where fix(tribunal1[p]) = 1]) ++ 
    " (Día: " ++ show(fix(diaTribunal1)) ++ ")\n" ++
    "TFGs a evaluar: " ++ 
    concat([show(t) ++ ", " | t in tfgs where fix(evaluaTribunal1[t]) = 1]) ++ "\n\n" ++
    
    "Tribunal 2: " ++ 
    concat([show(p) ++ "(" ++ get_depto(p) ++ "), " | p in profesores where fix(tribunal2[p]) = 1]) ++ 
    " (Día: " ++ show(fix(diaTribunal2)) ++ ")\n" ++
    "TFGs a evaluar: " ++ 
    concat([show(t) ++ ", " | t in tfgs where fix(evaluaTribunal2[t]) = 1]) ++ ""
];

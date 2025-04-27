(defmodule pedir-informacion (export ?ALL) (import MAIN ?ALL))

(deffunction opcion-valida? (?valor $?validas)
   (return (member$ ?valor ?validas)))

;;; Preguntar restricción alimentaria (obligatoria)
(defrule preguntar-preferencia-alimentaria
   ?i <- (info-faltante (campo preferencia-alimentaria))
   =>
   (printout t crlf "¿Tiene alguna restricción alimentaria? (vegana / vegetariana / sin_lactosa / sin_gluten / ninguna): " crlf)
   (bind ?resp (lowcase (read)))
   (if (opcion-valida? ?resp (create$ vegana vegetariana sin_lactosa sin_gluten ninguna)) then
      (assert (preferencia-alimentaria (tipo ?resp)))
   else
      (printout t "Opción no válida. Se asumirá que no hay restricciones alimentarias." crlf)
      (assert (preferencia-alimentaria (tipo ninguna))))
   (retract ?i)
   (assert (justificacion (campo restriccion-alimentaria) (valor ?resp)))
)

;;; Preguntar si le gustaría que sea picante (opcional)
(defrule preguntar-picante
   ?i <- (info-faltante (campo preferencia-picante))
   =>
   (printout t crlf "¿Desea que la receta sea picante? (si / no / cualquiera): " crlf)
   (bind ?resp (lowcase (read)))
   (if (opcion-valida? ?resp (create$ si no cualquiera)) then
      (assert (preferencia-picante (desea ?resp)))
   else
      (printout t "No se aplicará ninguna preferencia de picante." crlf))
   (retract ?i)
   (assert (justificacion (campo picante) (valor ?resp)))
)

;;; Preguntar momento del día (opcional)
(defrule preguntar-momento
   ?i <- (info-faltante (campo momento))
   =>
   (printout t crlf "¿Para qué momento del día busca la receta? (desayuno / comida / postre / cualquiera): " crlf)
   (bind ?resp (lowcase (read)))
   (if (opcion-valida? ?resp (create$ desayuno comida postre cualquiera)) then
      (assert (momento (tipo ?resp)))
   else
      (printout t "No se aplicará ninguna preferencia de momento del día." crlf))
   (retract ?i)
   (assert (justificacion (campo momento) (valor ?resp)))
)

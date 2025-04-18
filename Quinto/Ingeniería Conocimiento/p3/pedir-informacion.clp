(defmodule pedir-informacion (export ?ALL) (import MAIN ?ALL))

(deffunction opcion-valida? (?valor $?validas)
   (return (member$ ?valor ?validas)))

;;; Preguntar restricción alimentaria
(defrule preguntar-preferencia-alimentaria
   ?i <- (info-faltante (campo preferencia-alimentaria))
   =>
   (printout t crlf "¿Tiene alguna restricción alimentaria? (vegana / vegetariana / sin_lactosa / sin_gluten / ninguna): " crlf)
   (bind ?resp (lowcase (read)))
   (if (opcion-valida? ?resp (create$ vegana vegetariana sin_lactosa sin_gluten ninguna)) then
      (assert (preferencia-alimentaria (tipo ?resp)))
      (retract ?i)
   else
      (printout t "Opción no válida. No se tendrá en cuenta esta respuesta." crlf))

)

;;; Preguntar si le gustaría que sea picante
(defrule preguntar-picante
   ?i <- (info-faltante (campo preferencia-picante))
   =>
   (printout t crlf "¿Desea que la receta sea picante? (si / no): " crlf)
   (bind ?resp (lowcase (read)))
   (if (opcion-valida? ?resp (create$ si no)) then
      (assert (preferencia-picante (desea ?resp)))
      (retract ?i)
   else
      (printout t "Opción no válida. No se tendrá en cuenta esta respuesta." crlf))

)

;;; Preguntar momento del día
(defrule preguntar-momento
   ?i <- (info-faltante (campo momento))
   =>
   (printout t crlf "¿Para qué momento del día busca la receta? (desayuno / comida / postre): " crlf)
   (bind ?resp (lowcase (read)))
   (if (opcion-valida? ?resp (create$ desayuno comida postre)) then
      (assert (momento (tipo ?resp)))
      (retract ?i)
   else
      (printout t "Opción no válida. No se tendrá en cuenta esta respuesta." crlf))

)
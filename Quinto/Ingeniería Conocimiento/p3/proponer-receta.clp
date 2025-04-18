(defmodule proponer-receta (export ?ALL) (import MAIN ?ALL))

(deffunction contar-recomendaciones ()
   (bind ?n 0)
   (do-for-all-facts ((?r recomendacion)) TRUE
      (bind ?n (+ ?n 1)))
   (return ?n)
)

(defrule detectar-variedad-dificultad
   (declare (salience 90))
   (recomendacion (receta ?r1))
   (receta (nombre ?n1) (dificultad ?d1))
   (compatible ?n2&:(neq ?n1 ?n2))
   (receta (nombre ?n2) (dificultad ?d2&:(neq ?d1 ?d2)))
   =>
   (assert (necesita-preguntar-dificultad))
)

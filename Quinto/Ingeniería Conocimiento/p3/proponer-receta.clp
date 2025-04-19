(defmodule proponer-receta (export ?ALL) (import MAIN ?ALL))

(defrule proponer-receta-inicial
(declare (salience 100))
   (propuesta (receta ?rec-fact))
   =>
   (bind ?nombre       (fact-slot-value ?rec-fact nombre))
   (bind ?ingredientes (fact-slot-value ?rec-fact ingredientes))
   (bind ?dificultad   (fact-slot-value ?rec-fact dificultad))
   (bind ?duracion     (fact-slot-value ?rec-fact duracion))

   (printout t crlf "🍽️ ¿Qué te parece esta receta?: " ?nombre crlf)
   (printout t "📋 Ingredientes: " (implode$ ?ingredientes) crlf)
   (printout t "📊 Dificultad: " ?dificultad crlf)
   (printout t "⏱️ Tiempo estimado: " ?duracion crlf)

   (printout t crlf "¿Te gusta o quieres cambiar algo?" crlf)
   (printout t "(Responde: ninguno / dificultad / evitar alimento / priorizar alimento / tiempo): ")
   (bind ?resp (lowcase (read)))
   (assert (respuesta-cambio ?resp))
   
   )


(defrule aceptar-receta
(declare (salience 90))
   (propuesta (receta ?rec-fact))
   (respuesta-cambio ninguno)
   =>
   (bind ?nombre (fact-slot-value ?rec-fact nombre))
   (assert (aceptada aceptada))
   (printout t crlf "🎉 ¡Perfecto! Disfruta la receta " ?nombre crlf)
)

; si quiere cambair la dificultad
(defrule cambiar-por-dificultad
(declare (salience 90))
   ?rc <- (respuesta-cambio dificultad)
   =>
   (printout t "¿Qué dificultad prefieres? (muy_baja / baja / media / alta): ")
   (bind ?dif (read))
   (assert (dificultad-preferida ?dif))
   (retract ?rc)
)

(defrule filtrar-por-dificultad
   (declare (salience 80))
   (dificultad-preferida ?dif)
   ?r <- (recomendacion (receta ?rec-fact))
   (test (neq (fact-slot-value ?rec-fact dificultad) ?dif))
   =>
   (bind ?nombre (fact-slot-value ?rec-fact nombre))
   (printout t "❌ Elimino la receta por DIFICULTAD: " ?nombre crlf)
   (retract ?r)
)

(defrule eliminar-dificultad
(declare (salience 77))
?d <- (dificultad-preferida ?dif)
=>
(retract ?d)
)


; si quiere evitar un alimento
(defrule cambiar-por-evitar
(declare (salience 90))
   ?rc <- (respuesta-cambio evitar)
   =>
   (printout t "¿Qué ingrediente quieres evitar?: ")
   (bind ?ing (read))
   (assert (evitar-ingrediente ?ing))
   (retract ?rc)
)

(defrule filtrar-por-ingrediente-evitado
   (declare (salience 80))
   (evitar-ingrediente ?ing)
   ?r <- (recomendacion (receta ?rec-fact))
   (test (member$ ?ing (fact-slot-value ?rec-fact ingredientes)))
   =>
   (bind ?nombre (fact-slot-value ?rec-fact nombre))
   (printout t "❌ Elimino la receta por INGREDIENTE evitado: " ?nombre crlf)
   (retract ?r)
)

(defrule eliminar-evitar-ing
(declare (salience 77))
?e <- (evitar-ingrediente ?ing)
=>
(retract ?e)
)


; si quiere priorizar un ingrediente
(defrule cambiar-por-priorizar
   (declare (salience 90))
   ?rc <- (respuesta-cambio priorizar)
   =>
   (printout t "¿Qué ingrediente te gusta especialmente?: ")
   (bind ?ing (read))
   (assert (ingrediente-preferido ?ing))
   (retract ?rc)
)

(defrule filtrar-por-prioridad
   (declare (salience 80))
   (ingrediente-preferido ?ing)
   ?r <- (recomendacion (receta ?rec-fact))
   (test (not (member$ ?ing (fact-slot-value ?rec-fact ingredientes))))
   =>
   (bind ?nombre (fact-slot-value ?rec-fact nombre))
   (printout t "❌ Elimino la receta por NO tener el ingrediente preferido (" ?ing "): " ?nombre crlf)
   (retract ?r)
)

(defrule limpiar-ingrediente-preferido
   (declare (salience 77))
   ?e <- (ingrediente-preferido ?)
   =>
   (retract ?e)
)

; si quiere filtrar por tiempo
(defrule cambiar-por-tiempo
(declare (salience 90))
   ?rc <- (respuesta-cambio tiempo)
   =>
   (printout t "¿Cuál es la duración máxima que prefieres (en minutos)?: ")
   (bind ?max (read))
   (assert (duracion-maxima ?max))
   (retract ?rc)
)

(defrule filtrar-por-duracion
   (declare (salience 80))
   (duracion-maxima ?max)
   ?r <- (recomendacion (receta ?rec-fact))
   (test (numberp (eval (sub-string 1 (- (str-length (fact-slot-value ?rec-fact duracion)) 1) (fact-slot-value ?rec-fact duracion)))))
   (test (> (eval (sub-string 1 (- (str-length (fact-slot-value ?rec-fact duracion)) 1) (fact-slot-value ?rec-fact duracion))) ?max))
   =>
   (bind ?nombre (fact-slot-value ?rec-fact nombre))
   (bind ?dur-str (fact-slot-value ?rec-fact duracion))
   (printout t "❌ Elimino la receta por DURACIÓN: " ?nombre " (" ?dur-str ")" crlf)
   (retract ?r)
)

(defrule eliminar-diracion
(declare (salience 77))
?f <- (duracion-maxima ?max)
=>
(retract ?f)
)


; si no quedan recetas compatibles con las especificaciones
(defrule sin-recetas-disponibles
(declare (salience 70))
   ;?e <- (estado recomendar)
   (not (recomendacion (receta ?)))
   (not (aceptada aceptada))
   =>
   (printout t crlf "❌ No hay recetas que cumplan con esas restricciones." crlf)

   )

; finalizar
(defrule limpiar-propuesta-y-volver
   ?p <- (propuesta (receta ?))
   =>
   (retract ?p)
   (focus MAIN))


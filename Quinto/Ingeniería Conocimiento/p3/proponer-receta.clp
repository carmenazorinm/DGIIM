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
   ?p <- (propuesta (receta ?rec-fact))
   (respuesta-cambio ninguno)
   ?e <- (estado recomendar)
   =>
   (bind ?nombre (fact-slot-value ?rec-fact nombre))
   (printout t crlf "🎉 ¡Perfecto! Disfruta la receta " ?nombre crlf)
   (assert (aceptada aceptada))
   (assert (estado justificar-con-receta))
   (retract ?e)
   (retract ?p)
)


; si quiere cambair la dificultad
(defrule cambiar-por-dificultad
(declare (salience 90))
   ?rc <- (respuesta-cambio dificultad)
   (not (dificultad-preferida ?))
   =>
   (printout t "¿Qué dificultad prefieres? (muy_baja / baja / media / alta): ")
   (bind ?dif (read))
   (assert (dificultad-preferida ?dif))
   (retract ?rc)
   (assert (justificacion (campo dificultad) (valor ?dif)))
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
   (declare (salience 91))
   ?rc <- (respuesta-cambio dificultad)
   (dificultad-preferida ?dif)
   =>
   (printout t "Ya se ha indicado que se busca la dificultad: " ?dif crlf)
   (retract ?rc)
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
   (assert (justificacion (campo alimento-evitado) (valor ?ing)))
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
   (assert (justificacion (campo alimento-priorizado) (valor ?ing)))
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
   (assert (justificacion (campo tiempo-max) (valor ?max)))
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

(defrule eliminar-duracion
(declare (salience 91))
?rc <- (respuesta-cambio tiempo)
?f <- (duracion-maxima ?max)
=>
(printout t "Ya se ha indicado que la duración máxima es de " ?max " minutos."crlf)
(retract ?rc)
)


; si no quedan recetas compatibles con las especificaciones
(defrule sin-recetas-disponibles
(declare (salience 70))
   ;?e <- (estado recomendar)
   (not (recomendacion (receta ?)))
   (not (aceptada aceptada))
   =>
   (printout t crlf "⚠️  No se encontró ninguna receta compatible con tus preferencias." crlf)
   (assert (estado justificar-sin-receta))
   )

; finalizar y proponer la siguiente receta
(defrule limpiar-propuesta-y-volver
   ?p <- (propuesta (receta ?))
   =>
   (retract ?p)
   (focus MAIN))

; hacer la justifiación necesaria
(defrule justificar-con-receta
(declare (salience 60))
   ?e <- (estado justificar-con-receta)
   =>
   (retract ?e)
   (printout t crlf "📝 Justificación de la recomendación: " crlf)
   (do-for-all-facts ((?j justificacion)) TRUE
      (printout t "- Se tuvo en cuenta el " ?j:campo ": " ?j:valor crlf))
)

(defrule justificar-sin-receta
(declare (salience 60))
   ?e <- (estado justificar-sin-receta)
   =>
   (retract ?e)
   (printout t crlf "📝 Justificación del resultado:" crlf)
   (do-for-all-facts ((?j justificacion)) TRUE
      (printout t "- Se tuvo en cuenta el " ?j:campo ": " ?j:valor crlf))
   (printout t "🔍 Sin embargo, no se encontraron recetas que cumplieran con todas las preferencias indicadas." crlf)
)

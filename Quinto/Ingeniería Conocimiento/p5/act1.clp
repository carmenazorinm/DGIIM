; CARMEN AZORÍN MARTÍ

(deffacts datos 
    (ave gorrion) (ave paloma) (ave aguila) (ave pinguino)
    (mamifero vaca) (mamifero perro) (mamifero caballo)
    (vuela pinguino no seguro)
     (explicacion vuela pinguino "sabemos que el pinguino no vuela porque es un ave no voladora")
)

(defrule aves_son_animales
    (ave ?x)
    =>
    (assert (animal ?x))
    (bind ?expl (str-cat "sabemos que un "?x " es un animal porque las aves son un tipo de animal"))
    (assert (explicacion animal ?x ?expl))
)

(defrule mamiferos_son_animales
    (mamifero ?x)
    =>
    (assert (animal ?x))
    (bind ?expl (str-cat "sabemos que un " ?x " es un animal porque los mamiferos son un tipo de animal"))
    (assert (explicacion animal ?x ?expl))    
)

(defrule ave_vuela_por_defecto
    (declare (salience -1))
    (ave ?x)
    (not (vuela ?x ? ?)) ; para que no se asuma algoq ue ya sabemos
    =>
    (assert (vuela ?x si por_defecto))
    (bind ?expl (str-cat "asumo que un " ?x " vuela porque casi todas las aves vuelan"))
    (assert (explicacion vuela ?x ?expl))
)

(defrule retracta_vuela_por_defecto
    (declare (salience 1))
    ?f <- (vuela ?x ?r por_defecto)
    (vuela ?x ?s seguro)
    =>
    (retract ?f)
    (bind ?expl (str-cat "retractamos que un " ?x ?r " vuela por defecto, porque sabemos seguro que " ?x ?s " vuela"))
    (assert (explicacion retracta_vuela ?x ?expl))
)

(defrule mayor_parte_animales_no_vuelan
    (declare (salience -2))
    (animal ?x)
    (not (vuela ?x ? ?))
    =>
    (assert (vuela ?x no por_defecto))
    (bind ?expl (str-cat "asumo que " ?x " no vuela, porque la mayoria de los animales no vuelan"))
    (assert (explicacion vuela ?x ?expl))
)

; Definimos reglas que nos sirven para preguntar al usuario
(defrule pedir_animal
    =>
    (printout t "¿De qué animal quieres saber si vuela? " crlf)
    (bind ?nombre (read))
    (assert (consulta ?nombre))
)

(defrule preguntar_si_es_ave
    (consulta ?x)
    (not (animal ?x))
    (not (ave ?x))
    (not (mamifero ?x))
    =>
    (printout t "No conozco a " ?x ". Indica si es ave/mamifero/desconocido: ")
    (bind ?resp (read))
    (if (eq ?resp ave) then
        (assert (ave ?x))
        (assert (animal ?x))
        (assert (vuela ?x si por_defecto))
    )
    (if (eq ?resp mamifero) then
        (assert (mamifero ?x))
        (assert (animal ?x))
        (assert (vuela ?x no por_defecto))
    )
    (if (and (neq ?resp ave) (neq ?resp mamifero)) then
        (assert (animal ?x))
        (assert (vuela ?x no por_defecto))
    )
)

; mostramos la respuesta
(defrule mostrar_respuesta_si
    (consulta ?x)
    (vuela ?x si ?modo)
    =>
    (printout t ?x " vuela (" ?modo ")" crlf)
)

(defrule mostrar_explicacion_si
    (consulta ?x)
    (vuela ?x si ?)
    (explicacion vuela ?x ?e)
    =>
    (printout t "Explicación: " ?e crlf)
)

(defrule mostrar_respuesta_no
    (consulta ?x)
    (vuela ?x no ?modo)
    =>
    (printout t ?x " no vuela (" ?modo ")" crlf)
)

(defrule mostrar_explicacion_no
    (consulta ?x)
    (vuela ?x no ?)
    (explicacion vuela ?x ?e)
    =>
    (printout t "Explicación: " ?e crlf)
)



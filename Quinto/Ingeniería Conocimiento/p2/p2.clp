;;;; AÑADIR LA INFORMACION DE AL MENOS 2 RECETAS NUEVAS al archivo compartido recetas.txt (https://docs.google.com/document/d/15zLHIeCEUplwsxUxQU66LsyKPY9n9p5v1bmi8M85YlU/edit?usp=sharing)
;;;;;recoger los datos de https://www.recetasgratis.net  en el siguiente formato
(deftemplate receta
(slot nombre)   ; necesario
(slot introducido_por) ; necesario
(slot numero_personas)  ; necesario
(multislot ingredientes)   ; necesario
(slot dificultad (allowed-symbols alta media baja muy_baja))  ; necesario
(slot duracion)  ; necesario
(slot enlace)  ; necesario
(multislot tipo_plato (allowed-symbols entrante primer_plato plato_principal postre desayuno_merienda acompanamiento)) ; necesario, introducido o deducido en este ejercicio
(slot coste)  ; opcional relevante
(slot tipo_copcion (allowed-symbols crudo cocido a_la_plancha frito al_horno al_vapor))   ; opcional
(multislot tipo_cocina)   ;opcional
(slot temporada)  ; opcional
;;;; Estos slot se calculan, se haria mediante un algoritmo que no vamos a implementar para este prototipo, lo usamos con la herramienta indicada y lo introducimos
(slot Calorias) ; calculado necesario
(slot Proteinas) ; calculado necesario
(slot Grasa) ; calculado necesario
(slot Carbohidratos) ; calculado necesario
(slot Fibra) ; calculado necesario
(slot Colesterol) ; calculado necesario
)

(deftemplate propiedad_receta
   (slot tipo)
   (slot receta)
   (slot ingrediente))


(deftemplate es-carne (slot name))
(deftemplate es-pescado (slot name))
(deftemplate es-marisco (slot name))
(deftemplate es-reposteria (slot name))
(deftemplate es-pasta (slot name))
(deftemplate es-lacteo (slot name))
(deftemplate es-embutido (slot name))
(deftemplate es-picante (slot name))
(deftemplate con-gluten (slot name))
(deftemplate es-legumbre (slot name))
(deftemplate es-fruta (slot name))
(deftemplate es-verdura (slot name))
(deftemplate es-condimento (slot name))
;;;; Para los datos calculados se puede utilizar: https://www.labdeiters.com/nutricalculadora/ o https://fitia.app/buscar/alimentos-y-recetas/

; (receta
; 	(nombre “Salsa de champiñones”)
; 	(introducido_por “Carmen Azorin Marti”)
; 	(numero_personas 4)
; 	(ingredientes champinones cebolla leche vino_blanco maicena mantequilla sal pimienta_negra)
; 	(dificultad baja)
; 	(duracion 45m)
; 	(enlace “https://www.recetasgratis.net/receta-de-salsa-de-champinones-facil-59513.html”)
; 	(tipo_plato primer_plato acompanamiento)
; 	(tipo_coccion cocido)
; 	(Calorias 86)
;     (Proteinas 4)
;     (Grasa 4)
;     (Carbohidratos 9)
;     (Fibra 1)
;     (Colesterol 3)
; )

; (receta
; 	(nombre “Torrijas de la abuela”)
; 	(introducido_por “Carmen Azorin Marti”)
; 	(numero_personas 6)
; 	(ingredientes pan leche huevos canela azucar aceite_girasol cascara_limon)
; 	(dificultad media)
; 	(duracion 45m)
; 	(enlace “https://www.recetasgratis.net/receta-de-torrijas-de-la-abuela-73990.html”)
; 	(tipo_plato postre desayuno_merienda)
; 	(tipo_coccion cocido frito)
; 	(Calorias 657)
;     (Proteinas 13)
;     (Grasa 29)
;     (Carbohidratos 85)
;     (Fibra 2)
;     (Colesterol 183)
; )


;;; Crear un fichero de texto recetas.txt en el mismo directorio de recetas.clp y compiar el contenido del archivo compartido

(defrule carga_recetas
(declare (salience 1000))
=>
(load-facts "recetas.txt")
(assert (Tarea listarInicio))
)

; aquí deberiamos crear la regla de listarInciio
(defrule listarReceta
(declare (salience 999))
    (receta (nombre ?n))
    (Tarea listarInicio)
    =>
    (printout t "Receta: " ?n crlf)
)

; aqui eliminamos el hecho de listarInicio
(defrule eliminarListarInicio
(declare (salience 998))
    ?f <- (Tarea listarInicio)
    => 
    (retract ?f)
)



(defrule guarda_recetas
(declare (salience -1000))
=>
(save-facts "recetas_saved.txt")
)

; tengo que sacar todos los ingredientes de cada receta
(defrule guardar_ingredientes
(declare (salience 997))
	?receta <- (receta (ingredientes $?ingredientes))
	=>
	(foreach ?ingrediente ?ingredientes
		(assert (ingrediente ?ingrediente))
        ;(printout t "Ingrediente: " ?ingrediente crlf)
        )
)

; hechos de clasificación de alimentos
(deffacts clasificacion-ingredientes
  ;; Carnes
  (es-carne (name pollo))
  (es-carne (name pavo))
  (es-carne (name ternera))
  (es-carne (name cerdo))
  (es-carne (name cordero))
  (es-carne (name carne))
  
  ;; Pescados
  (es-pescado (name pescado))
  (es-pescado (name salmon))
  (es-pescado (name atun))
  (es-pescado (name bacalao))
  (es-pescado (name merluza))
  
  ;; Mariscos
  (es-marisco (name langostino))
  (es-marisco (name gamba))
  (es-marisco (name mejillon))
  (es-marisco (name almeja))
  
  ;; Ingredientes de repostería
  (es-reposteria (name azucar))
  (es-reposteria (name harina))
  (es-reposteria (name chocolate))
  (es-reposteria (name leche))
  (es-reposteria (name huevo))
  (es-reposteria (name vainilla))
  (es-reposteria (name miel))
  (es-reposteria (name fruta))
  (es-reposteria (name levadura))

  (es-pasta (name macarrones))
  (es-pasta (name lasania))
  (es-pasta (name espaguetis))
  (es-pasta (name tallarines))
  (es-pasta (name pasta))

  (es-lacteo (name leche))
  (es-lacteo (name yogur))
  (es-lacteo (name queso))
  (es-lacteo (name parmesano))

  (es-embutido (name jamon))
  (es-embutido (name salchichon))
  (es-embutido (name chorizo))

  (es-picante (name aji))
  (es-picante (name chile))
  (es-picante (name jalapeño))
  (es-picante (name jalapenio))
  (es-picante (name picante))
  (es-picante (name curry))
  (es-picante (name sriracha))

  (con-gluten (name harina))
  (con-gluten (name trigo))
  (con-gluten (name pan))

  (es-legumbre (name garbanzos))
  (es-legumbre (name lenteja))
  (es-legumbre (name frijoles))
  (es-legumbre (name guisante))
  (es-legumbre (name judia))
  (es-legumbre (name tomate))

  (es-fruta (name mora))
  (es-fruta (name fresa))
  (es-fruta (name coco))
  (es-fruta (name platano))
  (es-fruta (name limon))

  (es-condimento (name sal))
    (es-condimento (name pimienta))
    (es-condimento (name ketchup))
    (es-condimento (name mayonesa))
    (es-condimento (name mostaza))
    (es-condimento (name aceite))
    (es-condimento (name vinagre))
    (es-condimento (name ajo))
    (es-condimento (name perejil))
    (es-condimento (name pimenton))
    (es-condimento (name comino))
    (es-condimento (name canela))
    (es-condimento (name nuez_moscada))
    (es-condimento (name azucar))
    (es-condimento (name miel))
    (es-condimento (name soja))
    (es-condimento (name guindilla))
    (es-condimento (name orégano))
    (es-condimento (name albahaca))

)

(defrule determinar-carnes
(declare (salience 996))
    (es-carne (name ?carne)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?carne)) 
                               (lowcase (sym-cat ?i))))
    (not (es-carne (name ?i)))  
    => 
    (assert (es-carne (name ?i)))
    ;(printout t "Carne identificada (por patrón): " ?i crlf)
)


(defrule determinar-pescados
(declare (salience 996))
    (es-pescado (name ?pez)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?pez)) 
                               (lowcase (sym-cat ?i))))
    (not (es-pescado (name ?i)))  
    => 
    (assert (es-pescado (name ?i)))
    ;(printout t "Pescado identificada (por patrón): " ?i crlf)
)

(defrule determinar-mariscos
(declare (salience 996))
    (es-marisco (name ?marisco)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?marisco)) 
                               (lowcase (sym-cat ?i))))
    (not (es-marisco (name ?i)))  
    => 
    (assert (es-marisco (name ?i)))
    ;(printout t "Marisco identificada (por patrón): " ?i crlf)
)

(defrule determinar-reposteria
(declare (salience 996))
    (es-reposteria (name ?reposteria)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?reposteria)) 
                               (lowcase (sym-cat ?i))))
    (not (es-reposteria (name ?i)))  
    => 
    (assert (es-reposteria (name ?i)))
    ;(printout t "Reposteria identificada (por patrón): " ?i crlf)
)

(defrule determinar-pasta
(declare (salience 996))
    (es-pasta (name ?p)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?p)) 
                               (lowcase (sym-cat ?i))))
    (not (es-pasta (name ?i)))  
    => 
    (assert (es-pasta (name ?i)))
    ;(printout t "Pasta identificada (por patrón): " ?i crlf)
)

(defrule determinar-lacteo
(declare (salience 996))
    (es-lacteo (name ?p)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?p)) 
                               (lowcase (sym-cat ?i))))
    (not (es-lacteo (name ?i)))  
    => 
    (assert (es-lacteo (name ?i)))
    ;(printout t "Lacteo identificado (por patrón): " ?i crlf)
)

(defrule determinar-picante
(declare (salience 996))
    (es-picante (name ?p)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?p)) 
                               (lowcase (sym-cat ?i))))
    (not (es-picante (name ?i)))  
    => 
    (assert (es-picante (name ?i)))
    ;(printout t "Lacteo identificado (por patrón): " ?i crlf)
)

(defrule determinar-gluten
(declare (salience 996))
    (con-gluten (name ?p)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?p)) 
                               (lowcase (sym-cat ?i))))
    (not (con-gluten (name ?i)))  
    => 
    (assert (con-gluten (name ?i)))
    ;(printout t "Lacteo identificado (por patrón): " ?i crlf)
)


(defrule determinar-legumbre
(declare (salience 996))
    (es-legumbre (name ?p)) 
    (ingrediente ?i&:(str-index (lowcase (sym-cat ?p)) 
                               (lowcase (sym-cat ?i))))
    (not (es-legumbre (name ?i)))  
    => 
    (assert (es-legumbre (name ?i)))
    ;(printout t "Lacteo identificado (por patrón): " ?i crlf)
)


;;;EJERCICIO: Añadir reglas para  deducir tal y como tu lo harias (usando razonamiento basado en conocimiento):
;;;  1) cual o cuales son los ingredientes relevantes de una receta

; si tiene el ingrediente en el nombre -> ese ingrediente es relevante. Tambien si algun ingrediente contiene parcialmente el nombre de la receta
; esta función sirve para ignorar palabras cortas en el nomre de la receta
(deffunction palabra-significativa? (?palabra)
   (bind ?longitud (str-length ?palabra))
   ; Ignorar palabras de menos de 3 letras o artículos/preposiciones
   (return (and (>= ?longitud 3)
                (not (member$ (lowcase ?palabra) (create$ "de" "a" "la" "las" "los" "el" "en" "con" "para")))))
)

; si la receta es "pastel de coco", el ingrediente coco_rallado es relevante -> miramos si alguna palabra de la receta aparece parcialmente en el ingrediente
(deffunction alguna-palabra-en-ingrediente (?nombre ?ingrediente)
   (bind ?result FALSE)
   (bind ?ing (lowcase (sym-cat ?ingrediente))) ; Convertir ingrediente a string
   
   (if (stringp ?nombre) then
      (bind ?palabras-nombre (explode$ ?nombre))
      (foreach ?palabra ?palabras-nombre
         (if (and (palabra-significativa? ?palabra)
                 (str-index (lowcase ?palabra) ?ing)) then
            (bind ?result TRUE))))
   
   (return ?result)
)

; si el ingrediente aparece parcialmente o por completo en el nombre de la receta -> es relevante
(defrule ingrediente_relevante_por_nombre
(declare (salience 80))
    ?receta <- (receta (nombre ?nombre) (ingredientes $? ?ingrediente $?))
    =>
    (if (alguna-palabra-en-ingrediente ?nombre ?ingrediente) then 
        (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?receta) (ingrediente ?ingrediente)))
    )
    ;(printout t "Receta: " ?nombre " Ingrediente relevante: " ?ingrediente crlf)
)

; si es paella -> ingrediente relevante es arroz
(defrule nombre-paella-arroz-relevante
(declare (salience 80))
    ?r <- (receta (nombre ?nombre) (ingredientes $? ?i $?))
    (test (or (eq (lowcase ?nombre) "paella") 
              (str-index "paella" (lowcase ?nombre))
              (str-index "risotto" (lowcase ?nombre))))
    (test (eq (lowcase ?i) arroz))
    =>
    (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?i)))
    ;(printout t "Receta: " ?nombre " Ingrediente relevante: " ?i crlf)
)

; si es jugo -> agua es relevante
(defrule nombre-jugo-agua-relevante
(declare (salience 80))
    ?r <- (receta (nombre ?nombre) (ingredientes $? ?i $?))
    (test (or (eq (lowcase ?nombre) "jugo") 
              (str-index "jugo" (lowcase ?nombre))))
    (test (eq (lowcase ?i) agua))
    =>
    (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?i)))
    ;(printout t "Receta: " ?nombre " Ingrediente relevante: " ?i crlf)
)

; en una receta donde hay 4 ingredientes o menos -> todos los ingredientes son relevantes
(defrule pocos-ingredientes-todos-relevantes
(declare (salience 80))
    ?r <- (receta (nombre ?n) (ingredientes $?i&:(<= (length$ ?i) 4)))
    =>
    (foreach ?ing ?i
        (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?ing)))
        ;(printout t "Receta: " ?n " Ingrediente relevante: " ?ing crlf)
        )
)

; poner que se quiten los condimentos
(defrule eliminar-condimento-de-ingredientes-relevantes
   ?pr <- (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?ing))
   (es-condimento (name ?ing))
   =>
   (retract ?pr)
   ;(printout t "Eliminado ingrediente relevante por ser condimento: " ?ing " de la receta " ?r crlf)
)

; si es postre -> los ingredientes de reposteria y la fruta son relevantes
(defrule ingredientes-relevantes-postre
(declare (salience 80))
   ?r <- (receta (nombre ?nombre) (tipo_plato postre) (ingredientes $? ?ing $?))
   (or (es-reposteria (name ?ing)) (es-fruta (name ?ing)) (eq pan ?ing))
   =>
   (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?ing)))
)
; si es entrante -> los mariscos y embutidos son relevantes
(defrule ingredientes-relevantes-entrante-marisco
(declare (salience 80))
   ?r <- (receta (nombre ?nombre) (tipo_plato entrante) (ingredientes $? ?ing $?))
   (or (es-marisco (name ?ing)) (es-embutido (name ?ing)))
   =>
   (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?ing)))
)


; si es desayuno_merienda ->  los lacteos, frutas, reposteria y embutidos son relevantes
(defrule ingredientes-relevantes-desayuno
(declare (salience 80))
   ?r <- (receta (nombre ?nombre) (tipo_plato desayuno_merienda) (ingredientes $? ?ing $?))
   (or (es-lacteo (name ?ing)) (es-embutido (name ?ing)) (es-fruta (name ?ing)) (es-reposteria (name ?ing)))
   =>
   (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?ing)))
)


; si es plato_principal -> la carne y el pescado son relevantes
(defrule ingredientes-relevantes-principal
(declare (salience 80))
   ?r <- (receta (nombre ?nombre) (tipo_plato plato_principal) (ingredientes $? ?ing $?))
   (or (es-carne (name ?ing)) (es-pescado (name ?ing)))
   =>
   (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?ing)))
)
; si es primer_plato -> la verdura y la legumbre es relevante 
(defrule ingredientes-relevantes-primer-plato
(declare (salience 80))
   ?r <- (receta (nombre ?nombre) (tipo_plato primer_plato) (ingredientes $? ?ing $?))
   (or (es-legumbre (name ?ing)) (es-verdura (name ?ing)))
   =>
   (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?ing)))
)
; si es acompañamiento (como paatas fritas, ensalada...) -> todos menos los condimentos son relevantes
(defrule ingredientes-relevantes-acompanamiento
(declare (salience 80))
   ?r <- (receta (nombre ?nombre) (tipo_plato acompanamiento) (ingredientes $?ings))
   =>
   (foreach ?i ?ings
      (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?i))))
)

; si no tiene ingredientes relevantes -> todos los no condiemtnos son relevantes
(defrule marcar-no-condimentos-como-relevantes-si-no-hay-otros
   (declare (salience 79))
   ?r <- (receta (nombre ?nombre) (ingredientes $?ings))
   ;; No hay ningún ingrediente relevante para esta receta
   (not (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?)))
   =>
   (foreach ?ing ?ings
      (if (not (any-factp ((?f es-condimento)) (eq ?f:name ?ing)))
         then
            (assert (propiedad_receta (tipo ingrediente_relevante) (receta ?r) (ingrediente ?ing)))))
)




;;;  2) modificar las recetas completando cual seria el/los tipo_plato asociados a una receta, SOLO PUEDE SER UN TIPO DE PLATO
;;;;;;;; especialmente para el caso de que no incluya ninguno

;;; Reglas de inferencia para tipo_plato
(deffunction ingredientes_postre ($?ingredientes)
   (bind ?count 0)

   ;; Si hay al menos un ingrediente que sea carne/pescado/marisco → false
   (foreach ?ing $?ingredientes
      (if (or
            (any-factp ((?f es-carne)) (eq ?f:name ?ing))
            (any-factp ((?f es-pescado)) (eq ?f:name ?ing))
            (any-factp ((?f es-marisco)) (eq ?f:name ?ing)))
         then
            (return FALSE)))

   ;; Si hay al menos 2 ingredientes de repostería → true
   (foreach ?ing $?ingredientes
      (if (any-factp ((?f es-reposteria)) (eq ?f:name ?ing))
         then
            (bind ?count (+ ?count 1))))

   (return (>= ?count 2))
)

(deffunction ingredientes_entrante ($?ingredientes)
   ;; Si no contiene carne, pescado, ni repostería, ni pasta -> marisco es normal que tenga un entrante
   (foreach ?ing $?ingredientes
      (if (or
            (any-factp ((?f es-carne)) (eq ?f:name ?ing))
            (any-factp ((?f es-pescado)) (eq ?f:name ?ing))
            (any-factp ((?f es-pasta)) (eq ?f:name ?ing))
            (any-factp ((?f es-reposteria)) (eq ?f:name ?ing))
            )
         then
            (return FALSE)))

   (return TRUE)
)

(defrule es-postre
(declare (salience 90))
    ?receta <- (receta (nombre ?nombre)
                      (ingredientes $?ingredientes)
                      (tipo_plato $?tp&:(= (length$ $?tp) 0))) ; que no tenga tipo de plato
    =>
    (if (ingredientes_postre $?ingredientes) then
        ;(modify ?receta (tipo_plato postre))
        ;(printout t "Identificado como POSTRE: " ?nombre crlf)
    )
    (if (ingredientes_postre $?ingredientes) then
        (modify ?receta (tipo_plato postre))
    )
)

(defrule es-entrante
(declare (salience 90))
    ?receta <- (receta (nombre ?nombre)
                      (ingredientes $?ingredientes)
                      (tipo_plato $?tp&:(= (length$ $?tp) 0))
                      )  ; que no tenga tipo de plato    
    =>
    (if (ingredientes_entrante $?ingredientes) then 
        ;(printout t "Voy a identificar como ENTRANTE: " ?nombre crlf)
        )
    (if (ingredientes_entrante $?ingredientes) then 
        (modify ?receta (tipo_plato entrante))
    )
)

(deffunction ingredientes_primer_plato ($?ingredientes)
   (bind ?tiene_base FALSE)
   (bind ?tiene_proteina FALSE)

    ; si tiene pasta, legumbres o arroz y NO tiene proteina
   (foreach ?ing $?ingredientes
      (if (or 
            (any-factp ((?f es-pasta)) (eq ?f:name ?ing))
            (any-factp ((?f es-legumbre)) (eq ?f:name ?ing))
            (eq ?ing arroz))
         then (bind ?tiene_base TRUE))

      (if (or 
            (any-factp ((?f es-carne)) (eq ?f:name ?ing))
            (any-factp ((?f es-pescado)) (eq ?f:name ?ing)))
         then (bind ?tiene_proteina TRUE)))

   (return (and ?tiene_base (not ?tiene_proteina)))
)

(defrule es-primer-plato
(declare (salience 90))
   ?receta <- (receta (nombre ?nombre)
                      (ingredientes $?ingredientes)
                      (tipo_plato $?tp&:(= (length$ $?tp) 0)))
   =>
   (if (ingredientes_primer_plato $?ingredientes) then
      ;(printout t "Identificado como PRIMER PLATO: " ?nombre crlf)
      (modify ?receta (tipo_plato primer_plato)))
)


(deffunction ingredientes_acompanamiento ($?ingredientes)
   (bind ?n (length$ $?ingredientes))
   (return (or (= ?n 2) (= ?n 3)))
)

(defrule es-acompanamiento
(declare (salience 90))
    ?receta <- (receta (nombre ?nombre)
                       (ingredientes $?ingredientes)
                       (tipo_plato $?tp&:(= (length$ $?tp) 0)))
    =>
    (if (ingredientes_acompanamiento $?ingredientes) then
        ;(printout t "Identificado como ACOMPAÑAMIENTO: " ?nombre crlf)
        (modify ?receta (tipo_plato acompanamiento))
    )
)


(deffunction ingredientes_desayuno_merienda ($?ingredientes)
   (bind ?es_dulce TRUE)
   (bind ?es_salado TRUE)

   ;; Comprobamos si todos los ingredientes son fruta o lacteo (dulce)
   (foreach ?ing $?ingredientes
      (if (not (or
            (any-factp ((?f es-fruta)) (eq ?f:name ?ing))
            (any-factp ((?f es-lacteo)) (eq ?f:name ?ing))))
         then
            (bind ?es_dulce FALSE)))

   ;; Comprobamos si todos los ingredientes son pan o embutido (salado)
   (foreach ?ing $?ingredientes
      (if (not (or
            (eq ?ing pan)
            (any-factp ((?f es-embutido)) (eq ?f:name ?ing))))
         then
            (bind ?es_salado FALSE)))

   (return (or ?es_dulce ?es_salado))
)

(defrule es-desayuno-merienda
(declare (salience 90))
    ?receta <- (receta (nombre ?nombre)
                       (ingredientes $?ingredientes)
                       (tipo_plato $?tp&:(= (length$ $?tp) 0)))
    =>
    (if (ingredientes_desayuno_merienda $?ingredientes) then
        ;(printout t "Identificado como DESAYUNO/MERIENDA: " ?nombre crlf)
        (modify ?receta (tipo_plato desayuno_merienda))
    )
)

(defrule es-plato-principal
(declare (salience 89)) ; prioridad baja para que se aplique al final
    ?receta <- (receta (nombre ?nombre)
                       (tipo_plato $?tp&:(= (length$ $?tp) 0)))
    =>
    ;(printout t "Identificado como PLATO PRINCIPAL (por defecto): " ?nombre crlf)
    (modify ?receta (tipo_plato plato_principal))
)




;;;  3) si una receta es: vegana, vegetariana, de dieta, picante, sin gluten o sin lactosa

(defrule receta-vegana
(declare (salience 50))
   (receta (nombre ?n) (ingredientes $?ingredientes))
   (not (es-carne (name ?i&:(member$ ?i $?ingredientes))))
   (not (es-pescado (name ?i&:(member$ ?i $?ingredientes))))
   (not (es-marisco (name ?i&:(member$ ?i $?ingredientes))))
   (not (es-lacteo (name ?i&:(member$ ?i $?ingredientes))))
   (not (es-embutido (name ?i&:(member$ ?i $?ingredientes))))
   (not (find$ "huevo" $?ingredientes))
   =>
   (assert (propiedad_receta (tipo es_vegana) (receta ?n)))
   ;(printout t "La receta " ?n " es vegana." crlf)
)

(defrule receta-vegetariana
(declare (salience 50))
   (receta (nombre ?n) (ingredientes $?ingredientes))
   (not (es-carne (name ?i&:(member$ ?i $?ingredientes))))
   (not (es-pescado (name ?i&:(member$ ?i $?ingredientes))))
   (not (es-marisco (name ?i&:(member$ ?i $?ingredientes))))
   (not (es-embutido (name ?i&:(member$ ?i $?ingredientes))))
   =>
   (assert (propiedad_receta (tipo es_vegetariana) (receta ?n)))
   ;(printout t "La receta " ?n " es vegetariana." crlf)
)

(defrule receta-de-dieta
(declare (salience 50))
   (receta (nombre ?n) (numero_personas ?num_personas)
           (Calorias ?calorias) (Grasa ?grasa) (tipo_copcion ?tipo_copcion))
   (test (and (numberp ?calorias) (numberp ?num_personas) (> ?num_personas 0)))
   
   ; Verificamos si las calorías y la grasa por persona están por debajo de los límites establecidos
   (test (and (< (/ ?calorias ?num_personas) 300) (< (/ ?grasa ?num_personas) 15)))
   (not (find$ "azucar" $?ingredientes))
   (test (neq ?tipo_copcion frito))
   =>
   (assert (propiedad_receta (tipo es_de_dieta) (receta ?n)))
   ;(printout t "La receta " ?n " es de dieta." crlf)
)


(defrule receta-picante
(declare (salience 50))
   (receta (nombre ?n) (ingredientes $? ?ingrediente $?))
   (es-picante (name ?ingrediente))
   =>
   (assert (propiedad_receta (tipo es_picante) (receta ?n)))
   ;(printout t "La receta " ?n " es picante." crlf)
)

(defrule receta-sin-gluten
(declare (salience 50))
   (receta (nombre ?n) (ingredientes $?ingredientes))
   (not (con-gluten (name ?i&:(member$ ?i $?ingredientes))))
   (not (es-pasta (name ?i&:(member$ ?i $?ingredientes))))
   =>
   (assert (propiedad_receta (tipo es_sin_gluten) (receta ?n)))
   ;(printout t "La receta " ?n " es sin gluten." crlf)
)

(defrule receta-sin-lactosa
(declare (salience 50))
   (receta (nombre ?n) (ingredientes $?ingredientes))
   (not (es-lacteo (name ?i&:(member$ ?i $?ingredientes))))
   =>
   (assert (propiedad_receta (tipo es_sin_lactosa)(receta ?n)))
   ;(printout t "La receta " ?n " es sin lactosa." crlf)
)


;; AHORA PEDIR LA RECETA Y DECIR LAS PROPIEDADES

; Regla para solicitar el nombre de la receta
(defrule solicitar-nombre-receta
(declare (salience 10))
   =>
   (printout t "=================================" crlf)
   (printout t "Introduce el nombre de la receta: ")
   (bind ?nombre (readline))
   (assert (receta_solicitada ?nombre))  ; Almacena el nombre de la receta solicitada
   ;(printout t "Buscando la receta: " ?nombre crlf)
   (assert (Tarea recetaNoEncontrada))
)

; Regla para verificar si la receta existe
(defrule verificar-existencia-receta
(declare (salience 9))
   (receta (nombre ?nombre))
   (receta_solicitada ?nombre)
   ?f <- (Tarea recetaNoEncontrada)
   =>
   (printout t "Receta " ?nombre " encontrada." crlf)
   (retract ?f)
)

; Regla para manejar el caso en que la receta no exista
(defrule receta-no-encontrada
(declare (salience 8))
   (Tarea recetaNoEncontrada)
   (receta_solicitada ?nombre)
   =>
   (printout t "La receta " ?nombre " no se encuentra en la base de datos." crlf)
)

(deffunction mostrar-ingredientes-relevantes (?receta ?lista-ingredientes)
   (printout t "Ingredientes relevantes de la receta:" crlf)
   (foreach ?ing ?lista-ingredientes
      (if (any-factp ((?f propiedad_receta))
            (and (eq ?f:tipo ingrediente_relevante)
                 (eq ?f:receta ?receta)
                 (eq ?f:ingrediente ?ing)))
         then
            (printout t " - " ?ing crlf))))

(deffunction mostrar-propiedades-extra (?receta)
   (bind ?prop-list (create$)) ; lista vacía

   (foreach ?tipo (create$ es_vegana es_vegetariana es_sin_gluten es_picante es_sin_lactosa es_de_dieta)
      (if (any-factp ((?f propiedad_receta))
            (and (eq ?f:tipo ?tipo)
                 (eq ?f:receta ?receta)))
         then
            (bind ?prop-list (insert$ ?prop-list 1 ?tipo))))

   (if (neq (length$ ?prop-list) 0)
      then
         (printout t "Propiedades adicionales: " (implode$ ?prop-list ) crlf)
      else
         (printout t "Sin propiedades especiales." crlf)))


(defrule mostrar-ingredientes
(declare (salience 7))
   (receta_solicitada ?nombre)
   ?r <- (receta (nombre ?nombre) (ingredientes $?ings) (tipo_plato ?tipo))
   =>
   (printout t "Tipo de plato: " ?tipo crlf)
   (mostrar-propiedades-extra ?nombre)
   (mostrar-ingredientes-relevantes ?r $?ings)
)


;;;FORMATO DE LOS HECHOS: 
;  
;       (propiedad_receta ingrediente_relevante ?r ?a)
;       (propiedad_receta es_vegetariana ?r) 
;       (propiedad_receta es_vegana ?r)
;       (propiedad_receta es_sin_gluten ?r)
;       (propiedad_receta es_picante ?r)
;       (propiedad_receta es_sin_lactosa ?r)
;       (propiedad_receta es_de_dieta ?r)







 

 
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
(load-facts "recetas_base.txt")
)


(defrule guarda_recetas
(declare (salience -1000))
=>
(save-facts "recetas_saved.txt")
)

; tengo que sacar todos los ingredientes de cada receta
(defrule guardar_ingredientes
	?receta <- (receta (ingredientes $?ingredientes))
	=>
	(foreach ?ingrediente ?ingredientes
		(assert (ingrediente ?ingrediente)))
)

(defrule listar_alimentos
    (ingrediente ?x)
    =>
    (printout t crlf ?x crlf)
)


;;;EJERCICIO: Añadir reglas para  deducir tal y como tu lo harias (usando razonamiento basado en conocimiento):
;;;  1) cual o cuales son los ingredientes relevantes de una receta

; regla para guardar condimentos
(deffacts condimentos
(es_condimento sal)
(es_condimento ajo)
(es_condimento aji_molido)
(es_condimento romero)
(es_condimento pimienta)
(es_condimento oregano)
(es_condimento ramas_de_culantro)
(es_condimento aji_limo)
(es_condimento pimenton_dulce)
(es_condimento pimienta_negra)
(es_condimento laurel)
(es_condimento cayena)
(es_condimento cardamomo)
(es_condimento aji)
(es_condimento nuez_moscada)
(es_condimento canela_en_polvo)
(es_condimento coco_rallado)
(es_condimento azucar)
(es_condimento semillas_sesamo)
(es_condimento brotes_soja)
(es_condimento colorante)
(es_condimento levadura)
(es_condimento piemienta_negra)
(es_condimento curcuma)
(es_condimento ajo)
)
; regla para guardar ingredientes básicos reposteria
; regla para guardar ingredientes liquidos

;;;  2) modificar las recetas completando cual seria el/los tipo_plato asociados a una receta, 
;;;;;;;; especialmente para el caso de que no incluya ninguno
;;;  3) si una receta es: vegana, vegetariana, de dieta, picante, sin gluten o sin lactosa

;;;FORMATO DE LOS HECHOS: 
;  
;       (propiedad_receta ingrediente_relevante ?r ?a)
;       (propiedad_receta es_vegetariana ?r) 
;       (propiedad_receta es_vegana ?r)
;       (propiedad_receta es_sin_gluten ?r)
;       (propiedad_receta es_picante ?r)
;       (propiedad_receta es_sin_lactosa ?r)
;       (propiedad_receta es_de_dieta ?r)







 

 
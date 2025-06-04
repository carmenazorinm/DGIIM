(deftemplate Evidencia (slot nombre) (slot valor))
(deftemplate Explicacion (slot hipotesis) (slot texto))

(deffacts hipotesis-validas
  (Hipotesis problema_bujias)
  (Hipotesis problema_starter)
  (Hipotesis problema_bateria))


(deffunction encadenado (?fc_antecedente ?fc_regla)
  (if (> ?fc_antecedente 0)
    then (* ?fc_antecedente ?fc_regla)
    else 0))

(deffunction combinacion (?fc1 ?fc2)
  (if (and (> ?fc1 0) (> ?fc2 0))
    then (bind ?rv (- (+ ?fc1 ?fc2) (* ?fc1 ?fc2)))
  else
    (if (and (< ?fc1 0) (< ?fc2 0))
      then (bind ?rv (+ (+ ?fc1 ?fc2) (* ?fc1 ?fc2)))
    else
      (bind ?rv (/ (+ ?fc1 ?fc2) (- 1 (min (abs ?fc1) (abs ?fc2)))))
    ))
  ?rv)

; --- Etapa 1: Preguntar evidencias
(defrule preguntar-evidencias
  (declare (salience 100))
  =>
  (foreach ?evidence (create$ hace_intentos_arrancar hay_gasolina_en_deposito encienden_las_luces gira_motor)
    (printout t "¿" ?evidence "? (si/no): ")
    (bind ?resp (read))
    (assert (Evidencia (nombre ?evidence) (valor ?resp)))))

; --- Etapa 2: Convertir en FactorCerteza
(defrule certeza-evidencias
  (declare (salience 90))
  (Evidencia (nombre ?e) (valor ?v))
  =>
  (assert (FactorCerteza ?e ?v 1)))

; --- Etapa 3: Inferencias
(defrule R1
  (declare (salience 80))
  (FactorCerteza motor_llega_gasolina si ?f1)
  (FactorCerteza gira_motor si ?f2)
  =>
  (bind ?fc (encadenado (encadenado ?f1 ?f2) 0.7))
  (assert (FactorCerteza problema_bujias si ?fc))
  (assert (Explicacion (hipotesis problema_bujias) (texto (str-cat "Hay gasolina y el motor gira → posibles problemas con bujías. FC=" ?fc)))))

(defrule R2
  (declare (salience 80))
  (FactorCerteza gira_motor no ?f)
  =>
  (bind ?fc (encadenado ?f 0.8))
  (assert (FactorCerteza problema_starter si ?fc))
  (assert (Explicacion (hipotesis problema_starter) (texto (str-cat "El motor no gira → posible problema con el starter. FC=" ?fc)))))

(defrule R3
  (declare (salience 80))
  (FactorCerteza encienden_las_luces no ?f)
  =>
  (bind ?fc (encadenado ?f 0.9))
  (assert (FactorCerteza problema_bateria si ?fc))
  (assert (Explicacion (hipotesis problema_bateria) (texto (str-cat "No encienden las luces → posible problema con batería. FC=" ?fc)))))

(defrule R4
  (declare (salience 80))
  (FactorCerteza hay_gasolina_en_deposito si ?f)
  =>
  (bind ?fc (encadenado ?f 0.9))
  (assert (FactorCerteza motor_llega_gasolina si ?fc)))

(defrule R5
  (declare (salience 80))
  (FactorCerteza hace_intentos_arrancar si ?f)
  =>
  (bind ?fc (encadenado ?f -0.6))
  (assert (FactorCerteza problema_starter no ?fc))
  (assert (Explicacion (hipotesis problema_starter) (texto (str-cat "Hace intentos de arrancar → descartamos starter. FC=" ?fc)))))

(defrule R6
  (declare (salience 80))
  (FactorCerteza hace_intentos_arrancar si ?f)
  =>
  (bind ?fc (encadenado ?f 0.5))
  (assert (FactorCerteza problema_bateria si ?fc))
  (assert (Explicacion (hipotesis problema_bateria) (texto (str-cat "Hace intentos de arrancar → posible batería. FC=" ?fc)))))

; --- Etapa 4: Combinar inferencias múltiples del mismo tipo
(defrule combinar
  (declare (salience 70))
  ?f <- (FactorCerteza ?h ?s ?fc1)
  ?g <- (FactorCerteza ?h ?s ?fc2)
  (test (neq ?fc1 ?fc2))
  =>
  (retract ?f ?g)
  (assert (FactorCerteza ?h ?s (combinacion ?fc1 ?fc2))))

; --- Etapa 5: Generar certeza neta
(defrule combinar-signo
  (declare (salience 60))
  (FactorCerteza ?h si ?fc1)
  (FactorCerteza ?h no ?fc2)
  =>
  (assert (Certeza ?h (+ ?fc1 ?fc2)))) ; suma directa, no resta

(defrule certeza-solo-positiva
  (declare (salience 60))
  (FactorCerteza ?h si ?fc)
  (not (FactorCerteza ?h no ?))
  =>
  (assert (Certeza ?h ?fc)))

(defrule certeza-solo-negativa
  (declare (salience 60))
  (FactorCerteza ?h no ?fc)
  (not (FactorCerteza ?h si ?))
  =>
  (assert (Certeza ?h (* -1 ?fc))))

(defrule certeza-cero-si-no-existe
  (declare (salience 50))
  (Hipotesis ?h)
  (not (Certeza ?h ?))
  =>
  (assert (Certeza ?h 0)))

; --- Etapa 6: Elegir mejor hipótesis y justificar
(defrule inicializar-mejor-certeza
  (declare (salience 20))
  (Hipotesis ?h)
  ?c <- (Certeza ?h ?fc)
  (not (mejor-certeza ? _))
  =>
  (assert (mejor-certeza ?h ?fc)))

(defrule actualizar-mejor-certeza
  (declare (salience 19))
  (Hipotesis ?h1)
  (Hipotesis ?h2)
  ?m <- (mejor-certeza ?h1 ?fc1)
  ?c <- (Certeza ?h2 ?fc2&:(> ?fc2 ?fc1))
  =>
  (retract ?m)
  (assert (mejor-certeza ?h2 ?fc2)))

(defrule elegir-mejor-hipotesis
  (declare (salience 10))
  (mejor-certeza ?h ?fc)
  =>
  (printout t crlf "Diagnóstico más probable: " ?h " con certeza " ?fc crlf)
  (do-for-all-facts ((?exp Explicacion)) TRUE
    (if (eq ?exp:hipotesis ?h) then
      (printout t "Explicación: " ?exp:texto crlf))))


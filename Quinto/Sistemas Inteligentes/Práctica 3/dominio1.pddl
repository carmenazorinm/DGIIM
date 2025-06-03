(define (domain ejercicio1)
  (:requirements :strips :typing)

  ; tipos
  (:types
    personaje recurso localizacion
  )

  ; constantes 
  (:constants
    Enano Hobbit - personaje
    Mineral Mithril Madera Especia Alimento - recurso
  )

  (:predicates
    ; personaje en una localizacion
    (en ?p - personaje ?l - localizacion)
    ; recurso en una localizacion
    (enRecurso ?r - recurso ?l - localizacion)
    ; localizaciones conectadas
    (conectado ?l1 ?l2 - localizacion)
    ; rol de un personaje
    (esRol ?p - personaje ?r - personaje)
    ; tipo de recurso
    (esCategoria ?r - recurso ?c - recurso)
    ; disponibilidad de un personaje
    (disponible ?p - personaje)
    ; indica que un personaje esta extrayendo un recurso
    (extrayendo ?p - personaje ?r - recurso)
    ; indica que un recurso se esta generando
    (generando ?r - recurso)
  )

  ; accion de viajar de una localizacion a otra
  (:action Viajar
    :parameters (?p - personaje ?l1 - localizacion ?l2 - localizacion)
    ; si las localizaciones esta conectadas y el personaje está en la primera
    :precondition (and
      (en ?p ?l1)
      (conectado ?l1 ?l2)
    )
    ; el personaje deja la primera localizacion y llega a la segunda
    :effect (and
      (not (en ?p ?l1))
      (en ?p ?l2)
    )
  )

  ; accion de extraer un recurso
  (:action ExtraerRecurso
    :parameters (?p - personaje ?r - recurso ?l - localizacion)
    ; solo los enanos disponibles pueden extraer recursos
    :precondition (and
      (en ?p ?l)
      (disponible ?p)
      (esRol ?p Enano)
      (enRecurso ?r ?l)
    )
    ; el personaje comienza a extraer el recurso
    :effect (and
      (extrayendo ?p ?r)
      (generando ?r)
    )
  )
)
(define (domain ejercicio3)
    (:requirements :strips :typing)
    ; tipos
    (:types
        personaje recurso localizacion
    )

    (:constants
        ; añadimos Mago como tipos de rol
        Enano Hobbit Mago Elfo Humano - personaje
        ; los tipos de recursos del problema 1
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
        ; tipo de recurso
        (esAnillo ?o - recurso)
        (esEspada ?o - recurso)
        ; disponibilidad de un personaje
        (disponible ?p - personaje)
        ; indica si personaje es miembro de la comunidad
        (miembroComunidad ?p - personaje)
        ; indica si la comunidad está formada
        (comunidadFormada)
        ; indica si un personaje posee un recurso
        (posee ?p - personaje ?o - recurso)
        ; indica si un personaje es el portador del anillo
        (portador ?p - personaje)
        ; indica dónde se destruye el anillo
        (lugarDestruccion ?l - localizacion)
        ; indica que el anillo ha sido destruido
        (anilloDestruido)
    )

    ; para formar comunidad, se necesitan un hobbit y un mago
    ; y para formar la comunidad, todos deben reunirse en el mismo punto
    (:action formarComunidad
        :parameters (?m1 - personaje ?m2 - personaje ?m3 - personaje ?m4 - personaje ?m5 - personaje ?l - localizacion)
        :precondition (and
            (esRol ?m1 Hobbit)
            (esRol ?m2 Mago)
            (esRol ?m3 Hobbit)
            (esRol ?m4 Hobbit)
            (esRol ?m5 Elfo)
            (en ?m1 ?l)
            (en ?m2 ?l)
            (en ?m3 ?l)
            (en ?m4 ?l)
            (en ?m5 ?l)
            (not (comunidadFormada)) ; la comunidad no debe star formada
        )
        :effect (and
            (comunidadFormada)
            (miembroComunidad ?m1)
            (miembroComunidad ?m2)
            (miembroComunidad ?m3)
            (miembroComunidad ?m4)
            (miembroComunidad ?m5)
        )
    )

    ; como la comunidad esta formada por 2 personajes, basta con pasarlos como parametros
    (:action viajarComunidad
        ; l1 origen y l2 destino
        :parameters (?l1 ?l2 - localizacion ?p1 ?p2 ?p3 ?p4 ?p5 - personaje)
        ; los personajes de la comunidad en l1 y l1 y l2 conectados
        :precondition (and
            (comunidadFormada)
            (miembroComunidad ?p1)
            (miembroComunidad ?p2)
            (miembroComunidad ?p3)
            (miembroComunidad ?p4)
            (miembroComunidad ?p5)
            (en ?p1 ?l1)
            (en ?p2 ?l1)
            (en ?p3 ?l1)
            (en ?p4 ?l1)
            (en ?p5 ?l1)
            (conectado ?l1 ?l2)
            (esRol ?p1 Hobbit)
            (esRol ?p2 Mago)
            (esRol ?p3 Hobbit)
            (esRol ?p4 Hobbit)
            (esRol ?p5 Elfo)
            (not (= ?p1 ?p2))
            (not (= ?p1 ?p3))
            (not (= ?p1 ?p4))
            (not (= ?p1 ?p5))
            (not (= ?p2 ?p3))
            (not (= ?p2 ?p4))
            (not (= ?p2 ?p5))
            (not (= ?p3 ?p4))
            (not (= ?p3 ?p5))
            (not (= ?p4 ?p5))
        )
        ; los personajes pasan de l1 a l2
        :effect (and
            (not (en ?p1 ?l1)) (not (en ?p2 ?l1))
            (en ?p1 ?l2) (en ?p2 ?l2)
            (not (en ?p3 ?l1))
            (en ?p3 ?l2)
            (not (en ?p4 ?l1))
            (en ?p4 ?l2)
            (not (en ?p5 ?l1))
            (en ?p5 ?l2)
        )
    )

    ; un personaje puede viajar solo si la comunidad no está formada
    ; o si no es miembro de la comunidad
    (:action Viajar
        ; l1 origen y l2 destino
        :parameters (?p - personaje ?l1 ?l2 - localizacion)
        ; el personaje en l1 y l1 y l2 conectados
        ; y la comunidad no formada o el personaje no es miembro
        :precondition (and
            (en ?p ?l1)
            (conectado ?l1 ?l2)
            (or (not (comunidadFormada)) (not (miembroComunidad ?p)))
        )
        ; el personaje pasa de l1 a l2
        :effect (and
            (not (en ?p ?l1))
            (en ?p ?l2)
        )
    )

    ; un personaje debe recoger los 3 objetos y debe ser un Hobbit
    (:action recogerObjeto
        :parameters (?p - personaje ?o - recurso ?l - localizacion)
        :precondition (and
            (comunidadFormada)
            (miembroComunidad ?p)
            (en ?p ?l)
            (enRecurso ?o ?l)
            ; solo hobbits pueden coger el anillo
            (or (not (esAnillo ?o)) (esRol ?p Hobbit))
            ; solo se puede coger Mithril o Espada si ya se tiene el anillo
            ; el portador debe ser el mismo para los 3 objetos
            (or (not (esCategoria ?o Mithril)) (posee ?p Anillo))
            (or (not (esEspada ?o)) (posee ?p Anillo))
        )
        :effect (and
            ; efecto general para espada
            (when
                (esEspada ?o)
                (posee ?p Espada))

            ; efecto especial para mithril
            (when
                (esCategoria ?o Mithril)
                (posee ?p Mithril))

            ; efecto especial para anillo
            (when
                (esAnillo ?o)
                (and
                    (posee ?p Anillo)
                    (portador ?p)))
        )
    )

    ; el personaje tira el anillo en el lugar donde se destruye
    (:action destruirAnillo
        :parameters (?p - personaje ?l - localizacion)
        ; cuando se tienen los tres objetos y se esta en el lugar de destrucción
        :precondition (and
            (portador ?p)
            (en ?p ?l)
            (posee ?p Anillo)
            (posee ?p Mithril)
            (posee ?p Espada)
            (lugarDestruccion ?l)
        )
        ; 
        :effect (anilloDestruido)
    )

)
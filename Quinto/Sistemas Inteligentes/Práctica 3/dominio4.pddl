(define (domain ejercicio4)
    (:requirements :strips :typing)

    (:types
        personaje recurso localizacion edificio ; añadimos edificio como tipo
        )

    (:constants
        ; añadimos Mago , elfo y humano como tipos de rol
        Enano Hobbit Mago Elfo Humano - personaje
        ; los tipos de recursos del problema 1
        Mineral Mithril Madera Especia Alimento - recurso
        ; los tipos de edificios
        Extractor Fortaleza - edificio
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
        ; tipo de construccion
        (esEdificio ?e - edificio ?c - edificio)
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
        ; indica si un edificio esta construido en una localizacion
        (construido ?e - edificio ?l - localizacion)
        ; indica que un personaje esta extrayendo un recurso
        (extrayendo ?p - personaje ?r - recurso)
        ; indica que un recurso se esta generando
        (generando ?r - recurso)
    )

    ; para formar comunidad, se necesitan un hobbit y un mago
    ; y para formar la comunidad, todos deben reunirse en el mismo punto
    (:action formarComunidad
        :parameters (?h - personaje ?m - personaje ?l - localizacion)
        :precondition (and
            (esRol ?h Hobbit)
            (esRol ?m Mago)
            (en ?h ?l)
            (en ?m ?l)
            (not (comunidadFormada))
        )
        :effect (and
            (comunidadFormada)
            (miembroComunidad ?h)
            (miembroComunidad ?m)
        )
    )

    ; como la comunidad esta formada por 2 personajes, basta con pasarlos como parametros
    (:action viajarComunidad
        ; l1 origen y l2 destino
        :parameters (?l1 ?l2 - localizacion ?p1 ?p2 - personaje)
        ; los personajes de la comunidad en l1 y l1 y l2 conectados
        :precondition (and
            (comunidadFormada)
            (miembroComunidad ?p1)
            (miembroComunidad ?p2)
            (en ?p1 ?l1)
            (en ?p2 ?l1)
            (conectado ?l1 ?l2)
        )
        ; los personajes pasan de l1 a l2
        :effect (and
            (not (en ?p1 ?l1)) (not (en ?p2 ?l1))
            (en ?p1 ?l2) (en ?p2 ?l2)
        )
    )

    ; un personaje solo puede viajar solo si la comunidad no está formada
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
                (posee ?p ?o))

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

    (:action ExtraerRecurso
        ; el personaje extrae un recurso de una localizacion
        :parameters (?p - personaje ?l - localizacion ?r - recurso)
        :precondition (and
            ; el personaje debe estar en la localizacion y disponible
            (en ?p ?l)
            (enRecurso ?r ?l)
            (disponible ?p)

            ; si es Enano y quiere extraer Mithril, debe haber un Extractor construido en ese lugar
            
            (or
                (not (esCategoria ?r Mithril))
                (and (esRol ?p Enano) (construido Extractor ?l))
            )

            ; los Humanos solo pueden extraer Mineral
            (or
                (not (esCategoria ?r Mineral))
                (esRol ?p Humano)
            )

            ; los Enanos extraen Madera
            (or
                (not (esCategoria ?r Madera))
                (esRol ?p Enano)
            )

            ; todos los hobbits deben estar generando alimento
            (or
                (forall
                    (?h - personaje)
                    (or
                        (not (esRol ?h Hobbit))
                        (extrayendo ?h Alimento))
                )
                (and (esRol ?p Hobbit)
                    (esCategoria ?r Alimento)
                )
            )
        )
        ; el personaje comienza a extraer el recurso
        :effect (and
            (not (disponible ?p))

            ;; Alimento
            (when
                (esCategoria ?r Alimento)
                (and (extrayendo ?p Alimento)
                    (generando Alimento)))

            ;; Madera
            (when
                (esCategoria ?r Madera)
                (and (extrayendo ?p Madera)
                    (generando Madera)))

            ;; Mithril
            (when
                (esCategoria ?r Mithril)
                (and (extrayendo ?p Mithril)
                    (generando Mithril)))

            ;; Mineral
            (when
                (esCategoria ?r Mineral)
                (and (extrayendo ?p Mineral)
                    (generando Mineral)))
        )

    )

    (:action Construir
        :parameters (?p - personaje ?e - edificio ?l - localizacion)
        :precondition (and
            (en ?p ?l)
            (disponible ?p)

            ; si se construye un Extractor, el constructor debe ser Humano y debe haber Mineral
            (or
                (not (esEdificio ?e Extractor))
                (and (esRol ?p Humano)
                    (generando Mineral))
            )

            ; Si se construye una Fortaleza, debe ser un Mago y tener Madera y Mithril
            (or
                (not (esEdificio ?e Fortaleza))
                (and (esRol ?p Mago)
                    (generando Madera)
                    (generando Mithril))
            )
        )
        :effect (and
            (construido ?e ?l)
        )
    )
)
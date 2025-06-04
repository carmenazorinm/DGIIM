
(define (problem problema3)
    (:domain ejercicio3)

    (:objects
        ; los personajes
        Hobbit1 Hobbit2 Hobbit3 Hobbit4 Mago1 Mago2 Enano1 Enano2 Elfo1 Humano1 Humano2 - personaje
        ; los recursos
        r_fangorn r_moria_mineral r_moria_mithril r_erebor r_lothlorien r_mirkwood - recurso
        ; las localizaciones
        Hobbiton Bree Rivendell HighPass Mirkwood Erebor Moria Lothlorien Tharbad Fangorn Isengard HelmsDeep Edoras AmonHen MinasTirith DolAmroth Tolfolas MinasMorgul DeadMarshes Orodruin - localizacion
        ; los nuevos recursos espaciales del ejercicio
        Anillo Espada - recurso

    )

    (:init
        ; roles del problema
        (esRol Hobbit1 Hobbit)
        (esRol Hobbit2 Hobbit)
        (esRol Hobbit3 Hobbit)
        (esRol Hobbit4 Hobbit)
        (esRol Mago1 Mago)
        (esRol Mago2 Mago)
        (esRol Enano1 Enano)
        (esRol Enano2 Enano)
        (esRol Elfo1 Elfo)
        (esRol Humano1 Humano)
        (esRol Humano2 Humano)

        ; recursos -> se añade el Anillo y la Espada
        (esAnillo Anillo)
        (esEspada Espada)
        (enRecurso r_fangorn Fangorn)
        (esCategoria r_fangorn Madera)
        (enRecurso r_moria_mineral Moria)
        (enRecurso r_moria_mithril Moria)
        (esCategoria r_moria_mineral Mineral)
        (esCategoria r_moria_mithril Mithril)
        (enRecurso r_erebor Erebor)
        (esCategoria r_erebor Mineral)
        (enRecurso r_lothlorien Lothlorien)
        (esCategoria r_lothlorien Madera)
        (enRecurso r_mirkwood Mirkwood)
        (esCategoria r_mirkwood Madera)
        (enRecurso Alimento Hobbiton)
        (esCategoria Alimento Alimento)
        (enRecurso Especia Tolfolas)
        (esCategoria Especia Especia)

        ; tenemos Hobbit1, Hobbit2, Hobbit3 en Hobbiton;
        ; tenemos Hobbit4 en Bree; y tenemos Mago1 en Rivendell y Mago2 en Isengard
        (en Hobbit1 Hobbiton)
        (en Hobbit2 Hobbiton)
        (en Hobbit3 Hobbiton)
        (en Hobbit4 Bree)
        (en Mago1 Rivendell)
        (en Mago2 Isengard)
        (en Enano1 Fangorn)
        (en Enano2 Moria)
        (en Elfo1 Lothlorien)
        (en Humano1 Edoras)
        (en Humano2 Edoras)

        ; todos disponibles menos Enano1
        (disponible Hobbit1)
        (disponible Hobbit2)
        (disponible Hobbit3)
        (disponible Hobbit4)
        (disponible Mago1)
        (disponible Mago2)

        ; Enano1 no está disponible
        ; no se marca como disponible para reflejar que está ocupado

        ; localizacion de los nuevos recursos
        (enRecurso Anillo Rivendell)
        (enRecurso Espada Lothlorien)

        ;; Lugar de destrucción
        (lugarDestruccion Orodruin)

        ;; Conectividad de las localizaciones -> hecho por chatGPT
        ;; Hobbiton
        (conectado Hobbiton Bree)
        (conectado Hobbiton Tharbad)

        ;; Bree
        (conectado Bree Hobbiton)
        (conectado Bree Rivendell)
        (conectado Bree Tharbad)

        ;; Tharbad
        (conectado Tharbad Hobbiton)
        (conectado Tharbad Bree)
        (conectado Tharbad HelmsDeep)

        ;; Helm's Deep
        (conectado HelmsDeep Tharbad)
        (conectado HelmsDeep Edoras)
        (conectado HelmsDeep Isengard)

        ;; Isengard
        (conectado Isengard HelmsDeep)
        (conectado Isengard Fangorn)

        ;; Fangorn
        (conectado Fangorn Isengard)
        (conectado Fangorn AmonHen)

        ;; Amon Hen
        (conectado AmonHen Fangorn)
        (conectado AmonHen Lothlorien)
        (conectado AmonHen DeadMarshes)

        ;; Dead Marshes
        (conectado DeadMarshes AmonHen)
        (conectado DeadMarshes MinasMorgul)

        ;; Minas Morgul
        (conectado MinasMorgul DeadMarshes)
        (conectado MinasMorgul MinasTirith)
        (conectado MinasMorgul Orodruin)

        ;; Orodruin
        (conectado Orodruin MinasMorgul)

        ;; Minas Tirith
        (conectado MinasTirith MinasMorgul)
        (conectado MinasTirith Edoras)
        (conectado MinasTirith Tolfolas)

        ;; Tolfolas
        (conectado Tolfolas MinasTirith)
        (conectado Tolfolas DolAmroth)

        ;; Edoras
        (conectado Edoras HelmsDeep)
        (conectado Edoras DolAmroth)

        ;; Dol Amroth
        (conectado DolAmroth Edoras)
        (conectado DolAmroth Tolfolas)

        ;; Lothlorien
        (conectado Lothlorien AmonHen)
        (conectado Lothlorien Moria)

        ;; Moria
        (conectado Moria Lothlorien)
        (conectado Moria Rivendell)

        ;; Rivendell
        (conectado Rivendell Moria)
        (conectado Rivendell Bree)
        (conectado Rivendell HighPass)

        ;; High Pass
        (conectado HighPass Rivendell)
        (conectado HighPass Mirkwood)

        ;; Mirkwood
        (conectado Mirkwood HighPass)
        (conectado Mirkwood Erebor)

        ;; Erebor
        (conectado Erebor Mirkwood)

    )

    ; se busca destruir el anillo
    (:goal
        (anilloDestruido)
    )
)
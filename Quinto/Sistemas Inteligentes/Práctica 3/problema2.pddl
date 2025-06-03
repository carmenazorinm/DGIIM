
(define (problem problema2)
    (:domain ejercicio2)

    (:objects
        ; los personajes
        Hobbit1 Hobbit2 Hobbit3 Hobbit4 Mago1 Mago2 Enano1 - personaje
        ; los recursos
        r_fangorn r_moria r_erebor r_lothlorien r_mirkwood - recurso
        ; las localizaciones
        Hobbiton Bree Rivendell HighPass Mirkwood Erebor Moria Lothlorien Tharbad Fangorn Isengard HelmsDeep Edoras AmonHen MinasTirith DolAmroth Tolfolas MinasMorgul DeadMarshes Orodruin - localizacion
        ; aquí se pasa Mithril como recurso porque es algo que se posee
        Anillo Espada - recurso

    )

    (:init
        ;; Roles del problema
        (esRol Hobbit1 Hobbit)
        (esRol Hobbit2 Hobbit)
        (esRol Hobbit3 Hobbit)
        (esRol Hobbit4 Hobbit)
        (esRol Mago1 Mago)
        (esRol Mago2 Mago)
        (esRol Enano1 Enano)

        ;; recursos 
        (esAnillo Anillo)
        (esEspada Espada)
        (enRecurso r_fangorn Fangorn)
        (esCategoria r_fangorn Madera)
        (enRecurso r_moria Moria)
        (esCategoria r_moria Mineral)
        (esCategoria r_moria Mithril)
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

        ;; tenemos Hobbit1, Hobbit2, Hobbit3 en Hobbiton;
        ;stenemos Hobbit4 en Bree; y tenemos Mago1 en Rivendell y Mago2 en Isengard
        (en Hobbit1 Hobbiton)
        (en Hobbit2 Hobbiton)
        (en Hobbit3 Hobbiton)
        (en Hobbit4 Bree)
        (en Mago1 Rivendell)
        (en Mago2 Isengard)
        (en Enano1 Fangorn)

        ;; Disponibilidad
        (disponible Hobbit1)
        (disponible Hobbit2)
        (disponible Hobbit3)
        (disponible Hobbit4)
        (disponible Mago1)
        (disponible Mago2)

        ;; Enano1 no está disponible
        ;; No se marca como disponible para reflejar que está ocupado

        ;; Objetos en localizaciones
        (enRecurso Anillo Rivendell)
        (enRecurso Mithril Moria)
        (enRecurso Espada Lothlorien)

        ;; Lugar de destrucción
        (lugarDestruccion Orodruin)

        ;; Conectividad de las localizaciones
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

    (:goal
        (anilloDestruido)
    )
)
(define (problem problema_madera)
    (:domain ejercicio5)

    (:objects
        ; los personajes
        Enano1 Enano2 Hobbit1 - personaje
        ; los recursos
        r_fangorn r_moria r_erebor r_lothlorien r_mirkwood - recurso
        ; las localizaciones
        Hobbiton Bree Rivendell HighPass Mirkwood Erebor Moria Lothlorien Tharbad Fangorn Isengard HelmsDeep Edoras AmonHen MinasTirith DolAmroth Tolfolas MinasMorgul DeadMarshes Orodruin - localizacion
    )

    (:init

        ; localizaciones de los personajes
        (en Enano1 Tharbad)
        (en Enano2 Isengard)
        (en Hobbit1 Isengard)

        ; roles de los personajes
        (esRol Enano1 Enano)
        (esRol Enano2 Enano)
        (esRol Hobbit1 Hobbit)

        ; disponibilidad de los personajes -> Enano2 no está disponible
        (disponible Enano1)
        (disponible Hobbit1)

        ; inicializacion de recursos
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

        ;; Conectividad básica 
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

        ; coste de viajar entre localizaciones
        (= (costeCamino Hobbiton Bree) 1)
        (= (costeCamino Hobbiton Tharbad) 1)
        (= (costeCamino Bree Hobbiton) 1)
        (= (costeCamino Bree Rivendell) 1)
        (= (costeCamino Bree Tharbad) 1)
        (= (costeCamino Tharbad Hobbiton) 1)
        (= (costeCamino Tharbad Bree) 1)
        (= (costeCamino Tharbad HelmsDeep) 3)
        (= (costeCamino HelmsDeep Tharbad) 3)
        (= (costeCamino HelmsDeep Edoras) 1)
        (= (costeCamino HelmsDeep Isengard) 1)
        (= (costeCamino Isengard HelmsDeep) 1)
        (= (costeCamino Isengard Fangorn) 1)
        (= (costeCamino Fangorn Isengard) 1)
        (= (costeCamino Fangorn AmonHen) 1)
        (= (costeCamino AmonHen Fangorn) 1)
        (= (costeCamino AmonHen Lothlorien) 3)
        (= (costeCamino Lothlorien AmonHen) 3)
        (= (costeCamino AmonHen DeadMarshes) 1)
        (= (costeCamino DeadMarshes AmonHen) 1)
        (= (costeCamino DeadMarshes MinasMorgul) 1)
        (= (costeCamino MinasMorgul DeadMarshes) 1)
        (= (costeCamino MinasMorgul MinasTirith) 1)
        (= (costeCamino MinasMorgul Orodruin) 1)
        (= (costeCamino Orodruin MinasMorgul) 1)
        (= (costeCamino MinasTirith MinasMorgul) 1)
        (= (costeCamino MinasTirith Edoras) 1)
        (= (costeCamino MinasTirith Tolfolas) 1)
        (= (costeCamino Tolfolas MinasTirith) 1)
        (= (costeCamino Tolfolas DolAmroth) 1)
        (= (costeCamino Edoras HelmsDeep) 1)
        (= (costeCamino Edoras DolAmroth) 1)
        (= (costeCamino DolAmroth Edoras) 1)
        (= (costeCamino DolAmroth Tolfolas) 1)
        (= (costeCamino Lothlorien Moria) 1)
        (= (costeCamino Moria Lothlorien) 1)
        (= (costeCamino Moria Rivendell) 1)
        (= (costeCamino Rivendell Moria) 1)
        (= (costeCamino Rivendell Bree) 1)
        (= (costeCamino Rivendell HighPass) 1)
        (= (costeCamino HighPass Rivendell) 1)
        (= (costeCamino HighPass Mirkwood) 1)
        (= (costeCamino Mirkwood HighPass) 1)
        (= (costeCamino Mirkwood Erebor) 1)
        (= (costeCamino Erebor Mirkwood) 1)

    )

    ; se busca generar madera en Fangorn
    (:goal
        (generando r_fangorn)
    )
    (:metric minimize
        (total-cost)
    )
)
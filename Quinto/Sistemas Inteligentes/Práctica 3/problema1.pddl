(define (problem problema_madera)
  (:domain ejercicio1)

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
  )

  ; se busca generar madera en Fangorn
  (:goal
    (generando r_fangorn)
  )

)
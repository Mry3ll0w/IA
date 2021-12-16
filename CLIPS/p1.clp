;   a   b   c
;   d   e   f
;   g   h   i     Solo se puede indicar al norte de y al oeste de
(deffacts iniciales
    ;Reglas Norte
    (ubicacion A norte D)
    (ubicacion B norte E)
    (ubicacion C norte F)
    (ubicacion D norte G)
    (ubicacion E norte H)
    (ubicacion F norte I)
    ;Reglas Oeste
    (ubicacion B oeste C)
    (ubicacion E oeste F)
    (ubicacion H oeste I)
    (ubicacion A oeste B)
    (ubicacion B oeste E)
    (ubicacion C oeste F)

)
;Definicion de reglas

(defrule sur
    (ubicacion ?y norte ?x)
    =>(assert( ubicacion ?x sur ?y))
)

(defrule este
    ( ubicacion  ?y oeste ?x)
    =>
    (assert(ubicacion ?x este ?y))
)

;Transitividad  x y z 
(defrule t.norte
    (ubicacion ?x norte ?y)
    (ubicacion ?y norte ?z)
    =>
    (assert(ubicacion ?x norte ?z))
)

(defrule t.sur
    (ubicacion ?x sur ?y)
    (ubicacion ?y sur ?z)
    =>
    (assert(ubicacion ?x sur ?z))
)

(defrule t.este
    (ubicacion ?x este ?y)
    (ubicacion ?y este ?z)
    =>
    (assert(ubicacion ?x este ?z))
)

(defrule t.oeste
    (ubicacion ?x oeste ?y)
    (ubicacion ?y oeste ?z)
    =>
    (assert(ubicacion ?x oeste ?z))
)
;Definir Noreste, Sureste, Noroeste y Suroeste
;   A   B   C
;   D   E   F
;   G   H   I

(defrule noroeste
   (ubicacion ?b norte ?e)(ubicacion ?b oeste ?c)
    =>
    (assert(ubicacion ?c noroeste ?e))
)

(defrule noreste
    (ubicacion ?e este ?d)
    (ubicacion ?d norte ?g)
    =>
    (assert(ubicacion ?e noreste ?g))
)
;   A   B   C
;   D   E   F
;   G   H   I


(defrule suroeste
    (ubicacion ?d oeste ?e )
    (ubicacion ?d norte ?g)
    =>
    (assert(ubicacion ?g suroeste ?e))
)

(defrule sureste
    (ubicacion ?f norte ?i)
    (ubicacion ?f este ?e)
    =>
    (assert(ubicacion ?i sureste ?e))
)


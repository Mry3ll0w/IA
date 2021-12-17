;1)Gestion de valvulas

(deftemplate valvula
    (slot nombre (default ""))
    (slot T1 (default 0))
    (slot T2 (default 0))
    (slot presion (default 0))
    (slot estado (default cerrada)(allowed-values abierta cerrada))
)

(deffacts inicial_valvula
    (valvula	(nombre	Entrada)	(T1	101)	(T2	35)		(presion 1))
	(valvula	(nombre	Salida)		(T1	101)	(T2	155)	(presion 5))
	(valvula	(nombre	Pasillo1)	(T1	99)		(T2	37)		(estado	cerrada))
)

;Reglas de las valvulas


;R1: Si	una	válvula	está abierta con un	valor de 
;presión de	5, entonces la válvula se cierra	
;y se baja la presión a 0
(defrule r1
    ?v <- (valvula (presion ?vp)(estado ?ve))
    (test (eq ?vp 5)); ?vp == 5
    (test (eq ?ve abierta))
    =>
    (modify ?v (estado cerrada)(presion 0))
)


;R2
;Si	una	válvula	cerrada	tiene un valor de presión	
;menor de 10	y una temperatura T1 mayor	de	35	
;entonces esta válvula deberá abrirse y	aumentar	
;la	presión	en función	de	la	temperatura	T1

;Funcion necesaria para R2
(deffunction aumenta_presion (?p ?t)

    ;bucle while
    (while (> ?t 35)
        ;sumas en 1 la presion
        (bind ?p(+ ?p 1))
        ;disminuye en 5 temp
        (bind ?t(- ?t 5))
    )

    (return ?p)
)

;Regla r2
(defrule r2

    ?v <- (valvula (presion ?vp) (estado ?ve)(T1 ?vt1))
    (test (eq ?ve cerrada))
    (test (< ?vp 10))
    (test (> ?vt1 35))
    =>
    (modify ?v (estado abierta) (presion (aumenta_presion ?vp ?vt1) ) )
)

;REGLA NUMERO 3

;Funcion R3
;Para	decrementar	la	temperatura	crea	una	función	que	reciba	como	argumentos	
;las	dos	temperaturas,	T1	y	T2,	si	la	temperatura	T2	es	mayor	que	la	temperatura	
;T1	entonces	T2=	T2-T1
(deffunction decrementa_temp (?t1 ?t2)

    (if (> ?t2 ?t1) then
        (bind ?t2 (- ?t2 ?t1))
    )

    (return ?t2)

)


;R3: Si	dos	válvulas	distintas,	v1	y	v2,		tienen	la	misma	temperatura	T2,	y	la	
;temperatura	T1	de	la	válvula	v2,	es	menor	que	T2,	entonces	se	decrementa	la	
;temperatura	T2	de	la	válvula	v2	y	se	abren	ambas	válvulas.
(defrule r3
    ?v1 <- (valvula (nombre ?n1)  (T1 ?v1t1)(T2 ?v1t2) (estado cerrada))
    ?v2 <- (valvula (nombre ?n2) (T1 ?v2t1)(T2 ?v1t2) (estado cerrada)) 
    ;el nombre tiene que ser distinto para que no entre la misma valcula 2 veces
    
    ;Si t1 de v2 es menor que t2 de v2
    (test (< ?v2t1 ?v1t2) )
    => 
    (modify ?v2 (T2 (decrementa_temp ?v2t1 ?v1t1))(estado abierta))
    (modify ?v1 (estado abierta))
)


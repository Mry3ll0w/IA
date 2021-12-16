(deftemplate pacman     
    (slot posx (default 1)) ;Cuando muere se pone a 1 
    (slot posy (default 1)) ; Cuando muere se pone a 1
    (slot frutas (default 0))
    (slot vidas ) ; NUmero de intentos

)


(deftemplate fantasma
    (slot posx)
    (slot posy)
)

(deftemplate fruta
    (slot posx)
    (slot posy)
)


;REGLAS

(defrule comer
    ;Se necesita crear una variable para modificar/eliminar un elemento
    ?p <- (pacman (posx ?px) (posy ?py) (frutas ?fr ) (vidas ?pv))
    ?f <- (fruta (posx ?px) (posy ?py)); se usa la misma variable para no tener que usar un test
    =>
    ;1) aumentar contador de fruta
    (modify ?p(frutas (+ ?fr 1)));fr ++
    ;2) eliminas la fruta
    (retract ?f)

    (printout t "Una fruta menos"crlf); crlf = \n

)

(defrule morir
    
    ?p <- (pacman (posx ?px) (posy ?py) (frutas ?fr ) (vidas ?pv))
    ?f <- (fantasma (posx ?px) (posy ?py))
    =>
    ;Pierde una vida y vuelve a pos 1,1 el pacman
    (modify ?p (vidas (- ?fr 1)  )); vida -= 1
    (modify ?p ((posx 1) (posy 1) )); Pos inicial
)

(defrule ganar
    
    ?p <- (pacman (posx ?px) (posy ?py) (frutas ?fr ) (vidas ?pv))
    (test (eq ?fr 10))
    =>
    ;Al ganar eliminamos  el comecocos
    
    (retract ?p)
    (printout t "Has ganado"crlf)

)

(defrule gameover

    (declare (salience 1)); Cambiar la prioridad para evitar el bucle infinito dandole preferencia a gameover
    
    ?p <- (pacman (posx ?px) (posy ?py) (frutas ?fr ) (vidas ?pv))
    (test (eq ?pv 0))
    
    =>
    
    ;(retract ?p) Se elimina el retract para hacer uso de prioridad, si se elimina no es necesaria la prioridad
    ; Se puede a eleccion
    (printout t "Has Perdido"crlf)

)

; Template producto
(deftemplate producto
    (slot id_producto)
    (slot nombre)
    (slot pasillo (allowed-values 1 2 3 4 5 6 7 8 9 10 11 12) )
    (slot precio)
    (slot stock)
)

; Template Pedido

(deftemplate pedido
    (slot id_cliente)
    (slot id_producto)
    (slot unidades)
)

;Template Carro 
(deftemplate carro
    (slot id_cliente )
    (slot articulos_comprados (default 0))
    (slot importe_total (default 0))
    (slot pasillo_actual (allowed-values 1 2 3 4 5 6 7 8 9 10 11 12) )
)

(deftemplate cliente
    (slot id_cliente )
    (slot pasillo (default 1)
    (allowed-values 1 2 3 4 5 6 7 8 9 10 11 12)
    )
    (slot factura (default 0))
    (slot n_productos (default 0))
)

;FACTORES DE ENTEROS

(deffacts	productos

(producto	
        (id_producto	1)	
        (nombre	leche)
        (pasillo	3)	
        (stock	45)	
        (precio	1)
)
(producto	
    (id_producto	2)	
    (nombre	galletas)	
    (pasillo	4)
    (stock		10)	
    (precio	2.20)
)
(producto	
    (id_producto	3)	
    (nombre	cafe)	
    (pasillo	5)	
    (stock	2)	
    (precio	2.6)
)
(producto	
    (id_producto	4)	
    (nombre	arroz)	
    (pasillo	12)	
    (stock	30)	
    (precio	1.98)
)

(cliente (id_cliente 33))

(pedido	(id_cliente	33)	(id_producto	1)	(unidades	3))
(pedido	(id_cliente	33)	(id_producto	2)	(unidades	30))
)

;REGLAS 

;ASIGNAR A UN CARRO
(defrule asignar_carro
    ?c <- (cliente (id_cliente ?idc))
    =>
    (assert (carro (id_cliente ?idc)))

)


;MOVER CARRO

;Funcion incrementar pasillo
(deffunction incrementa_pasillo (?p) 
    ;Primero incremento
    (bind ?p (+ ?p 1))

    ;Compruebo si supera a 12
    (if (> ?p 12 )then
        (bind ?p 1)
    )

(return ?p)
)

(defrule mover_carro
    ?ca <- (carro (id_cliente ?c_carro) (pasillo_actual ?c_pasillo))
    ?ped <- (pedido (id_cliente ?c_ped) (id_producto ?p_prod))
    ?prod <- (producto (id_producto ?prod_id) (pasillo ?prod_pas))

    (test (eq ?c_carro ?c_ped));Cliente tiene que coicidir
    (test (eq ?p_prod ?prod_id));Coincide pasillo
    (test (neq ?c_pasillo ?prod_pas));No coincide pasillo 
    =>
    (modify ?ca ( pasillo_actual 
        (incrementa_pasillo ?c_pasillo) ) 
    ) 

)


;Regla Comprar


(defrule comprar
    (declare (salience 1));AUMENTA LA PRIORIDAD
    ?ca <- (carro (pasillo_actual ?c_pasillo)
            (id_cliente ?c_cliente)
            (importe_total ?c_importe)
            )
    
    ?pr <- (producto (id_producto ?prod_id) 
            (pasillo ?p_pasillo)(stock ?p_stock)
            (precio ?pr_precio)
            )
    
    ?ped <- (pedido (id_producto ?ped_idprod) 
            (id_cliente ?ped_cliente))

    (test (eq ?p_pasillo ?c_pasillo));
    (test (eq ?prod_id ?ped_idprod))
    (test (eq ?c_cliente ?ped_cliente))
    (test (> ?p_stock 0))

    

    =>
    (retract ?ped)
    (modify ?pr (stock (- ?p_stock 1) ))
    (modify ?ca (importe_total (+ ?c_importe ?pr_precio )))


)

;Regla inexistente
(defrule insufiente

    ?pr <- (producto (id_producto ?prod_id) 
            (stock ?p_stock)
            (precio ?pr_precio)
            )
    
    ?ped <- (pedido
        (id_producto ?ped_idpro)
        (id_cliente ?ped_cliente)
         
    )
    (test (eq ?prod_id ?ped_idpro))
    (test (< ?p_stock 0))
    =>
    (printout t "No existe stock cliente: "?ped_cliente crlf)
    (retract ?ped)
)
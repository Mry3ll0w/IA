
;TEMPLATES DEL BANCO
(deftemplate cuenta
    (slot DNI )
    (slot Saldo (default 0))
    (slot estado 
        (allowed-values enPantalla dineroEntregado Inicial SuperaLimite SinSaldo)
        (default Inicial)
    )
)

(deftemplate tarjeta
    (slot DNI )
    (slot Pin)
    (slot Intentos (default 3))
    (slot Limite)
    (slot Anno (default 2022))
    (slot valida (default false)(allowed-values false true))
)

(deftemplate usuario
    (slot DNI )
    (slot Pin)
    (slot Cantidad (default 0))
)

;FACTORES
(deffacts iniciales
    ;Usuarios
    (usuario (DNI 123456)(Pin 1212)	(Cantidad 300))
    (usuario (DNI 456456)(Pin 1211)	(Cantidad 200))
    (usuario (DNI 456456)(Pin 4545)	(Cantidad 3000))
    
    ;Tarjetas
    (tarjeta	(DNI	123456)	(Pin	1212)	(Intentos	3)	(Limite	500)	(Anno	2022))
    (tarjeta	(DNI	456456)	(Pin	4545)	(Intentos	3)	(Limite	500)	(Anno	2022))	
    (tarjeta	(DNI	000111)	(Pin	0011)	(Intentos	0)	(Limite	500)	(Anno	2022))	
    
    ;cuentas
    (cuenta	(DNI	123456)	(Saldo	5000))
    (cuenta	(DNI	456456)	(Saldo	33))
    (cuenta	(DNI	000111)	(Saldo	30000))
)

;Interfaz para introducir datosa un usuario
(defrule input_data

    ;no hay nada que validar asi que se ponen directamente abajo del consecuente
    =>
    (printout t "Introduce el DNI del titular de la tarjeta"crlf)
    (bind ?dni(read))

    (printout t "Introduce El pin de tu tarjeta"crlf)
    (bind ?pin(read))

    (printout t "Introduce la cantidad que deseas sacar"crlf)
    (bind ?cant(read))

    (assert (usuario (DNI ?dni) (Pin ?pin) (Cantidad ?cant)))
)



;VALIDACION DE LA TARJETA

;Cuando	se	supera	el	límite	se	informa mediante	un	mensaje.	El	
;número	de	intentos	debe	verificarse	antes	que	cualquier	otro	requisito.
(defrule Supera_Intentos

    ?t<-(tarjeta (Intentos ?t_int)(DNI ?dni))
    (test (<= ?t_int 0)); Si los intentos han llegado a 0 se 
    =>
    (printout t "Se han superado el limite de intentos de la tarjeta de "?dni crlf)
)

;Pin_Invalido: Cuando	no	se	valida	el	Pin	se	informa	mediante	mensaje.
(deffunction dec_intento (?intento)
    
    (bind ?intento (- ?intento 1))

    (return ?intento)

)

(defrule Pin_Invalido
    ?t<-(tarjeta (Pin ?tpin) (DNI ?tdni)(Intentos ?tint))
    ?u<-(usuario (Pin ?upin) (DNI ?udni))
    
    (test (eq ?tdni ?udni)); Hay que ver que las tarjetas coincidan en dni con un usuario    
    (test (neq ?tpin ?upin)); si no son iguales print pin invalido
    (test (> ?tint 0));Comprobamos si los intentos son mayores que 0
    =>
    (printout t "El pin de la tarjeta no es correcto")
    (modify ?t(Intentos (dec_intento ?tint)))
)

;Valida tarjeta
(defrule Valida_Tarjeta
    
    ?t <- (tarjeta (Pin ?tpin) (DNI ?tdni)(Intentos ?tint)(valida false))
    ?u <- (usuario (Pin ?upin) (DNI ?udni))

    (test (eq ?tdni ?udni));Comprobamos que esa tarjeta sea de ese usuario
    (test (eq ?tpin ?upin));Comprobamos que el pin sea correcto
    (test (> ?tint 0));Comprobamos que los intentos son mayores que 0
    => 
    (modify ?t(valida true))


)



;Fecha invalida
(defrule tarjeta_invalida
    ?t<-(tarjeta (Anno ?date))

    (test (>= ?date 2020));Comprobamos que la tarjeta sea mas nueva o del año 2020
    =>
    (printout t "Tarjeta con fecha invalida, se elimina del sistema")
    (retract ?t);eliminamos la tarjeta invalida
)


;COMPROBACIONES DE SALDO Y ENTREGA DE DINERO

;1) Si la tarjeta es valida muestra el saldo y cambia el estado a enPantalla
(defrule muestra_saldo

    ?t<-(tarjeta (valida true)(DNI ?t_dni))
    ?c<-(cuenta (DNI ?cdni)(estado ?cest)(Saldo ?saldo))

    (test (eq ?t_dni ?cdni));Mira que la cuenta corresponda a esa tarjeta
    
    =>
    (modify ?c(estado enPantalla))
    (printout t "Saldo: " ?saldo crlf)

)


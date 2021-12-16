
;El	portal	proporciona	a	los	clientes un	formulario	con	las	siguientes	preguntas:
;1. Cantidad	de	dinero	que	desea	gastarse
;2. Maletero	pequeño,	mediano	o	grande
;3. Mínimo	número	de	r_cab	del	motor
;4. Sistema	ABS
;5. Consumo	máximo	de	combustible	a	los	100	km

;Si	el	usuario	deja	algún	campo	en	blanco	se	asume	lo	siguiente:
;• El	precio	del	coche	no	debe	superar	los	13000	euros		
;• Maletero	grande
;• Mínimo	80	caballos			
;• Sistema	ABS
;• Consumo	máximo	de	8	litros

(deftemplate coche
    (slot modelo (type INTEGER) (allowed-values 0 1 2 3 4 5 )(default 0))
    (slot precio (type INTEGER) (default 13000))
    (slot caballos (type INTEGER))
    (slot ABS (type SYMBOL) (allowed-values si no))
    (slot size_maletero(type SYMBOL)(allowed-values small medium large) (default large))
    (slot consumo (type FLOAT))
)

(deffacts datos 
    (coche(modelo 1)(precio 12000)(size_maletero small)(caballos 65)(ABS no)(consumo 4.7))    
    (coche(modelo 2)(precio 12500)(size_maletero small)(caballos 80)(ABS si)(consumo 4.9))
    (coche(modelo 3)(precio 13000)(size_maletero medium)(caballos 100)(ABS si)(consumo 7.8))
    (coche(modelo 4)(precio 14000)(size_maletero large)(caballos 125)(ABS si)(consumo 6.0))
    (coche(modelo 5)(precio 15000)(size_maletero small)(caballos 147)(ABS si)(consumo 8.5))
) 

(deftemplate respuesta
    (slot precio (type INTEGER) (default 13000))
    (slot caballos (type INTEGER))
    (slot ABS (type SYMBOL) (allowed-values si no))
    (slot size_maletero(type SYMBOL)(allowed-values small medium large) (default large))
    (slot consumo (type FLOAT))
)

;DEFINICION DE UNA VARIABLE GLOBAL
(defglobal 
    ?*r_bugdet* = 0
    ?*r_cab* = 0
    ?*r_abs* = 0
    ?*r_maletero* = "small"
    ?*r_consumo* = 0
)

(defrule preguntas
=>

(printout t "Cuanto dinero puedes gastar??")
(bind ?r_bugdet (read))

(printout t "Cuantos caballos quieres ??")
(bind ?r_cab (read))

(printout t "Quiere A.B.S. ? ")
(bind ?r_abs (read))

(printout t "Cual es el size del maletero que quieres(small/medium/large)? ")
(bind ?r_maletero (read))


(printout t "Cual es el consumo maximo??")
(bind ?r_consumo (read))

;Metemos en respuesta los datos
(assert (respuesta 
    (precio ?r_bugdet)
    (caballos ?r_cab)
    (ABS ?r_abs)
    (size_maletero ?r_maletero)
    (consumo ?r_consumo) 
))

); inicial

;Creamos el test para la comprobacion de los datos introducidos
(defrule tests

   (respuesta 
        (precio ?r_precio)
        (size_maletero ?r_male)
        (caballos ?r_cab)
        (ABS ?r_abs)
        (consumo ?r_litros)
    ) 

   (coche 
        (modelo ?modelo) 
        (precio ?precio)
        (size_maletero ?size_maletero)
        (caballos ?caballos)
        (ABS ?ABS)
        (consumo ?litros)
    )
   
   ;Requisitos para obtener el coche
   ;El test verifica que dos condiciones de cumplan
   (test(<= ?precio ?r_precio))
   (test(eq ?size_maletero ?r_male))
   (test (<= ?r_cab ?caballos))
   (test (eq ?ABS ?r_abs))
   (test (>= ?r_litros ?litros))
    =>
    (printout t "Modelo: " ?modelo crlf)

)

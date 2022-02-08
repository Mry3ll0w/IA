

;PLANTILLAS

(deftemplate via 

    (slot id)
    (slot descripcion)
    (slot cantidad_vehiculos (default 0))

)

(deftemplate semaforo 

    (slot id(allowed-values A B C D))
    (slot s_via);donde esta colocado
    (slot estado (allowed-values rojo verde))
    (slot cantidad_vehiculos (default 0))

)

(deftemplate vehiculo

    (slot matricula)
    (slot tipo (allowed-values automovil camion moto bicicleta))
    (slot accion (allowed-values nada llegando esperando cruzando realizado)(default nada))

)

(deftemplate celula

    (slot id(allowed-values 1 2 3))
    (slot sem_colocado (allowed-values A B C D))
    (slot estado (allowed-values activada desactivada)(default desactivada))
    (slot v_matricula); del coche que la activo por ultima vez

)


;REGLAS 

;Llegando un vehículo (Activando S1): cuando un sensor de tipo 1 es activado por un vehículo que ha
;entrado en la vía, se deberá crear un hecho vehículo para registrarlo en el sistema con la información
;pertinente e indicando que está llegando al semáforo. También habrá que actualizar el estado del
;sensor 1, cuya célula pasa de desactivada a activada, y se mostrará un mensaje del tipo:

(defrule activandoS1

    ?v   <- (vehiculo (matricula ?vm) (tipo ?vt))
    ?c   <- (celula (id 1) (v_matricula ?vm) (sem_colocado ?csem) (estado desactivada))
    ?vi  <- (via (id ?vid))
    ?sem <- (semaforo (id ?csem) (s_via ?vid))
    
    =>
    (modify ?c(estado activada)) 
    (assert (vehiculo (matricula ?vm) (tipo ?vt) (accion llegando)))
    (printout t "Se activa el sensor tipo 1 acaba de ser activado por el/la" ?vt "con matrícula " ?vm " en la vía " ?vid)
)

;R2 
;Cuando el semáforo está en Verde, el vehículo que estaba llegando o estaba
;esperando, deberá continuar su camino para cruzar la vía, por lo tanto en dicho vehículo se ha de
;actualizar la información y mostrarse un mensaje como el siguiente:

;El/la camión con matrícula 1234ASD está cruzando la vía Constitución con la vía Falla.

;Además habría que desactivar los sensores 1 y 2, para reflejar que ya ha pasado por allí el vehículo. El
;número de vehículos que han pasado por el semáforo correspondiente en el intervalo de tiempo dado
;también debe incrementarse, ya que el semáforo está en verde, y cuantos otros campos sean
;necesarios para el buen funcionamiento del sistema. Esta acción de cruce tiene preferencia sobre
;cualquier otra acción

(defrule cruzando 
    
    (declare (salience 100))

    ?ve <- (vehiculo (matricula ?vm) (accion llegando | esperando ) (tipo ?vt) )
    ?vi <- (via (id ?vid) )
    ?sem <- (semaforo (id ?sid) (s_via ?vid) (estado verde) (cantidad_vehiculos ?s_cant))
    ?c1 <- (celula (id 1))
    ?c2 <- (celula (id 2))
    (via (id ?v2))

    (test (neq ?vid ?v2)); para que no sea la misma via

    =>

    (modify ?c1 (estado desactivada)(v_matricula ?vm))
    (modify ?c2 (estado desactivada)(v_matricula ?vm))
    (modify ?sem (cantidad_vehiculos (+ ?s_cant 1)))
    (modify ?vi (cantidad_vehiculos (+ ?s_cant 1)))

    (printout t "El/la " ?vt " con matrícula " ?vm " está cruzando la vía " ?v2  " con la vía" ?vid crlf)
)

;Defrule R3
;Situación actual: En cualquier momento, desde las oficinas de control remoto se pueden realizar
;consultas sobre el estado de los semáforos o de los sensores. Escribe una regla que se activaría con un
;hecho del tipo:
;que muestre en pantalla toda la información de los semáforos. Por ejemplo:
;Semaforos D y C están en Rojo han pasado 12 vehiculos por la via Falla
;Semaforos B y A están en Verde han pasado 10 vehiculos por la via Constitucion
;pereza 




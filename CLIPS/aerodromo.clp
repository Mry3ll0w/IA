
;aeronaves 
;cuentan	 con diferente	 información	 para	 identificar	 la	 aeronave, 
;la	 compañía,	 
;los	aeródromos de origen y	 destino,	
;la	 velocidad	actual		
;Petición que	realiza	la	aeronave	 para	 realizar	 una	 determinada	 
;acción:	 Ninguna, Despegue, Aterrizaje, Emergencia, Rumbo.	 

;Estado	 actual	 de	 la	 aeronave:	 enTierra (valor por defecto),	Ascenso, Crucero, Descenso

(deftemplate aeronave

    (slot identificador)
    (slot company)
    (slot aerodromo_origen)
    (slot aerodromo_destino)
    (slot velocidad_actual)
    (slot peticion (allowed-values Ninguna Despegue Aterrizaje Emergenecia Rumbo ))
    (slot estado_actual (allowed-values enTierra Ascenso Crucero Descenso) (default enTierra))

)

;aeródromos,	
;identificador,	
;la	ciudad	donde	se	encuentran,
;el	estado	del	Radar,	que	puede	tomar	los	valores	ON cuando	funciona	correctamente y	OFF en	cualquier	otra	situación,																							
;el	 radio	 de	 Visibilidad, medido	en	kms	
;la	velocidad	del	viento,	medida	también	en	km/h.

(deftemplate aerodromo

    (slot identificador)
    (slot ciudad)
    (slot estado_radar (allowed-values ON OF))
    (slot radio_visibilidad )
    (slot velocidad_viento)

)

;El	piloto 
;asignado	a	una	determinada	aeronave	para	realizar	un	vuelo	determinado,	y	que	confirma	
;la	acción	requerida	por	una	aeronave	a	través	de	un	campo, estado, cuyos	valores	permitidos	son:	
;OK,	SOS,	Ejecutando,	Stand-by (valor	por	defecto).

(deftemplate piloto

    (slot identificador)
    (slot avion_asignado)
    (slot estado (allowed-values OK SOS Ejecutando Stand-by)(default Stand-by))
)

;vuelos
;entre	 dos	 aeródromos	 (sus	 identificadores), donde	 se	
;especifica	la	distancia,	la	velocidad	de	despegue	(por	defecto	240	km/h) y	la	velocidad	de	crucero	
;estándar	 medida	 de	 acuerdo	 a	 una	 serie	 de	 parámetros	 de	 los	 vuelos	 comerciales	 típicos	 (no	
;entramos	en	más	detalles	en	este	enunciado),	por	defecto 700 km/h.
(deftemplate vuelo 

    (slot origen)
    (slot destino)
    (slot distancia)
    (slot velocidad_despegue (default 240))
    (slot velocidad_crucero (default 700))

)

;-------------------------------------------------- REGLAS -----------------------------------------------------------

;Despegar
;
;la aeronave esta enTierra
;estado_piloto OK
;aerodromo_origen radar ok, visibiliadad > 5, velocidad viento < 75
;Consecuente
;   aeronave : estado = ascenso, velocidad_actual = vuelo.velocidad_despegue, peticion = Ninguna 
;   piloto: accion = Ejecutando
;
(defrule despegar

    ?v <- (vuelo (origen ?vorigen)(destino ?vdestino) (velocidad_despegue ?vdespegue))
    ?av <-(aeronave (identificador ?av_id)(aerodromo_origen ?vorigen)(aerodromo_destino ?vdestino)(estado_actual enTierra))
    ?p <- (piloto (avion_asignado ?p_avion)(estado OK))
    ?ae <-(aerodromo (identificador ?ae_id)(estado_radar ON)(radio_visibilidad ?ae_visi)(velocidad_viento ?ae_viento))

    (test (> ?ae_visi 5))
    (test (< ?ae_viento 75))
    =>
    (modify ?av (estado_actual Ascenso)(velocidad_actual ?vdespegue)(peticion Ninguna))
    (modify ?p(estado Ejecutando))

)

;Regla Excepcion
;Piloto
;    Estado != OK 
;Aeronave
;    Peticion == despegue
;=>
;Aeronave.peticion = EMERGENCIA
;Muestra mensaje por pantalla
(defrule excepcion

    ?p <-(piloto (avion_asignado ?p_av)(estado ?p_estado))
    ?av <-(aeronave(identificador ?av_id)(aerodromo_origen ?av_origen)(aerodromo_destino ?av_destino)(peticion Despegue)
            (company ?av_company))

=>
    (modify ?av (peticion Emergenecia))
    (printout t "El piloto de la aeronave "?p_av " de la company "?av_company "no se encuetra disponible"crlf)

)

;Regla Crucero

;Funcion para calcular el tiempo estimado
;   Se recibe como parametro vuelo.velocidad_Crucero y vuelo.distancia
;
(deffunction tiempo_estimado (?distancia ?velocidad)

    (bind ?distacia(div ?distacia ?velocidad))

(return ?distacia);Contiene el tiempo estimado

)   
;Caracteristicas regla
;piloto
;   
;aeronave
;   estado_actual = Ascenso     peticion = Despegue
;CONSECUENTE
;   aeronave.velocidad_actual = vuelo.velocidad_Crucero
;   Imprime por pantalla tiempo estimado (funcion)
;   piloto.estado = Stand-by
(defrule Crucero

    ?p <- (piloto (avion_asignado ?p_av))
    ?av <- (aeronave (identificador ?av_id)(estado_actual Ascenso)(peticion Despegue)(aerodromo_origen ?ae_origen)
        (aerodromo_destino ?ae_destino))
    ?v <- (vuelo (velocidad_crucero ?v_crucero)(origen ?ae_origen)(destino ?ae_destino)(distancia ?v_distancia))    
    =>
    (modify ?av(velocidad_actual ?v_crucero))
    (modify ?p(estado Stand-by))
    (printout t "El tiempo estimado es de: "(tiempo_estimado ?v_distancia ?v_crucero)  crlf)  
)

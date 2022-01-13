
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
    (slot aerodrom_destino)
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
(deftemplate vuelos 

    (slot origen)
    (slot destino)
    (slot distancia)
    (slot velocidad_despegue (default 240))
    (slot velocidad_crucero (default 700))

)

;-------------------------------------------------- REGLAS -----------------------------------------------------------
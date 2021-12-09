;Factores (son variables)
(deffacts BaseFacts
    (tienePelo Robi)
    (colorLeonardo Robi)
    (rayasNegras Robi)
    (tienePluma Susi)
    (colorBlanco Susi)
    (vuela Susi)
    (comeCarne Robi)
    (comePescado Susi)
)

;R1:	Si	un	animal	tiene	pelo,	entonces	es	mamífero	

(defrule R1
    (pelos ?x) (animal ?x)
    =>
    (assert (mamifero?x))
);Fin r1

;R2:	Si	un	animal	da	leche,	entonces	es	mamífero
(defrule R2
    (da_leche ?x)
    =>
    (assert (mamifero?x))
)

;R3:	Si	un	animal	tiene	plumas	es	un	ave
(defrule R3
    (plumas ?x) 
    =>
    (assert (ave?x))
)

;R4:	Si	un	animal	vuela	y	pone	huevos,	es	ave
(defrule R4
    (vuela ?x) (pone_huevos ?x) 
    =>
    (assert (ave?x))
)

;R5:	Si	un	animal	come	carne,	es	carnívoro
(defrule R5
    (comer_carne ?x) 
    =>
    (assert (carnivoro?x))
)


;R6:	Si	un	animal	tiene	dientes	puntiagudos,	tiene	garras,	tiene	ojos	al	frente	es	carnívoro
(defrule R6
    (dientes_puntiagudos ?x) (garras ?x) (ojos_frente ?x)
    =>
    (assert (carnivoro?x))
)


;R7:	Si	un	animal	mamífero	tiene	pezuñas	es	una	ungulado
(defrule R7
    (mamifero ?x) (pezunas ?x) 
    =>
    (assert (ungulado?x))
)


;R8:	Si	un	animal	mamífero	rumia	es	un	ungulado
(defrule R8
    (rumia ?x) (mamífero ?x) 
    =>
    (assert (ungulado?x))
)


;R9:	Si un	animal	mamífero	y	carnívoro	tiene	color	leonado	con	manchas	oscuras	se	trata	de	un	
;leopardo
(defrule R9
    (mamifero ?x) (carnívoro ?x) (color_leonado ?x) (manchas_oscuras ?x) 
    =>
    (assert (leopardo?x))
)


;R10:	Si	un	animal	mamífero	y	carnívoro	tiene	color	leonado	con	rayas	negras	es	un	tigre	
(defrule R10
    (mamifero ?x) (carnivoro ?x) (leonado ?x) (rayas_negras ?x) 
    =>
    (assert (tigre?x))
)


;R11:	Si	un	animal	ungulado	con	cuello	largo	y	piernas	largas	tienen	manchas	oscuras	es	una	
;jirafa
(defrule R11
    (ungulado ?x) (cuello_largo ?x) (piernas_largas ?x) (manchas_oscuras ?x) 
    =>
    (assert (jirafa?x))
)


;R12:	Si	un	animal	es	un	ungulado	con	rayas	negras	es	una	cebra
(defrule R12
    (ungulado ?x) (rayas_negras ?x) 
    =>
    (assert (cebra?x))
)


;R13:	Si	un	animal	es	ave	y	no	vuela	y	tiene	el	cuello	largo	y	piernas	largas	de	color	blanco	y	
;negro	es	un	avestruz
;(defrule R13
;    (ave ?x) ~(vuela ?x) (cuello_largo ?x) (piernas_largas ?x)
;    =>
;    (assert(avestruz?x))
;)

;R14:	Si	un	animal	es	ave,	no	vuela,	nada,	de	color	blanco	y	negro,	se	trata	de	un	pingüino	
;(defrule R14
;    (ave ?x) (~vuela ?x) (nada ?x) (color_blanco ?x) (color_blanco ?x)
;    =>
;    (assert(pinguino?x))
;)


;R15:	Si	es	un	ave	que	vuela	bien y	come	pescado,	es	un	albatros
(defrule R15
    (ave ?x) (vuela ?x) (comer_pescado ?x)
    =>
    (assert(albatros?x))
)


;R16:	Si	un	animal	es	de	una	especie	y	ese	animal	es	padre	de	otro,	entonces	el	hijo	es	de	la	
;misma	especie. ???????????????????????????


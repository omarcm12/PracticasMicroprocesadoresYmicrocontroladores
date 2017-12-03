;Programa:
;Escriba un programa que invierte la posición de bits, intercambiando el orden de bits
;del mas significativo al menos significativo, del valor dado en:
;I. El registro R31-R30 si R24 es 0,	Z
;II. El registro R29-R28 si R24 es 1,  Y
;III. El programa realizará ninguna accion para cualquier otro valor en R24.
;Nota: El programa debe realizar estas acciones indefinidamente.

.INCLUDE "m1280def.inc"  ;incluir definiciones de registros para 1280

.equ INIT_VALUE = 0   ;valor inicial R14  ;0 Z   ;1 Y

;------------- Inicializar  ----------------

  ldi R24,INIT_VALUE  ;incia con r24 en 0
  ldi r30,0xB0		;z
  ldi r31,0xB0
  ldi r28,0xCA		;y
  ldi r29,0XC0
   	

;------------- ciclo principal  ------------
	
	inicio:
		ldi r20,7		;contador
		ldi r16,1		;mascaras  ..000001
		ldi r17,128		;mascaras  10000..
		cpi r24,0
		breq invierteZ
		cpi r24,1
		breq invierteY
					;en otro caso el programa no hace nada
		rjmp inicio

	invierteZ:     
		mov r18,r30		;registros auxiliares
		mov r19,r31
		and r18,r16		;parte baja
		cpi r18,0
		breq esCeroZ		;el bit fue 0
		rjmp esUnoZ 
		sigueZ:
			cpi r20,0
			breq inicio
			dec r20
			lsl r16		;ajuste de mascaras
			lsr r17
			rjmp invierteZ  
	
	esCeroZ:
		and r19,r17		;parte alta
		cpi r19,0
		breq sigueZ	;ambos bits fueron 0
		
		distintosZ:
			eor r30,r16
			eor r31,r17		;invierte bits
			rjmp sigueZ		
	
	esUnoZ:
		and r19,r17
		cpi r19,0	
		breq distintosZ
		rjmp sigueZ		;ambos fueron 1


	invierteY:     
		mov r18,r28		;registros auxiliares
		mov r19,r29
		and r18,r16
		cpi r18,0		;comparacion parte baja
		breq esCeroY		;el bit fue 0
		rjmp esUnoY 
		sigueY:
			cpi r20,0
			breq inicio
			dec r20
			lsl r16		;ajuste de mascaras
			lsr r17
			rjmp invierteY  
	
	esCeroY:
		and r19,r17
		cpi r19,0
		breq sigueY	;ambos bits fueron 0
		distintosY:
			eor r28,r16
			eor r29,r17		;invierte bits
			rjmp sigueY		
	
	esUnoY:
		and r19,r17
		cpi r19,0	
		breq distintosY
		rjmp sigueY		;ambos fueron 1
	     
;----------------------------------------------
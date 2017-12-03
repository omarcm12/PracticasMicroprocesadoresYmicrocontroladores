.INCLUDE = "m1280def.inc"


inicio:
call DelayB
nop
rjmp inicio


DelayA:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	ldi r24,6 
	nxt:
		ldi r25,206
		nxt2:
			dec r25
			brne nxt2
		dec r24
	brne nxt 
ret

DelayB:
	ldi r24,190
	next:
		ldi r25,139
		nop
		next2:
			dec r25
			brne next2
		dec r24
		brne next
ret

DelayC:
	ldi r24,118
	nxte:
		ldi r25,215
		nxte2:
			ldi r26,139
			nxte3:
				dec r26
				brne nxte3
		dec r25
		brne nxte2
	nop
	nop
	dec r24
	brne nxte		
ret
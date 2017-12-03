dosseg
.model tiny
.code

public _peekb

_peekb PROC  ; Leer el dato (8 bits) en segment:offset  *** regresa dato a C  ***

				;unsigned char peekb(unsigned int segment,unsigned int offset)
	push bp

	mov bp,sp 
				
	mov ax,[bp + 4]	;segment + 4
	mov bx,[bp + 6]	;offset + 6
	mov ds,ax
	mov al,[bx]
	pop bp	
	ret
_peekb ENDP

end
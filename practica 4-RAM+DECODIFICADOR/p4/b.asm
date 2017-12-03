dosseg
.model tiny
.code

public _pokeb

_pokeb PROC ; Escribir el dato (8 bits) en segment:offset
	
	push bp
					;void pokeb(unsigned int segment,unsigned int offset, unsigned char dato);

	mov bp,sp		;segment + 4
					;offset + 6
					;dato + 8
	mov ax,[bp + 4]
	mov bx,[bp + 6]
	mov cl,[bp + 8]
	mov ds,ax
	mov [bx], cl
	

	pop bp	
	ret
	_pokeb ENDP

	end
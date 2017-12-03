dosseg
.model tiny
.code

public _outportb
public _inportb

_outportb PROC  ; Direccion (16 bits) - Dato (8 bits)


	push bp

	mov bp,sp

	mov dx, [bp + 4]	;Direccion
	mov al, [bp + 6]	;dato
	out dx, al

	pop bp
	ret
_outportb ENDP

_inportb PROC  ; Direccion 16 bits

	push bp

	mov bp,sp

	mov dx,[bp + 4]
	in al, dx

	pop bp
	ret
_inportb ENDP



end

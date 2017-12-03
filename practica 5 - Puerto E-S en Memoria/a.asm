dosseg	
.model tiny
.code

public _putchar
public _pokeb
public _pokew


_putchar	PROC
			
	push bp
	
	mov bp,sp
	mov dl,[bp+4]
	mov ah,2
	int 21h
	
	pop bp
	ret

_putchar	ENDP


_pokeb proc ; Escribir el dato (8 bits) en segment:offset
	
	push bp
	
	mov bp,sp

	push ds
	push dx
	push bx

	mov dx,[bp+4]	;segment
	mov bx,[bp+6]	;offset
	mov ax,[bp+8]	;dato

	mov ah,0

	mov ds,dx
	mov [bx],al

	pop bx
	pop dx
	pop ds
	
	pop bp
	ret

_pokeb endp

_pokew proc ; Escribir el dato (16 bits) en segment:offset
	
	push bp
	mov bp,sp

	push ds
	push dx
	push bx

	mov ax,[bp+4]	;segment
	mov bx,[bp+6]	;offset
	mov dx,[bp+8]	;dato

	mov ds,ax
	mov [bx],dx

	pop bx
	pop dx
	pop ds
	
	pop bp
	ret

_pokew endp



END
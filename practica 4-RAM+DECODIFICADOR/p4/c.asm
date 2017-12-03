dosseg
.model tiny
.code

public _print
public _putchar

_print PROC  ; Llega un dato de 16 bits desde c e imprime en hexadecimal
				;void print(unsigned int offset);

	push bp

	mov bp,sp 				
	mov si,[bp + 4]
	
	call printHex
  
	pop bp	
	ret
	_print ENDP

_putchar PROC
	push bp
	mov bp,sp
	mov dl,[bp + 4]
	mov ah,2
	int 21h
	pop bp
	ret

_putchar ENDP

printHex	proc
	
	push si
	push ax
	push cx
	push dx

	mov ax,si    ;para convertir si a hexa
	mov si,16     ;en base 16	
	mov cx,0

	divide:
		mov dx,0
		div si
		push dx  ;guardo el residuo
		inc cx
		cmp ax,0
		je termina
		jmp divide

	termina:
        pop ax
        cmp ax,10
        jl sigue
        add ax, 7
        sigue:
        add ax,48
        mov dl,al
        mov ah,2
        int 21h 
        loop termina

        mov dl,10
        mov ah,2
        int 21h

        mov dl,13
        mov ah,2
        int 21h
        
        pop dx
        pop cx
        pop ax
        pop si
        ret

printHex	endp

END
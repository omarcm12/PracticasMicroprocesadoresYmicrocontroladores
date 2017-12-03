;Carlos Omar Calderon Meza 1217146
;Ingeniero en computacion
;Microprocesadores y microcontroladores

;Practica 1

;Cumpliendo con las siguientes funcionalidades:

;a) Implementar el procedimiento HammingDistance el cual espera los dos números
;en BX y DX y el resultado guardarlo en AX.

;b) Desplegar en pantalla ambos números en binario e imprimir la distancia
;encontrada.

.model tiny
; .STACK 100h
;----- Insert INCLUDE "filename" directives here
;----- Insert EQU and = equates here
locals
.data

.code
org 100h

principal proc

	mov sp,0fffh ; inicializar SP (Stack Pointer)
	mov bx,23h    ;primer numero en hexadecimal
	mov dx,765h	 ;segundo numero en hexadecimal
	mov ax,0     ;incializo ax

	call HammingDistance  ;regresa en ax la distancia

	mov si,bx 
	call printBin  ;mando a imprimir el primer numero
	call saltaLinea

	mov si,dx 
	call printBin  ;mando a imprimir el primer numero
	call saltaLinea
	call saltaLinea

	mov si,ax
	call printDec
	
	ciclo:
	jmp ciclo

	ret
endp
;***************************************************************
; procedimientos
;***************************************************************

HammingDistance proc
	
	push bx   	;salvo los registros
	push dx
	push si
	push cx

		mov si,dx   ;utilizo si para guardar los bits distintos
		xor si,bx	

		mov cx,16	;contador para distancia

		@@cuenta:	
			shr si,1
			jc @@incrementa  ;salta si carry es 1 
			@@sigue:
				loop @@cuenta
	pop cx
	pop si
	pop dx
	pop bx
	ret

	@@incrementa:
		inc ax
		jmp @@sigue

endp

printDec proc     ;recibe en si el numero a imprimir en decimal
	push cx
	push ax
	push dx

	mov ax,si    ;para convertir si a binario
	mov si,10     ;en base 2
	

	mov cx,0

	@@divide2:
		mov dx,0
		div si
		push dx  ;guardo el residuo
		inc cx
		cmp ax,0
		je @@termina2
		jmp @@divide2

	@@termina2:
        pop ax
        add ax,48
        call putchar   
        loop @@termina2

	pop dx
	pop ax	
	pop cx
	ret

endp

printBin proc   ;recibe en si un numero a imprimir en binario
	
	push cx
	push ax
	push dx

	mov ax,si    ;para convertir si a binario
	mov si,2     ;en base 2
	

	mov cx,0

	@@divide:
		mov dx,0
		div si
		push dx  ;guardo el residuo
		inc cx
		cmp cx,16
		je @@termina
		jmp @@divide

	@@termina:
        pop ax
        add ax,48
        call putchar   
        loop @@termina

	pop dx
	pop ax	
	pop cx
	ret

endp


putchar proc    ;procedimiento de la hoja de practica 1 de micros.
	push ax
	push dx
	mov dl,al
	mov ah,2 ; imprimir caracter DL
	int 21h ; usando servicio 2 (ah=2)
	pop dx ; del int 21h
	pop ax
	ret
	endp

saltaLinea proc
	push ax

	mov al,10
	call putchar
	mov al,13
	call putchar

	pop ax
	ret
endp

end principal
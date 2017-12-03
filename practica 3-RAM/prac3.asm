;Carlos Omar Calderon Meza 1217146
;Ingeniero en computacion
;Microprocesadores y microcontroladores

;Practica 3

.model small
; .STACK 100h
;----- Insert INCLUDE "filename" directives here
;----- Insert EQU and = equates here
locals
.data

.code

org 100h

principal proc

	mov sp,0fffh ; inicializar SP (Stack Pointer)
	mov si,0200H	 ; primer direccion a comparar



	@@inicio:
		mov byte ptr 00:[si],55h
		cmp byte ptr 00:[si],55h
		jne @@fallo
		mov byte ptr 00:[si],170 ;AAh
		cmp byte ptr 00:[si],170
		jne @@fallo
		cmp si,0FFFH  
		je @@exito
		inc si
		mov ax,si  ; numero a convertir
        mov bx,10    
        call printNumBase
		jmp @@inicio

	@@fallo:
		mov dl,'F'
		mov ah,2
		int 21h
		jmp @@next

	@@exito:
		mov dl,'E'
		mov ah,2
		int 21h
		jmp @@next

	@@next:
		mov ah,04ch	     ; fin de programa
		mov al,0             ;
		int 21h              ; 


	ret

endp

printNumBase PROC
    
    push ax   ; respaldar registros a utilizar
    push bx
    push cx
    push dx

    mov cx,0    ; utilizo un contador para saber cuentos digitos resultaran en la conversion

    convierte:
      cmp ax,0      ;compara si el cociente de la divicon es 0 para dejar de dividir
      je termina    ; si el igual a 0 termina de convertir
      mov dx,0      ;asegura dx = 0 para la divicon de 32 bits a 16
      div bx        ; divide DX:AX / BX base seleccionada a convertir
      push dx       ;Guardo residuo en la pila para imprimir al final 
      inc cx        ;inclemento el contador
      jmp convierte ;itera a siguiente digito
    

    termina:      
      mov ax,0
      pop ax      ;saco de la pila el ultimo digito guardado
      cmp ax,9    ; comparo los digitos para convertir a ascci
      JBE conviertea  ;convierte numeros menores o iguales a 9 
      add ax,7        ; se le suma 7 para llegar al valor ascci

    conviertea:     
      add ax,30h    ; si el numero es mayor a 9 se suma 30 o 37 si fue menor a 9
    imprime: 
     call putchar   ; imprimo digito 
     loop termina   ; hasta que terminen los digitos
   
    pop dx          ; regreso al estado que estaban los registros antes de entrar al procedimmiento
    pop cx
    pop bx
    pop ax

    ret
    
  ENDP

putchar proc
  		mov dl,al
		mov ah,2
		int 21h
ret
endp

end principal
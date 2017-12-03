#include <avr/io.h>
 #define F_CPU 16000000
void UART0_putchar(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));  //mientras el buffer no este vacio espera
	UDR0 = data;
}

void UART0_puts(char *str)
{
	while(*str)
	UART0_putchar(*str++);
	
}

void itoa(char* str, uint16_t number, uint8_t base)
{
	char aux[20];
	int i=0;
	if(number == 0)
	*str++ = 48;
	aux[i] = number%base;
	i++;
	while(number)
	{
		aux[i] = number%base;
		number =number/base;
		i++;
	}
	i--;
	for(i; i!=0; i--)
	{
		if(aux[i] > 9)
		{
			aux[i] += 7;
		}
		*(str++) = aux[i]+48;
	}
	*(str++) = 0;  //cierre de cadena para evitar basura
}

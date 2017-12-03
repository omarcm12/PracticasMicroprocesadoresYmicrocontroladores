#include <avr/io.h>
void UART0_putchar(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));  //mientras el buffer no este vacio espera
	UDR0 = data;
}

char UART0_getchar( void )
{
	while(!(UCSR0A & (1<<RXC0)));  //mietras la recepcion no este completa
	return UDR0;
}

void UART0_puts(char *str)
{
	while(*str)
	UART0_putchar(*str++);
	
}



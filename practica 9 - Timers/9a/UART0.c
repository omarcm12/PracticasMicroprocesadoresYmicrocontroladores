#include <avr/io.h>
void UART0_Ini( void )
{
	 //19200   UBRR0 = (16000000/(16*19200))-1;
	UBRR0 = 0x33;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}

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




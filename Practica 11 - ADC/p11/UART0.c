#include <avr/io.h>
void UART0_Ini( void )
{
	UCSR0A = 1<<U2X0;					//doble velocidad asincrona UART0
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);		/*		transmision, recepcion     */
	UCSR0C = (3<<UCSZ00);
}


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

uint8_t UART0_available( void )
{
	if(UCSR0A &1<<RXC0)
		return 1;
	else
		return 0;
}

UART0_AutoBaudRate( void )
{
	DDRE = ~(1<<PE0);				//PE0 como entrada
	UCSR0C = 3<<UCSZ00;             //8 bits timer 0
	TCCR0A = 0;						//modo normal timer 0
	TCCR0B = 2<<CS00;				//preescalador en 8 timer 0
	while( PINE & 1<<PE0 );			//mientras no se active el startbit esperar
	TCNT0 = 0;						//inicializa en 0 para el conteo
	while(!(PINE &1<<PE0));
	TCCR0B =0;						//salva el conteo
	
	UBRR0 = TCNT0 - 1;				//1/Time;
}



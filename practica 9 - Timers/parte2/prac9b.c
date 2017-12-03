#include <avr/io.h>
#include "Timer2.h"
#include "UART0.h"

void UpdateClock( void );
void DisplayClock( void );
void PrintDec2d( uint8_t dato);
void SetClock( uint8_t hora, uint8_t minuto, uint8_t segundo);
UART0_AutoBaudRate( void );

uint8_t seg = 0;
uint8_t min = 0;
uint8_t hor = 0;

int main()
{
	char str[20];
	UART0_AutoBaudRate();
	UART0_puts("\n\rAutobauding done. UBRR= ");
	itoa(str,UBRR0,10);
	UART0_puts(str);
	UART0_puts("\n\r");
	Timer2_Ini(7);							/* Inicializar Timer0 para 1 sec.*/
	SetClock(23,59,50);
	while(1)
	{										/* == main loop == */
		if( Timer2_SecFlag() )				/* ¿ha pasado 1 Segundo? */
		{
			UpdateClock();					/* actualiza el reloj			*/
			DisplayClock();
		}
		UART0_putchar(13);
	}										/* fin del loop principal */
	return 0;								/* <-- no se llega aqui */
}

void UpdateClock( void )
{
	seg += base;
	if(seg >= 60)
	{
		seg = seg-60;
		min++;
	}
	if(min == 60)
	{
		hor++;
		min = 0;
	}
	if(hor==24)
		hor = 0;
	
}
void DisplayClock( void )
{
	PrintDec2d(hor);
	UART0_putchar(':');
	PrintDec2d(min);
	UART0_putchar(':');
	PrintDec2d(seg);
}

void PrintDec2d( uint8_t dato)
{
	UART0_putchar( dato/10 +'0'); /* Imprime decenas */
	UART0_putchar( dato%10 +'0'); /* Imprime unidades */
}

void SetClock( uint8_t hora, uint8_t minuto, uint8_t segundo)
{
	hor=hora;
	min=minuto;
	seg=segundo;
}

UART0_AutoBaudRate( void )
{
	DDRE = ~(1<<PE0);				//PE0 como entrada
	UCSR0A = 1<<U2X0;				//doble velocidad asincrona UART0
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //activa transmision y recepcion del UART0
	UCSR0C = 3<<UCSZ00;             //8 bits
	TCCR0A = 0;						//modo normal
	TCCR0B = 2<<CS00;				//preescalador en 8
	while( PINE & 1<<PE0 );			//mientras no se active el startbit esperar
	TCNT0 = 0;						//inicializa en 0 para el conteo
	while(!(PINE & 1<<PE0));
	TCCR0B =0;						//detiene el timer
	
	UBRR0 = TCNT0 - 1;				//1/Time;
}

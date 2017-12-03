#include <avr/io.h>
#include "Timer0.h"
#include "UART0.h"
void UpdateClock( void );
void DisplayClock( void );
void PrintDec2d( uint8_t dato);
void SetClock( uint8_t hora, uint8_t minuto, uint8_t segundo);

uint8_t seg = 0;
uint8_t min = 0;
uint8_t hor = 0;

int main()
{
	DDRB = (1<<PB7);						/* llamar a función para inicializar puertos E/S */
	UART0_Ini();							/* llamar a función para inicializar UART0 */
	Timer0_Ini();							/* Inicializar Timer0 para 1 sec.*/
	SetClock(23,59,50);
	while(1)
	{										/* == main loop == */
		if( Timer0_SecFlag() )				/* ¿ha pasado 1 Segundo? */
		{				
			PORTB |= ( 1 << PB7 );			/* instrucciones para encender LED */
			UpdateClock();					/* actualiza el reloj			*/
			DisplayClock();
			PORTB &= ~( 1 << PB7 );			/* instrucciones para apagar LED */
		}
		UART0_putchar(13);

	}										/* fin del loop principal */
		return 0;							/* <-- no se llega aqui */
}

void UpdateClock( void )
{
	seg = ((++seg)%60);
	if(seg == 0)
	{
		min =  ((++min)%60);
		if (min == 0)
		{
			hor = ((++hor)%24);
		}
	}
	
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
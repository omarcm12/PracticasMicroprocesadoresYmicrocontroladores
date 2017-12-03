/*  Practica 5
	Microprocesadores y microcontroladores
	Carlos Omar Calderon Meza  */


#include "Timer.h"
#define BYTE unsigned char



void UpdateClock( void );
void DisplayClock( void );
void PrintDec2d( BYTE );
void Delay( BYTE );
void SetClock( BYTE, BYTE, BYTE);

extern void putchar(char x);
extern void pokeb(unsigned int segment,unsigned int offset, unsigned char dato);

BYTE seg=0;
BYTE min=0;
BYTE hor=0;

void main()
{
	Timer_Ini(); /* inicialzaTimer de 1 segundo */
	pokeb(0x0000, 0xFFFF, seg);
	SetClock(23,59,50);

	while(1)
	{
		/* Verificaci�n para actualizar el reloj */
		if(TimerSecFlag() )
		{ /* Ha pasado un segundo? */
			UpdateClock(); /* actualiza y muestra el reloj */
			DisplayClock(); /* desplegar reloj en 0,0 */
			pokeb(0x0000, 0xFFFF, seg);
			/* indicar en puerto */
		}
	
/* otras cosas por hacer */
	Delay(100);
	putchar(13);
	}
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
	putchar(':');
	PrintDec2d(min);
	putchar(':');
	PrintDec2d(seg);

}
void Delay( BYTE i)
{
	while(--i);
}

void PrintDec2d( BYTE dato)
{
	putchar( dato/10 +'0'); /* Imprime decenas */
	putchar( dato%10 +'0'); /* Imprime unidades */
}

void SetClock( BYTE hora, BYTE minuto, BYTE segundo)
{
	hor=hora;
	min=minuto;
	seg=segundo;
}

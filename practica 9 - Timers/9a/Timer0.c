#include <avr/interrupt.h>
#include <inttypes.h>
static volatile uint8_t SecFlag = 0;

// #TIKS = 1ms/(1/16Mhz/64))-1

void Timer0_Ini ( void ){
	OCR0A = 249;					/* Establecer valor de OCR0A*/					
	TCNT0 = 0x00;
	TCCR0A = 2<<WGM00;				/* inicializa timer0 en modo CTC */
	TCCR0B = 3<<CS00;				/* con Prescalador 64 */				
	TIMSK0 = 1<<OCIE0A;				/*Habilita interrupcion Output compare Match A */
	sei();
}
uint8_t Timer0_SecFlag ( void )
{
	if( SecFlag )
	{
		SecFlag=0;
		return 1;
	}
	else
		return 0;
	
}
ISR ( TIMER0_COMPA_vect )					/* Timer/Counter0 Compare Match A */
{			
	static uint16_t mSecCnt;
	mSecCnt++;						/* Incrementa contador de milisegundos */
	if( mSecCnt==1000 )
	{
		mSecCnt=0;
		SecFlag=1;					/* Bandera de Segundos */
	}
}


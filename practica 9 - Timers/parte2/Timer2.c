#include <avr/interrupt.h>
#include <inttypes.h>
static volatile uint8_t SecFlag = 0;

// #TIKS = 1s/((1/32768/1024))-1 = 255

void Timer2_Ini ( uint8_t baseT ){
	
	TIMSK2 = 1;				//Disable the Timer/Counter2 interrupts by clearing OCIE2x and TOIE2.
	ASSR = 1<<AS2;			 //Select clock source by setting AS2 as appropriate.
	TCNT2 = 0x00;			 //Write new values to TCNT2, OCR2x, and TCCR2x.
	TCCR2A = 2<<WGM20;		 //ctc
	OCR2A = 31*baseT;//		(baseT/(1/(32768/1024)))-1;
	TCCR2B = 7<<CS20;		//pre-escalador
	while(ASSR & ((1<<TCN2UB)|(1<<OCR2AUB)|(1<<TCR2AUB)|(1<<TCR2BUB)));//To switch to asynchronous operation: Wait for TCN2UB, OCR2xUB, and TCR2xUB.
	TIFR2 = 1;						//Clear the Timer/Counter2 Interrupt Flags.
	TIMSK2 = 1<<OCIE2A;						//Enable interrupts, if needed.
	sei();
}

uint8_t Timer2_SecFlag ( void )
{
	if( SecFlag )
	{
		SecFlag=0;
		return 1;
	}
	else
		return 0;
	
}
ISR ( TIMER2_COMPA_vect )					/* Timer/Counter2 Compare Match A */
{	
	SecFlag=1;					/* Bandera de Segundos */	
}

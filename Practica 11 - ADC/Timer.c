#define TICKS(f) (62500/f)-1
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "UART0.h"

static volatile uint8_t SecFlag = 0, silencio = 0, tocando = 0, volumen = 50, fin, i;		//banderas de estado
static volatile uint16_t  tam, myCont = 0, tiempo;
static volatile struct note *myMusic;


void Timer2_Freq_Gen(uint8_t ticks)
{
	/* 	Si "ticks" es mayor que 0 entonces, inicializa y habilita el Generador 
		de Frecuencia del Timer2 con el tope dado por "ticks".
		De lo contrario se requiere deshabilitar el Generador, generando de 
		esta forma el silencio (0 lógico). */
	
	if(ticks)
	{
		OCR2A = ticks;	
		OCR2B = OCR2A*volumen/100;						
		TCCR2B = (1<<WGM22) | (6<<CS20);		//TOP OCR2A - preescalador 256
		myCont = 0;		
		tocando = 1;						//inicia la reproduccion de la nota							
	}
	else
	{
		TCCR2B = 0;  //detiene el timer2
		myCont = 0;	//inicia el silencio
		silencio = 1;
	}
}

void Timer2_Play(const struct note song[],unsigned int len)
{
	/*	Función que establece las condiciones necesarias para que
		el generador recorra el arreglo de notas. */
	myMusic = song;
	i=0; fin=0; tam=len;	
	DDRH |= (1<<PH6);								//como salida OC2B
	TCCR2A = (3<<WGM20)|(2<<COM2B0);			
	Timer2_Freq_Gen(0);								//Inicia la cancion									
}


ISR( TIMER0_COMPA_vect ){ 
	/* 	Código para actualizar bandera de segundos */
	static uint16_t mSecCnt;
	mSecCnt++;						/* Incrementa contador de milisegundos */
	myCont ++;
	if( mSecCnt==1000 )
	{
		mSecCnt=0;
		SecFlag=1;					/* Bandera de Segundos */
	}

	/*	Agregar las instrucciones necesarias para reproducir
		la siguiente nota en el arreglo dependiendo de la duración, 
		e insertar los silencios entre cada nota. */
	if(fin == 0)
	{
		if(tam == 0)
		{
			fin = 1;
			TCCR2B = 0;
		}
			
		if(tocando)
		{
			if(myCont >= tiempo)
			{
				Timer2_Freq_Gen(0);
				tocando = 0;
			}
		}
		if(silencio)
		{
			if(myCont >= SILENCE)
			{
				Timer2_Freq_Gen(TICKS(myMusic[i].freq));
				tiempo = myMusic[i].delay;
				i++;
				tam--;
				silencio = 0;
			}
		}
		
	}
	
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

void Timer2_Volume(uint8_t direction){
	/* 	Ajusta el ciclo de trabajo para incrementar o decrementar  el volumen
	   	de las notas que se estan generando. */
	
	volumen = direction;
	
}

void Timer0_Ini ( void ){
	/* 	Permanece igual, ocasionando una interrupción 
		cada 1 ms en modo CTC. */
	OCR0A = 249;					/* Establecer valor de OCR0A					 */
	TCNT0 = 0x00;
	TCCR0A = 2<<WGM00;				/* inicializa timer0 en modo CTC				 */
	TCCR0B = 3<<CS00;				/* con Prescalador 64							 */
	TIMSK0 = 1<<OCIE0A;				/* Habilita interrupcion Output compare Match A  */
	sei();
}

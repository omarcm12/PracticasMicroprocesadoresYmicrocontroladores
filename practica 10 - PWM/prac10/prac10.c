#include "UART0.h"
#include "Timer.h"
UART0_AutoBaudRate( void );


const struct note ImperialMarch[]=
{
	//for the sheet music see:
	//http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
	//this is just a translation of said sheet music to frequencies / time in ms
	//used TEMPO ms for a quart note
	{a, TEMPO},
	{a, TEMPO},
	{a, TEMPO},
	{f, TEMPO*3/4},
	{cH, TEMPO*1/4},

	{a, TEMPO},
	{f, TEMPO*3/4},
	{cH, TEMPO*1/4},
	{a, TEMPO*2},
	//first bit

	{eH, TEMPO},
	{eH, TEMPO},
	{eH, TEMPO},
	{fH, TEMPO*3/4},
	{cH, TEMPO*1/4},

	{gS, TEMPO},
	{f, TEMPO*3/4},
	{cH, TEMPO*1/4},
	{a, TEMPO*2},
	//second bit...

	{aH, TEMPO},
	{a, TEMPO*3/4},
	{a, TEMPO*1/4},
	{aH, TEMPO},
	{gSH, TEMPO/2},
	{gH, TEMPO/2},

	{fSH, TEMPO*1/4},
	{fH, TEMPO*1/4},
	{fSH, TEMPO/2},
	{0,TEMPO/2},
	{aS, TEMPO/2},
	{dSH, TEMPO},
	{dH, TEMPO/2},
	{cSH, TEMPO/2},
	//start of the interesting bit

	{cH, TEMPO*1/4},
	{b, TEMPO*1/4},
	{cH, TEMPO/2},
	{0,TEMPO/2},
	{f, TEMPO*1/4},
	{gS, TEMPO},
	{f, TEMPO*3/4},
	{a, TEMPO*1/4},

	{cH, TEMPO},
	{a, TEMPO*3/4},
	{cH, TEMPO*1/4},
	{eH, TEMPO*2},
	//more interesting stuff (this doesn't quite get it right somehow)

	{aH, TEMPO},
	{a, TEMPO*3/4},
	{a, TEMPO*1/4},
	{aH, TEMPO},
	{gSH, TEMPO/2},
	{gH, TEMPO/2},

	{fSH, TEMPO*1/4},
	{fH, TEMPO*1/4},
	{fSH, TEMPO/2},
	{0,TEMPO/2},
	{aS, TEMPO/2},
	{dSH, TEMPO},
	{dH, TEMPO/2},
	{cSH, TEMPO/2},
	//repeat... repeat

	{cH, TEMPO*1/4},
	{b, TEMPO*1/4},
	{cH, TEMPO/2},
	{0,TEMPO/2},
	{f, TEMPO/2},
	{gS, TEMPO},
	{f, TEMPO*3/4},
	{cH, TEMPO*1/4},

	{a, TEMPO},
	{f, TEMPO*3/4},
	{c, TEMPO*1/4},
	{a, TEMPO*2}
	//and we're done
};


int main(void)
{
	UART0_AutoBaudRate();
	UART0_puts("Reproduccion iniciada\n\r");
	Timer0_Ini();
	
	
	while(1){
		switch(UART0_getchar()){
			case 'v' : Timer2_Volume(-1);
			break;
			case 'V' : Timer2_Volume(1);
			break;
			case 'p' :
			case 'P' : Timer2_Play(ImperialMarch,sizeof(ImperialMarch)/sizeof(struct note));
			break;
			default : break;
		}
	}
	return 0;
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
	while(!(PINE &1<<PE0));
	TCCR0B =0;						//salva el conteo
	
	UBRR0 = TCNT0 - 1;				//1/Time;
}

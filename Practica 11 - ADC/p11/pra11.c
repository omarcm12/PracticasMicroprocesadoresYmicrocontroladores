#include "UART0.h"
#include "Timer.h"
#include "ADC.h"
#include<avr/io.h>
#define PHOTORESISTOR PORTA0

void Timer2_Set_Volume(uint8_t volume);

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
	char cad[20];
	UART0_Ini();
	UART0_AutoBaudRate();
	Timer0_Ini();
	ADC_Ini();
	ADC_MinMax(PHOTORESISTOR);
	while(1){
		if (UART0_available()){
			if(UART0_getchar() == 'p'){
				Timer2_Play(ImperialMarch,sizeof(ImperialMarch)/sizeof(struct note));
			}
		}
		itoa(cad,ADC_Normalize(ADC_Read(PHOTORESISTOR)),10);
		UART0_puts(cad);
		UART0_puts("\n\r");
		Timer2_Volume(ADC_Normalize(ADC_Read(PHOTORESISTOR)));
	}
	return 0;
}


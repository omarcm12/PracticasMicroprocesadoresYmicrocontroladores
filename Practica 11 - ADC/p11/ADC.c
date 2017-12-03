#include <avr/io.h>
#include "UART0.h"
static volatile uint8_t offset, var, menor, mayor;

void ADC_Ini ( void )
{
	char cad[10];
	ADMUX = (1<<REFS0)|(0x1f<<MUX0)|(1<<ADLAR);  // 8 bits y a tierra la medicion
	ADCSRB &=~(1<<MUX5);				//parte de medicion a tierra
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(7<<ADPS0);  //activa ADC, inicia conversion, prescaler 128
	while(ADCSRA & (1<<ADSC));				//espera a que termine la conversion
	offset = ADCH;
	itoa(cad,offset,10);
	UART0_puts("Offset\n\r");
	UART0_puts(cad);
	UART0_puts("\n\r");
}

/*Está función lo que realiza es una lectura del ADC usando el canal correcto y retornando el
valor de 8 bits acorde a la aplicación (ver figura 1), compensando el desplazamiento de la
medición.*/
uint8_t ADC_Read( uint8_t channel )
{
	uint8_t aux;
	char cad[10];
	
	if(channel > 7)
	{
		DIDR2 = 0;		//desactiva la parte digital
		ADMUX =(1<<REFS0)|((channel-8)<<MUX0)|(1<<ADLAR);
		ADCSRB |=1<<MUX5;
	}
	else
	{
		DIDR0 = 0;		//desactiva la parte digital
		ADMUX =(1<<REFS0)| (channel<<MUX0)|(1<<ADLAR);
		ADCSRB &=~(1<<MUX5);
	}
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(7<<ADPS0);
	while(ADCSRA&(1<<ADSC));				//espera a que termine conversion
	aux = ADCH;
	
	return aux - offset;
}

/*Función que captura el rango de valores, encuestando primero por el mínimo.*/

void ADC_MinMax( uint8_t channel )
{
	char cad[10];
	
	UART0_puts("Valor menor listo?\n\r");
	UART0_getchar();
	UART0_getchar();
	menor=ADC_Read(channel);
	itoa(cad,menor,10);
	UART0_puts(cad);
	UART0_puts("\n\r");
	UART0_puts("Valor mayor listo?\n\r");
	UART0_getchar();
	mayor=ADC_Read(channel);
	itoa(cad,mayor,10);
	UART0_puts(cad);
	UART0_puts("\n\r");
	UART0_puts("Termino min_Max\n\r");
	
}



/*Esta función inicializa para 8 bits de resolución y habilita el ADC del microcontrolador de
forma generica. Encontrar el desplazamiento (offset) de la medición y almacenarla.*/

uint8_t ADC_Normalize(uint8_t value)
{
	if(value > mayor)
	value = mayor;
	if(value < menor)
	value = menor;
	
	return 100-(((value-menor)*100)/(mayor-menor));
}
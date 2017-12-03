#include <avr/io.h>
#include"UART0.h"
#define uint16_t unsigned int
#define uint8_t unsigned char


int main( void )
{
	char cad[20];
	unsigned int num;
	UART0_Ini(1);
	while(1)
	{
		UART0_getchar();
		UART0_puts("\n\rIntroduce un número:\n\r");
		UART0_gets(cad);
		num = atoi(cad);
		itoa(cad,num,2);
		UART0_puts("\n\rBin:");
		UART0_puts(cad);
		itoa(cad,num,16);
		UART0_puts("\n\rHEx:");
		UART0_puts(cad);
	}
	return 0;
}



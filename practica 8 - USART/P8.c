#include <avr/io.h>
#define uint16_t unsigned int
void UART0_putchar(char data);
void UART0_puts(char *str);
char UART0_getchar( void );
void UART0_Ini(uint16_t mode);

int main( void )
{
	char cad[20];
	uint16_t num;
	UART0_Ini(1);
	while(1)
	{
		UART0_puts("\n\rIntroduce un número:\n\r");
		UART0_getchar();
	}
	return 0;
}

void UART0_Ini(uint16_t mode)
{
	if(mode)
	{
		//19200,8,N,1
		//UBRR0 = (12000000/(8/19200))-1;
		//UCSR0A = 1<<U2X0;
		UBRR0 = 0x33;

	}
	else
	{
		//9600,8,N,1
		UBRR0 = (12000000/(8/9600))-1;
	}
			UCSR0B = (1<<RXEN0)|(1<<TXEN0);
			//UCSR0C = (3<<UPM00)|(1<<UCSZ01)|(1<<UCSZ00);
			UCSR0C = (3<<UCSZ00) | ~();
}

void UART0_putchar(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));  //mientras el buffer no este vacio espera
	UDR0 = data;
}

char UART0_getchar( void )
{
	while(!(UCSR0A & (1<<RXC0)));  //mietras el buffer no este vacio
	return UDR0;
}

void UART0_gets(char *str)
{
	char dato = UART0_getchar();
	while(dato!=13)
	{
		if(dato == 8)
		{
			UART0_putchar(" ");
			UART0_putchar('\b');
			*str--;
			*str = '\0';
		}
		else
		*str++ = dato;

		dato = UART0_getchar();
	}
}

void UART0_puts(char *str)
{
	while(*str)
		UART0_putchar(*str++);
	
}
void itoa(char *str, uint16_t number, uint8_t base)
{
	char aux[20];
	int i=0;
	aux[i] = number%base;
	for(i=1; number != 0; i++)
	{
		aux[i] = number%base;
		number =(int)number/base;
	}
	i--;
	for(i; i!=0; i--)
	{
		if(aux[i] > 9)
		{
			aux[i] += 7;
		}
		*str++ = aux[i]+48;
	}
	*str = '\0';  //cierre de cadena para evitar basura
}

uint16_t atoi(char *str)
{
	uint16_t pos = 1, res = 0, numeros[5], i=0, j = 0;
	
	while(*str)
	{
		if(*str >= 48 && *str <= 57)
		{
			numeros[i] = *str - 48;
			*str++;
			pos *= 10;
			j++; i++;
		}
		else
		break;
	}
	
	pos /= 10;  //ajuste a la potencia
	for(i=0; j>0; i++)
	{
		res += numeros[i] * pos;
		pos /= 10;
		j--;
	}
	
	return res;
}
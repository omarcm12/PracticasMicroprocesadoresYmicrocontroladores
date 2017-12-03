#include <avr/io.h>
void UART0_Ini(uint16_t mode)
{
	if(mode)  //19200   UBRR0 = (16000000/(16*19200))-1;
	{
		UBRR0 = 0x33;
	}
	else  //9600
	{
		UBRR0 = 0x66;
	}
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}
void UART0_putchar(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));  //mientras el buffer no este vacio espera
	UDR0 = data;
}

char UART0_getchar( void )
{
	while(!(UCSR0A & (1<<RXC0)));  //mietras la recepcion no este completa
	return UDR0;
}

void UART0_puts(char *str)
{
	while(*str)
	UART0_putchar(*str++);
	
}

void itoa(char* str, uint16_t number, uint8_t base)
{
		char aux[20];
		int i=0;
		if(number == 0)
			*str++ = 48;
		aux[i] = number%base;
		i++;
		while(number)
		{
				aux[i] = number%base;
				number =number/base;
				i++;	
		}
		i--;
		for(i; i!=0; i--)
		{
			if(aux[i] > 9)
			{
				aux[i] += 7;
			}
			*(str++) = aux[i]+48;
		}
	*(str++) = 0;  //cierre de cadena para evitar basura
}


uint16_t atoi(char *str)
{
	uint16_t pos = 1, res = 0, i=0;
	
	while(*str)
	{
		if(*str >= 48 && *str <= 57)
		{
			*str++;
			i++;
		}
		else
			break;
	}
	for(i; i!=0; i--)
	{
		*str--;	
		res = res + ((*str - 48)*pos);
		pos *=10;
	}
			
	return res;
}


void UART0_gets(char *str)
{
	int cont = 0;
	char dato = UART0_getchar();
	UART0_putchar(dato);
	while(dato!=13)
	{
		if(dato == 8)
		{
			if(cont>0)
			{
				UART0_putchar(" ");
				UART0_putchar('\b');
				*str--;
				*str = '\0';
				cont --;
			}
		}
		else
		{
			if(cont <=19)
			{
				*str++ = dato;
				cont ++;
			}
		}
		dato = UART0_getchar();
		UART0_putchar(dato);
	}
	*str = '\0';
}


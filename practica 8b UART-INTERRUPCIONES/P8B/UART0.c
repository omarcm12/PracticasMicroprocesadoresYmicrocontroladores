#include <avr/io.h>
#include <avr/interrupt.h>

#define BUFFER_SIZE 64
#define MOD(n) n&(BUFFER_SIZE-1)
#define IS_BUFFER_EMPTY(buffer) buffer.in_idx == buffer.out_idx
#define IS_BUFFER_FULL(buffer) buffer.in_idx == MOD(buffer.out_idx - 1)

typedef struct
{
	char buffer[BUFFER_SIZE];				/*	espacio reservado			*/
	volatile unsigned char in_idx :6;		/*	indice entrada (Head)		*/
	volatile unsigned char out_idx :6;		/*	indice entrada (tail)		*/
} ring_buffer_t;

ring_buffer_t bufferRx;
ring_buffer_t bufferTx;

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
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);		/*		transmision, recepcion e interrupcion de recepcion      */
	UCSR0C = (3<<UCSZ00);
	sei();								/*		Ativa las interrupciones glovales						*/
	
	UCSR0B = UCSR0B|(1<<RXCIE0);		/*		Activa interrupcion de recepcion completa				*/
	bufferRx.in_idx = 0;
	bufferRx.out_idx = 0;
	bufferTx.in_idx = 0;
	bufferTx.out_idx = 0;
}

void UART0_putchar(char data)	
{
	while((IS_BUFFER_FULL(bufferTx)));				/* espera si la cola esta llena*/
	
	if(IS_BUFFER_EMPTY(bufferTx))					/* si la cola esta vacia */
	{
		bufferTx.buffer[bufferTx.in_idx++] = data;  /* ingresa el dato en la cabeza y aumenta*/			
		UCSR0B = UCSR0B|(1<<UDRIE0);				/* Activar interrupcion Transmision completa*/
	}
	else
	{
		bufferTx.buffer[bufferTx.in_idx++] = data;  /*ingresa el dato en la cabeza y aumenta*/	
	}	
}

ISR( _VECTOR(26) )									/* Registro de transmision vacio */
{
	if(IS_BUFFER_EMPTY(bufferTx))					/* si la cola esta vacia */
		UCSR0B = UCSR0B&(~(1<<UDRIE0));				/*desactivar la interrupcion*/
	else
		UDR0 = bufferTx.buffer[bufferTx.out_idx++];	/* Manda el dato de la cola al UDR0*/

}

uint8_t UART0_available( void )				/* Retorna 1 si existe datos en la cola */
{
	return  bufferRx.in_idx == bufferRx.out_idx ? 0:1;
}

char UART0_getchar( void ) 
{
	while((IS_BUFFER_EMPTY(bufferRx)));					/*	espera si no hay datos en la cola */
	
	return bufferRx.buffer[bufferRx.out_idx++];			/*	Regrasa el dato				*/
}

ISR( _VECTOR(25) )										/* Recepcion completa */
{
	while(IS_BUFFER_FULL(bufferRx));					/* espera si esta llena la cola */
	
	bufferRx.buffer[bufferRx.in_idx++] = UDR0;
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
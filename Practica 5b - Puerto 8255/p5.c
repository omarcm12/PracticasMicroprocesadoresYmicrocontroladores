/*		Practica 5b
			Microprocesadores y microcontroladores
			Carlos Omar Calderon Meza 	1217146
			Ingeniero en computacion*/

#define BYTE unsigned char
#define WORD unsigned int
#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43
#define PTOs_all_out 0x80

extern void outportb( WORD, BYTE );  /*funciones externas en lenguaje ensamblador*/
extern BYTE inportb( WORD );

void setBitPort( WORD puerto, BYTE num_bit );
void clrBitPort( WORD puerto, BYTE num_bit );
void notBitPort( WORD puerto, BYTE num_bit );
BYTE tstBitPort( WORD puerto, BYTE num_bit );
BYTE reverseBitPort( WORD puerto );
void printBin( BYTE );
char getch( void );
void putchar( char dato );
void puts(char *cad );
char getchar( void );

void main( void )
{
	char dato, temp, num_bit;

	puts("practica 5b\n\r"); /* imprimir mensaje */
	outportb(RCtr, PTOs_all_out); /* inicializar 8255 */
	outportb(PA,0x55); /* presentar 55h en el Pto A */

	while(1)
	{
		puts("\n\rIngrese un dato\n\r");
		dato = getch(); /* leer tecla */
		printBin(dato);
		outportb(PB,dato); /* presentar tecla en PB */
		num_bit = 2;

		puts("\n\rsetBitPort\n\r");
		setBitPort(PB,num_bit);
		dato = inportb(PB);
		printBin(dato);
		getch();

		puts("\n\rclrBitPort\n\r");
		clrBitPort(PB,num_bit);
		dato = inportb(PB);
		printBin(dato);
		getch();

		puts("\n\rnotBitPort\n\r");
		notBitPort(PB,num_bit);
		dato = inportb(PB);
		printBin(dato);
		getch();

		puts("\n\rtstseBitPort\n\r");
		temp = tstBitPort(PB,num_bit);
		dato = inportb(PB);
		printBin(dato);
		if(temp == 1)
			puts("\n\rEstado de bit : 1\n\r");
		else
			puts("\n\rEstado de bit : 0\n\r");
		getch();

		puts("\n\rreverseBitPort\n\r");
		reverseBitPort(PB);
		dato = inportb(PB);
		printBin(dato);

	}

}

/*funcion que activa un bit*/
void setBitPort( WORD puerto, BYTE num_bit )
{
	outportb( puerto, inportb(puerto)|(0x01 << num_bit) );
}

/*funcion que desactiva un bit*/
void clrBitPort( WORD puerto, BYTE num_bit )
{
	outportb( puerto, inportb(puerto) & (~(0x01 << num_bit)) ); /* con ~ ingresa 1's por la derecha*/
}

/*funcion que invierte un bit*/
void notBitPort( WORD puerto, BYTE num_bit )
{
	outportb( puerto, inportb(puerto)^(0x01 << num_bit) );
}

/*funcion que retorna el estado de un bit*/
BYTE tstBitPort( WORD puerto, BYTE num_bit )
{
	if( inportb(puerto) & (0x01 << num_bit) )
		return 1;
	else
		return 0;
}

/*funcion que inverte el orden de los bits*/
BYTE reverseBitPort( WORD puerto )
{
	BYTE masSig = 7, menosSig = 0, mask1 = 0x80, mask2 = 0x01;
	int i;
	for(i=0; i<4; i++)
	{
		if(inportb(puerto)&mask1) /*comparacion principal*/
		{
				if(inportb(puerto)&mask2) /*Ambos 1's*/
				{
						mask1 >>= 1; mask2 <<= 1;
						masSig --; menosSig ++;
				}
				else		/*distintos*/
				{
						notBitPort(PB,masSig);
						notBitPort(PB,menosSig);
						mask1 >>= 1;	mask2 <<= 1;
						masSig --; menosSig ++;
				}
			}
			else
			{
				if(inportb(puerto)&mask2) /*distintos*/
				{
						notBitPort(PB,masSig);
						notBitPort(PB,menosSig);
						mask1 >>= 1;	mask2 <<= 1;
						masSig --; menosSig ++;
				}
				else /*Ambos 0's*/
				{
					mask1 >>= 1;	mask2 <<= 1;
					masSig --; menosSig ++;
				}
			}
		}
}

/* función simple para desplegar un byte en formato binario */
void printBin( BYTE dato )
{
	BYTE msk=0x80;
	do
	{
		putchar( (dato & msk) ? '1' : '0' );
		msk>>=1;
	}while( msk );
}
/* funcion simple para imprimir una cadema*/
void puts(char *cadena)
{
	while( *cadena )
		putchar( *cadena++ );
}

/*Despliega en pantalla un byte*/
void putchar( char dato )
{
	asm mov dl, dato
	asm mov ah,2
	asm int 21h
}

/*Retorna un byte ingresado desde el teclado*/
char getch( void )
{
	char dato;

	asm mov ah,8
	asm int 21h
	asm mov dato, al

	return dato;
}

/* funcion para ingresar un valor por teclado con ECO*/
char getchar( void )
{
	char dato;

	asm mov ah,1
	asm int 21h
	asm mov dato, al

	return dato;
}

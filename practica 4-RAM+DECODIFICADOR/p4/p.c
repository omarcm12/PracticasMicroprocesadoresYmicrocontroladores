/*		CARLOS OMAR CALDERON MEZA
		PRACTICA 3
		MICROPROCESADORES Y MICRONCONTROLADORES
		INGENIERO EN COMPUTACION - FCQI			*/

extern unsigned char peekb(unsigned int segment,unsigned int offset);   /*Leer el dato (8 bits) en segment:offset*/
extern void pokeb(unsigned int segment,unsigned int offset, unsigned char dato); /*Escribir el dato (8 bits) en segment:offset*/
extern void print(unsigned int offset);
void fallo( void );
void exito( void );
extern void putchar(char dato);

int main( void )
{
	unsigned int segment = 0x00, offset = 0x5000;
	
	while(1)
	{
		print(offset);

		pokeb(segment, offset, 0x55);  /*Escribir el dato (8 bits) en segment:offset*/
		if( peekb(segment, offset) != 0x55)	/*Leer el dato (8 bits) en segment:offset*/
			fallo();
  
		pokeb(segment, offset, 0xAA);  /*Escribir el dato (8 bits) en segment:offset*/
		if( peekb(segment, offset) != 0xAA)	/*Leer el dato (8 bits) en segment:offset*/
			fallo();
		
		if(offset == 0x57FF)		/*Llega hasta la ultima direccion fisica y cambia a las direcciones espejo*/  
			offset = 0xD000;
		
		if(offset == 0xD7FF)		/*Al leer todas las direciones fisicas y espejo marca el exito*/
			exito();

		offset ++;

	}


	return 0;
}

void fallo()
{
	putchar('F');
	while(1)
	{
		/*   NADA  */
	}
}

void exito()
{
	putchar('E');
	while(1)
	{
		/*   NADA  */
	}
}


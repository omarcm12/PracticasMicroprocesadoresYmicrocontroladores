/*		Practica 2

Carlos Omar Calderon Meza 127146
Ingeniero en computacion
Microprocesadores y microcontroladores
*/

void getch( void );
unsigned long int generarNumero( int, unsigned long int );
unsigned long int alteraNumero( unsigned long int, unsigned unsigned long int, unsigned long int, int );
unsigned long int deMenosSig( unsigned long int, unsigned long int );
unsigned long int deMasSig( unsigned long int, unsigned long int );
void putchar( char );
void saltaLinea( void );
void imprimir( unsigned long int );

int main( void )
{

	while(1)
	{  	
		unsigned long int MSB = 2147483648, x = 2147483647, LSB = 1; /*La idea es 1000000... 0111111... 000001*/
		int n = 8, m=3, dif = 32 - (n+1);
	
		x = generarNumero(dif,x);
		imprimir(x);
		saltaLinea();
		x = alteraNumero(MSB,LSB,x,m);
		saltaLinea();
		imprimir(x);
		saltaLinea();

		getch();
	}
	
	return 0;

}

void imprimir( unsigned long int numero )
{

		unsigned long int recorre = 2147483648; 	
		int i=0;
	
		while(i<32)
		{
			if(recorre & numero)
				putchar(49);
			else
				putchar(48);

			recorre >>= 1;
			i++;
		}

}

unsigned long int alteraNumero( unsigned long int MSB, unsigned long int LSB, unsigned long int x, int m )
{
	int bandera = 0;
	
	while(m>0)
	{
			if(bandera==1)
			{
				x = deMasSig(MSB,x);
				bandera = 0;
			}	
			else
			{
				x = deMenosSig(LSB,x);
				bandera = 1;
			}
			m--;
	}

	return x;

}

unsigned long int deMenosSig( unsigned long int LSB, unsigned long int x )
{
	int bandera = 1, i = 0;
	unsigned long int MSB = 2147483648;

	while(i<32)
	{
		if(x & LSB)
		{
			if(bandera==1)
			{
				x = x^LSB;
				bandera = 0;
			}
			else
				bandera =1;
		}

		LSB <<=1;
		i++;
	}

	return x;
	
}

unsigned long int deMasSig( unsigned long int MSB, unsigned long int x )
{
	int i = 0, bandera = 1;

	while(i<32)
	{
		if(x & MSB)
		{
			if(bandera==1)
			{
				x = x^MSB;
				bandera = 0;
			}
			else
			{
				bandera =1;
			}
		}
		MSB >>=1;
		i++;
	}

	return x;
	
}

void saltaLinea()
{
	putchar(10);
	putchar(13);
}
	
unsigned long int generarNumero( int dif, unsigned long int x )
{
	int i;
	for(i=0; i<dif; i++)
	{
		x >>= 1;
	}

	return x;	
}

void getch( void )
{
	asm mov ah,8
	asm int 21h
}

w
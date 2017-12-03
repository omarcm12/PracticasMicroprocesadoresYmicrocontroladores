#include<stdio.h>

void generarNumero(int m,long int *x);
void alteraNumero(unsigned int MSB, unsigned int LSB, long int *x, int m);
void deMenosSignificativo(unsigned int LSB, long int *x);
void deMasSignificativo(unsigned int LSB, long int *x);

struct numero
{
	int alto;
	int bajo;	
};

int main()
{

	unsigned int contador = 2147483648;
	long int  numero = 2147483647;
	unsigned int MSB = 2147483648, LSB = 1;  
	int n = 10, m=3, i;
	int diferencia = 32 - (n+1);
	
	generarNumero(diferencia,&numero);
	
	for(i=0; i < 32; i++)
	{
		if(contador & numero)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		contador >>= 1;
	
	}
		printf("\n");
	
	alteraNumero(MSB,LSB,&numero,m);
	contador = 2147483648;
	
	for(contador; contador > 0; contador >>= 1)
	{
		if(contador & numero)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	
	}
	
		printf("\n%ld",numero);
	return 0;
}

void alteraNumero(unsigned int MSB, unsigned int LSB, long int *x, int m)
{
	int bandera = 0;
	
	for(m; m>0; m--)
	{
			if(bandera==1)
			{
				deMasSignificativo(MSB,x);
				bandera = 0;
			}	
			else
			{
				deMenosSignificativo(LSB,x);
				bandera = 1;
			}
				
	}	
}

void deMenosSignificativo(unsigned int LSB, long int *x)
{
	int bandera = 1;
	for(LSB; LSB<2147483648; LSB <<=1)
	{
		if(*x & LSB)
		{
			if(bandera==1)
			{
				*x = *x^LSB;
				bandera = 0;
			}
			else
			{
				bandera =1;
			}
		}
	}
	
}


void deMasSignificativo(unsigned int MSB, long int *x)
{
	int bandera = 1;
	for(MSB; MSB>0; MSB >>=1)
	{
		if(*x & MSB)
		{
			if(bandera==1)
			{
				*x = *x^MSB;
				bandera = 0;
			}
			else
			{
				bandera =1;
			}
		}
	}
}

void generarNumero( int m, long int *x)
{
	int c=0;
	while(c<m)
	{
		*x >>= 1;
		c++;
	}
}

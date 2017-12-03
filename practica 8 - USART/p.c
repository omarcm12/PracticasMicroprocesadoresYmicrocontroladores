#include<stdio.h>
#include<conio.h>

#define uint16_t unsigned int 
#define uint8_t unsigned char 

uint16_t atoi(char *str);
void itoa(char* str, uint16_t number, uint8_t base);
void getss(char *str);
void putss(char *str);

int main()
{
	char cad[20];
	getss(cad);
	putss(cad);
	return 0;
}

void putcharr(char dato)
{
	printf("%c",dato);
}

void getss(char *str)
{
	char dato =_getch();
	putcharr(dato);
	while(dato!=13)
	{
		if(dato == 8)
		{
			putcharr(" ");
			putcharr('\b');
			*str--;
			*str = '\0';
		}	
		else
			*str++ = dato;

		dato =_getch();
		putcharr(dato);
	}
}
void putss(char *str)
{
	while(*str)
		putcharr(*str++);
	
}

void itoa(char* str, uint16_t number, uint8_t base)
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
	*str = 0;  //cierre de cadena para evitar basura
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


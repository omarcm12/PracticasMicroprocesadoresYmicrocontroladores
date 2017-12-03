#include<stdio.h>
#define uint16_t unsigned int 
#define uint8_t unsigned char 

uint16_t atoi(char *str);
void itoa(char* str, uint16_t number, uint8_t base);
int main()
{
	char cad[20];
	uint16_t res;
//	scanf("%s",cad);
//	res:16;
	res = atoi("ase23");
//	printf("\n\n%d",res);
	printf("\n\n");
	itoa(cad, res,16);
	printf("\n\n%s",cad);
	return 0;
}

void itoa(char* str, uint16_t number, uint8_t base)
{
	char aux[20];
	int i=0;
	if(number ==0 )
		*str++ = 48;
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
	if(res >65535)
		res = 0;
	return res;
}

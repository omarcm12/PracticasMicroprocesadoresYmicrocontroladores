#ifndef _TIMER2_H
#define _TIMER2_H
#include <inttypes.h>
/* Función para inicializar el Timer0 y generar */
/* la temporización de 1 Sec. */
void Timer2_Ini ( uint8_t baseT );
/* Función para verificar bandera del segundo */
uint8_t Timer2_SecFlag ( void );
#endif
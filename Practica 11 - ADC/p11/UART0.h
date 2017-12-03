#include <inttypes.h>
void UART0_putchar(char data);
void UART0_puts(char *str);
char UART0_getchar( void );
void itoa(char *str, uint16_t number, uint8_t base);
uint8_t UART0_available( void );
void UART0_Ini( void );
void UART0_AutoBaudRate( void );
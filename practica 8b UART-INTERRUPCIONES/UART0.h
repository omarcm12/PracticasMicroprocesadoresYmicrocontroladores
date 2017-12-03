void UART0_putchar(char data);
void UART0_puts(char *str);
char UART0_getchar( void );
void UART0_Ini(uint16_t mode);
void itoa(char *str, uint16_t number, uint8_t base);
uint16_t atoi(char *str);
void UART0_gets(char *str);
uint8_t UART0_available( void );

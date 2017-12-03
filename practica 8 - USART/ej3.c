//
#define BAUD    9600
#define F_CPU   8000000L
 
#include &lt;avr/io.h&gt;
/* Macros para el calculo del Registro UBRR */
#include &lt;util/setbaud.h&gt;
#include &lt;avr/interrupt.h&gt;
 
void UsartInit();
void UsartPutChar(char c);
void UsartPutString(char* s);
char UsartGetChar();
char UsartKbhit();
 
/* Manejador de la interrupción por dato recibido en la USART */
ISR(USART_RXC_vect) {
 
    /* Se envía el dato recibido */
    UsartPutChar(UDR);
 
}
 
int main() {
 
    UsartInit();
 
    /* Se habilitan las interrupciones globales */
    sei();
 
    while(1) {}
 
    return 0;
}
 
void UsartInit() {
 
    UBRRL = UBRRL_VALUE;
    UBRRH = UBRRH_VALUE;
 
    UCSRC = _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1);
 
    /* Se habilita la interrupción por dato recibido. */
    UCSRB = _BV(RXEN) | _BV(TXEN)| _BV(RXCIE);
}
 
void UsartPutChar(char c) {
    while (!(UCSRA & _BV(UDRE)));
    UDR = c;
}
 
void UsartPutString(char* s) {
    while (*s)
        UsartPutChar(*s++);
}
 
char UsartGetChar() {
    while (!(UCSRA & _BV(RXC)));
    return UDR;
}
 
char UsartKbhit() {
    return (UCSRA & _BV(RXC));
}
//
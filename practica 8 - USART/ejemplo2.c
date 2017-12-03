#define BAUD    9600
#define F_CPU   8000000L
 
#include &lt;avr/io.h&gt;
// Macros para el calculo del Registro UBRR
#include &lt;util/setbaud.h&gt;
 
void UsartInit();
void UsartPutChar(char c);
void UsartPutString(char* s);
char UsartGetChar();
char UsartKbhit();
 
int main() {
 
    UsartInit();
 
    while(1) {
 
        if(UsartKbhit()) {
 
            UsartPutChar(UsartGetChar());
 
        }
    }
 
    return 0;
}
 
void UsartInit() {
 
    UBRRL = UBRRL_VALUE;
    UBRRH = UBRRH_VALUE;
 
    UCSRC = _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1);
 
    UCSRB = _BV(RXEN) | _BV(TXEN);
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
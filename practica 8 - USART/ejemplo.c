57600, 5, PO, 16Mhz

void UART3_Ini(){
   UBRR3 = (16000000/(8/57600))-1;       //U2X = 1 
   //UBRR3 = 34;
   UCSR3A=1<<U2X3;
   UCSR3B=(1<<TXEN3)|(1<RXNE3);
   UCSR3C=(3<<UPM30)|(1<<USBS3)|(1<<UCSZ30); 
} 

VOID UART3_SEND(char DATA){
	while(!(UCSR3A & (1<<UDRE3))){
		
		UDRE3 = data;
	}
}

char UART3_getchar(void){
	while(!(UCSR3A & (1<<UDRE3))){
		
		return UDR3;
	}
}

//el unico led disponible es L4 portB bit7
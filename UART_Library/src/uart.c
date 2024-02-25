#include "uart.h"
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL)))-1)

void UART_init(){
	UCSRA = (1<<U2X);
	UCSRB = (1<<TXEN)|(1<<RXEN); // The flags are set automatically no need for interrupt
	UCSRC = (1<<URSEL) | (1<<UCSZ1)| (1<<UCSZ0);
	// UBRR is about 2bytes divided to UBRR_High & UBRR_Low
	// Therefore if you have a data more than 1 byte then store this data in  UBRR_High
	// Since URSEL is the first bit in UBRR then it will be set to 0;
	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;
}
void UART_sendByte(uint8 data){
	UDR = data; //Transmit
	while(bitIsClear(UCSRA,TXC)); // Wait for transmit flag
	setBit(UCSRA,TXC); //Clear flag
}
uint8 UART_recieveByte(){
	while(bitIsClear(UCSRA,RXC)){}
	setBit(UCSRA,RXC);
	return UDR;
}
void UART_sendString(uint8 *Str){
	uint8 i = 0;
	while(Str[i] != '\0'){
		UART_sendByte(Str[i]);
		i++;
	}
	UART_sendByte('#');
}
void UART_recieveString(uint8 * Str){
	uint8 i = 0;
	Str[i] = UART_recieveByte(); // Checks if there is even a msg
	while(Str[i] != '#'){ // The agreed stop symbol because there is no representation in data.
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0'; // let the agreed stop sign be the end of the string.
}

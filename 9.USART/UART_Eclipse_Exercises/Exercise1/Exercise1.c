/*
 * Exercise1.c
 *
 */ 

#include "uart.h"

int main(void)
{
	uint8 Str[20];
	uint8 data;
	UART_init();
    while(1)
    { 
		data = UART_recieveByte(); //Receive Byte from Terminal1
		UART_sendByte(data); //Resend the received byte to Terminal2
		//UART_receiveString(Str); //Receive String from Terminal
	    //UART_sendString(Str); //Resend the string to Terminal2
    }
}

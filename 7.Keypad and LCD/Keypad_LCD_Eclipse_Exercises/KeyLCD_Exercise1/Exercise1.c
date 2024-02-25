/*
 * Exercise1.c
 *
 */ 

#include "keypad.h"

int main(void)
{
	uint8 key;
	DDRC  |= 0x0F; /* 7-segment pins as output pins */
	PORTC &= 0xF0; /* 7-segment displays Zero at the beginning */
    while(1)
    {
        key = KeyPad_getPressedKey(); /* get the pressed button from keypad */
	    if((key >= 0) && (key <= 9))
		{ 
			 PORTC = key;
		}						
    }
}

/*
 * MC1.c
 *
 * 
 */

#include "keypad.h"
#include "spi.h"

int main(void)
{
	uint8 key;
	SPI_initMaster(); //intitialize Master MC
    while(1)
    {
		key = KeyPad_getPressedKey(); //get the pressed key
		SPI_sendByte(key); //send the pressed key to the second MC using spi
		_delay_ms(500); //press time is 500msec
    }
}



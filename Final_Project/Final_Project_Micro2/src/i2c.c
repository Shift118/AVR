#include "i2c.h"

void TWI_init(){
	TWBR = 0x02; // Bit Rate: 400.000 kbps using 0 prescaler "TWSR" and F_cpu = 8MHZ;
	TWSR = 0;
///////////////////////////

/*TWAR Register:-
    Bit 7:1 - TWA6: TWA0: TWI address bits
	TWI address bits contain TWI 7-bit address with which it can called by other masters in slave mode.

	Bit 0 – TWGCE: TWI general call enable bit
	TWI general call enable bit when set it enables recognition of general call over the TWI bus
*/
	TWAR = 0b00000010;  // My address for slave mode.
	TWCR = (1<<TWEN); // TWI enable bit
}
void TWI_start(){
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // Clear flag for further use , Start bit, Enable I2C bit
	while(bitIsClear(TWCR,TWINT)); // While is cleared wait , But when transmit is successful continue.
}
void TWI_stop(){
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); // Clear flag for further use , Stop bit, Enable I2C Bit.
	// Here I don't care about checking the flag because I have already stopped.
}
void TWI_write(uint8 data){
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);// Clear flag for further use, Enable I2C bit
	while(bitIsClear(TWCR,TWINT));
}
uint8 TWI_readWithACK(){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(bitIsClear(TWCR,TWINT));
	return TWDR;
}
uint8 TWI_readWithNACK(){
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(bitIsClear(TWCR,TWINT));
	return TWDR;
}
uint8 TWI_getStatus(){
	uint8 status;
	status = TWSR & 0xf8; // I only need the last 5 bit (status bits)
	return status;
}


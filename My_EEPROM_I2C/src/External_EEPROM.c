#include "External_EEPROM.h"
#include "i2c.h"

void EEPROM_init(){
	TWI_init();
}
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data){

	TWI_start();

	if (TWI_getStatus() != TW_START){
			return ERROR;
	}//                                       A10,A9,A8, (R/W = 0)"Write"
	//                             1010 or (SlaveAdress & 0111 0000 0000) >> 7)
	TWI_write((uint8)(0xA0 | ( (u16addr & 0x0700)>>7) ));

	if (TWI_getStatus() != TW_MT_SLA_W_ACK){
		return ERROR;
	}
	TWI_write((uint8)(u16addr)); // Send the required Memory Location

	if(TWI_getStatus() != TW_MT_DATA_ACK){
		return ERROR;
	}
	TWI_write(u8data);// write byte to eeprom

	if (TWI_getStatus() != TW_MT_DATA_ACK){
		return ERROR;
	}
	TWI_stop();
	return SUCCESS;
}
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data){
	TWI_start();
	if (TWI_getStatus() != TW_START){
		return ERROR;
	}
	TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));

	if (TWI_getStatus() != TW_MT_SLA_W_ACK){
		return ERROR;
	}

	TWI_write((uint8)(u16addr)); // Memory Location.
	if (TWI_getStatus() != TW_MT_DATA_ACK){
		return ERROR;
	}

	//////Send Repeated Start Bit//////
	TWI_start(); // repeated start
	if(TWI_getStatus() != TW_REP_START){
		return ERROR;
	}

	//                                          Memory Location + Read
	TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
	if(TWI_getStatus() != TW_MT_SLA_R_ACK){
		return ERROR;
	}

	*u8data = TWI_readWithNACK();
	if(TWI_getStatus() != TW_MR_DATA_NACK){
		return ERROR;
	}
	TWI_stop();
	return SUCCESS;

}

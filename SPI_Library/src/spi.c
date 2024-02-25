#include "spi.h"

void SPI_initMaster(){
	setBit(DDRB,PB4);  //SS
	setBit(DDRB,PB5);  //MOSI
	clearBit(DDRB,PB6);  //MISO
	setBit(DDRB,PB7);  //SCK "clock"

	SPCR = (1<<SPE) | (1<<MSTR); //Enable SPI and Master + choose_spi clock
}
void SPI_initSlave(){
	clearBit(DDRB,PB4);  //SS
	clearBit(DDRB,PB5);  //MOSI
	setBit(DDRB,PB6);  //MISO
	clearBit(DDRB,PB7);  //SCK "clock"

	SPCR = (1<<SPE); //Enable SPI + choose_spi clock
}
void SPI_sendByte(uint8 data){
	SPDR = data;
	while(bitIsClear(SPSR,SPIF)){} // Wait for transfer complete flag
}
uint8 SPI_recieveByte(){
	while(bitIsClear(SPSR,SPIF)){} // Wait for Data Receive complete flag
	return SPDR; // return data
}
void SPI_sendString(uint8 * Str){
	uint8 i = 0;
	while(Str[i] !='\0'){
		SPI_recieveByte(Str[i]);
		i++;
	}
}
void SPI_recieveString(uint8 * Str){
	uint8 i = 0;
	Str[i] = SPI_recieveByte();
	while(Str[i] != '#'){
		i++;
		Str[i] = SPI_recieveByte();
	}
	Str[i] = '\0';
}

#include "adc.h"

void ADC_init(void){
	ADMUX = 0; // We need all pins to be equal to 0
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0); //I am working on 1M Hz then use prescale = 8
	// 125 Khz is the valid range of ADC
}
uint16 ADC_readChannel(uint8 channel_num){
	channel_num &= 0x07; // Because I only need 3bits to which channel I want
	ADMUX &= 0xE0; // To clear the first 5 bits in the ADMUX
	ADMUX |= channel_num; // Select the wanted channel.
	setBit(ADCSRA,ADSC); // Start Conversion
	while(bitIsClear(ADCSRA,ADIF)); // While flag has not triggered wait
	setBit(ADCSRA,ADIF); // Clear the flag by setting it. As written in the datasheet.
	return ADC;
}

#include <avr/io.h>
#define setBit(REG,Bit) (REG |= (1<<Bit))
#define clearBit(REG,Bit) (REG &= ~(1<<Bit))
#define clearBit(REG,Bit) (REG &= ~(1<<Bit))
#define bitIsSet(REG,Bit) (REG &(1<<Bit))
#define bitIsClear(REG,Bit) (~(REG &(1<<Bit)))


int main(void){
	clearBit(DDRA,PA0);
	clearBit(DDRA,PA1);
	clearBit(DDRA,PA2);
	// IN ports
	setBit(DDRC,PC0);
	setBit(DDRC,PC1);
	clearBit(PORTC,PC0);
	clearBit(PORTC,PC1);
	for(;;){
		if(bitIsSet(PINA,PA0)){
			setBit(PORTC,PC1);
			clearBit(PORTC,PC0);
		}
		else if(bitIsSet(PINA,PA1)){
			setBit(PORTC,PC0);
			clearBit(PORTC,PC1);
		}
		else if(bitIsSet(PINA,PA2)){
			clearBit(PORTC,PC1);
			clearBit(PORTC,PC0);
		}
	}
}

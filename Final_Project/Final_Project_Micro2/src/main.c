#include "uart.h"
#include "External_EEPROM.h"
#define write "write"
#define read "read"
#define correct 1
#define wrong 0


void PassCheckResponse(bool condition){
	if (condition == wrong){
		setBit(PORTD,PD7); //buzzer
		setBit(PORTD,PD2); // Motor
		clearBit(PORTD,PD5); // Motor
		for (int i = 0 ; i < 3 ; i++){
			toggleBit(PORTD,PD4); // red led
			_delay_ms(500);
		}
		clearBit(PORTD,PD7); //Buzzer
		clearBit(PORTD,PD4); //red led
		clearBit(PORTD,PD2); //Motor
	}
	else if(condition == correct){
		clearBit(PORTD,PD2); // Motor
		setBit(PORTD,PD5); // Motor
		for (int i = 0 ; i < 3 ; i++){
			toggleBit(PORTD,PD3); // red led
			_delay_ms(500);
		}
		clearBit(PORTD,PD3); //red led
		clearBit(PORTD,PD5); //Motor
	}
}

uint8 passCheck(uint8 * pass_arr){
	uint8 pin1,pin2,pin3,pin4;
	EEPROM_readByte(0x0311, &pin1);
	_delay_ms(10);
	EEPROM_readByte(0x0312, &pin2);
	_delay_ms(10);
	EEPROM_readByte(0x0313, &pin3);
	_delay_ms(10);
	EEPROM_readByte(0x0314, &pin4);
	_delay_ms(10);

	if(pass_arr[0] != pin1){return 0;}
	else if(pass_arr[1] != pin2){return 0;}
	else if(pass_arr[2] != pin3){return 0;}
	else if(pass_arr[3] != pin4){return 0;}
	return 1;
}
int main(void){
	//init
	setBit(DDRD,PD7);
	setBit(DDRD,PD5);
	setBit(DDRD,PD4);
	setBit(DDRD,PD3);
	setBit(DDRD,PD2);
	clearBit(PORTD,PD7);
	clearBit(PORTD,PD5);
	clearBit(PORTD,PD4);
	clearBit(PORTD,PD3);
	clearBit(PORTD,PD2);
	// EEPROM
	uint8 password[4] , choice = 0 ,count = 0;

	EEPROM_init();
	EEPROM_writeByte(0x0311, '0');
	_delay_ms(10);
	EEPROM_writeByte(0x0312, '0');
	_delay_ms(10);
	EEPROM_writeByte(0x0313, '0');
	_delay_ms(10);
	EEPROM_writeByte(0x0314, '0');
	_delay_ms(10);
	//UART
	UART_init();

	while(1){
		choice = UART_recieveByte();
		//Choice 1
		while (choice == 0x01){
			password[0] = UART_recieveByte();
			_delay_ms(10);
			password[1] = UART_recieveByte();
			_delay_ms(10);
			password[2] = UART_recieveByte();
			_delay_ms(10);
			password[3] = UART_recieveByte();
			_delay_ms(10);

			if (!passCheck(password)){
				UART_sendByte(0);
				count++;
				if (count == 3){
					PassCheckResponse(wrong);
					count = 0;
					choice = 0;
				}
			}else {
				UART_sendByte(1);
				count=0;
				choice = 0;
				PassCheckResponse(correct);
			}
		}
		//Choice 2
		while (choice == 0x02){
			EEPROM_writeByte(0x0311, UART_recieveByte());
			_delay_ms(10);
			EEPROM_writeByte(0x0312, UART_recieveByte());
			_delay_ms(10);
			EEPROM_writeByte(0x0313, UART_recieveByte());
			_delay_ms(10);
			EEPROM_writeByte(0x0314, UART_recieveByte());
			_delay_ms(10);
			UART_sendByte(1);
			choice = 0;
		}
	}
}

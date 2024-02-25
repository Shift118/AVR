#include "lcd.h"

void LCD_init(void){
	LCD_CTRL_PORT_DIR |= (1<<RS) | (1<<RW) | (1<<E);
	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |= 0Xf0;
		#else
			LCD_DATA_PORT_DIR |= 0X0f; // IF LOWER PINS ARE USED
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE);
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
	#elif (DATA_BITS_MODE == 8)
			LCD_DATA_PORT_DIR |= 0xff;
			LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	#endif
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}
void LCD_sendCommand(uint8 command){
	clearBit(LCD_CTRL_PORT,RS);
	clearBit(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	setBit(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | (command & 0xf0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xf0) | ((command & 0xf0) >> 4);
		#endif
		_delay_ms(1);
		clearBit(LCD_CTRL_PORT,E);
		_delay_ms(1);
		setBit(LCD_CTRL_PORT,E);
		_delay_ms(1);
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | ((command&0x0f)<< 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xf0) | (command & 0x0f);
		#endif
		_delay_ms(1);
		clearBit(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = command;
		_delay_ms(1);
		clearBit(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#endif
}
void LCD_displayCharacter(uint8 data){
	setBit(LCD_CTRL_PORT,RS);
	clearBit(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	setBit(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | (data&0xf0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xf0) | ((data&0xf0)>>4);
		#endif
			_delay_ms(1);
			clearBit(LCD_CTRL_PORT,E);
			_delay_ms(1);
			setBit(LCD_CTRL_PORT,E);
			_delay_ms(1);
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | ((data&0x0f)<<4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xf0) | (data&0x0f);
		#endif
		_delay_ms(1);
		clearBit(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = data;
		_delay_ms(1);
		clearBit(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#endif

}
void LCD_displayString(const char *Str){
	uint8 i = 0;
	while(Str[i] != '\0'){
		LCD_displayCharacter(Str[i]);
		i++;
	}
}
void LCD_goToRowColumn(uint8 row,uint8 col){
	uint8 Address;
	switch(row){
	case 0: Address = col; break;
	case 1: Address = col+0x40; break;
	case 2: Address = col+0x10; break;
	case 3: Address = col+0x50; break;
	}
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str){
	LCD_goToRowColumn(row, col);
	LCD_displayString(Str);
}
void LCD_intgerToString(int data){
	char str[16];
	itoa(data,str,10); // 10 is for decimal, if 2 the binary
	LCD_displayString(str);
}
void LCD_integerToStringRowCol(int row, int col,int data){
	LCD_goToRowColumn(row, col);
	LCD_intgerToString(data);
}
void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_COMMAND);
}





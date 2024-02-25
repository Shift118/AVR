#include "keypad.h"
#include "lcd.h"
int main(void){
	LCD_init();
	LCD_displayCharacter('c');
	LCD_integerToStringRowCol(1, 5, 4800);
	for(;;){

	}
}

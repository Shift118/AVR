#include "lcd.h"
#include "keypad.h"

int main(int argc, char **argv) {
	LCD_init();
	uint8 key;


	for (;;){
		key = KeyPad_getPressedKey();
		if(key){
			LCD_displayCharacter(key);
		}
	}
}

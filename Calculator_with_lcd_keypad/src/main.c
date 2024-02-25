#include "keypad.h"
#include "lcd.h"
#include <string.h>

uint8 isOperator(char c){
	return c == '+' || c == '-' || c == '*' || c == '%';
}

int main(void){
	LCD_init();
	uint8 stay = 0;
	char e1[16] = "" , e2[16] = "",empty[16] = "                ";
	int num1=1,num2=5;

	for(;;){
		char key = KeyPad_getPressedKey();
		if (key){
			char operatorUsed = key;
			if(key == 'C'){
				// Clear Input 1 and Input 2
				e1[0] = '\0'; e2[0] ='\0';stay = 0;
				num1 = 0; num2 = 0;
				LCD_clearScreen();
				LCD_displayString("Cleared :) ");
				_delay_ms(1000);
				LCD_clearScreen();
			}else if(key == '='){
					num1 = atoi(e1);
					num2 = atoi(e2);
					LCD_clearScreen();
					switch(operatorUsed){
					case '+': LCD_integerToStringRowCol(0, 0, num1+num2); break;
					case '-': LCD_integerToStringRowCol(0, 0, num1-num2); break;
					case '*': LCD_integerToStringRowCol(0, 0, num1*num2); break;
					case '%': LCD_integerToStringRowCol(0, 0, num1/num2); break;
					}
				}
			if (isOperator(key)) LCD_clearScreen();
			while(isOperator(key) || stay){
				stay = 1;
				key = KeyPad_getPressedKey();
				if(key == '='){
					num1 = atoi(e1);
					num2 = atoi(e2);
					LCD_displayStringRowColumn(0, 0, empty);
					LCD_displayStringRowColumn(0, 0, "Equals: ");
					switch(operatorUsed){
					case '+': LCD_integerToStringRowCol(0, 8, num1+num2); key = 'C';break;
					case '-': LCD_integerToStringRowCol(0, 8, num1-num2); key = 'C'; break;
					case '*': LCD_integerToStringRowCol(0, 8, num1*num2); key = 'C'; break;
					case '%': LCD_integerToStringRowCol(0, 8, num1/num2); key = 'C'; break;
					}
				}
				if(key == 'C'){
					// Clear Input 1 and Input 2
					e1[0] = '\0'; e2[0] ='\0';stay = 0;
					num1 = 0; num2 = 0;
					_delay_ms(1000);
					LCD_clearScreen();
					LCD_displayString("Cleared :) ");
					_delay_ms(500);
					LCD_clearScreen();
				}else{
					if(!isOperator(key) && key != 'C' && key != '='){
						LCD_displayStringRowColumn(0, 0, empty);
						strncat(e2,&key,1);
						LCD_displayStringRowColumn(0, 0, e2);
					}
				}
			}
			LCD_displayStringRowColumn(0, 0, empty);
			if (key != 'C' && !isOperator(key)) strncat(e1,&key,1) ;
			LCD_displayStringRowColumn(0, 0, e1);
		}
	}
}

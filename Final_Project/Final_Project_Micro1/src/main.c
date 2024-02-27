#include "uart.h"
#include "lcd.h"
#include "keypad.h"

void lcdConfigure(){
	LCD_clearScreen();
	LCD_displayString("1.Enter Password");
	LCD_displayStringRowColumn(1, 0,"2.New Password");

}
void keypad_Passcode(uint8 * password){
	LCD_clearScreen();
	LCD_displayString("Enter Password:");
	LCD_goToRowColumn(1, 6);
	for(uint8 i = 0; i<4; i++){
		password[i] = KeyPad_getPressedKey();
		LCD_displayCharacter(password[i]);
		_delay_ms(500);
	}
}

int main(void){
	//init
	uint8 choice = 0 , count = 0 , password_arr[4];
	//LCD
	LCD_init();
	//Keypad
	char key = 0;
	//UART
	UART_init();
	while(1){
		if (!key){
			lcdConfigure();
		}
		key = KeyPad_getPressedKey();
		if (key){
			choice = key;
			while (choice == '1'){
				UART_sendByte(0x01); // Entering Passcode
				keypad_Passcode(password_arr);
				LCD_clearScreen();
				UART_sendByte(password_arr[0]);
				_delay_ms(10);
				UART_sendByte(password_arr[1]);
				_delay_ms(10);
				UART_sendByte(password_arr[2]);
				_delay_ms(10);
				UART_sendByte(password_arr[3]);
				_delay_ms(10);
				if(UART_recieveByte() == 0){
					count++;
					LCD_clearScreen();
					LCD_displayString("Incorrect");
					_delay_ms(1000);
					if (count == 3){
						LCD_clearScreen();
						LCD_displayString("Close down");
						LCD_clearScreen();
						choice = 0;
						count = 0;
						key = 0;
					}
				}else{
					count =0;
					choice = 0;
					key = 0;
					LCD_clearScreen();
					LCD_displayString("Correct Passcode");
					_delay_ms(1000);
					LCD_clearScreen();
				}
			}
			while(choice == '2'){
				UART_sendByte(0x02); // Entering Passcode
				keypad_Passcode(password_arr);
				UART_sendByte(password_arr[0]);
				_delay_ms(10);
				UART_sendByte(password_arr[1]);
				_delay_ms(10);
				UART_sendByte(password_arr[2]);
				_delay_ms(10);
				UART_sendByte(password_arr[3]);
				_delay_ms(10);
				if(UART_recieveByte()){
					choice = 0;
					key = 0;
					LCD_clearScreen();
					LCD_displayString("Password Created");
					LCD_clearScreen();
				}
			}
		}
	}
	return 0;
}

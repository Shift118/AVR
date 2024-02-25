#ifndef UART_H_
#define UART_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#define USART_BAUDRATE 9600

void UART_init();
void UART_sendByte(uint8 data);
uint8 UART_recieveByte();
void UART_sendString(uint8 *Str);
void UART_recieveString(uint8 * Str);
#endif

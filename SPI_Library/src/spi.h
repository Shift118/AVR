#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

void SPI_initMaster();
void SPI_initSlave();
void SPI_sendByte(uint8 data);
uint8 SPI_recieveByte();
void SPI_sendString(uint8 * Str);
void SPI_recieveString(uint8 * Str);

#endif


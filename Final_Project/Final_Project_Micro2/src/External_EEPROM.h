#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define ERROR 0
#define SUCCESS 1

void EEPROM_init();
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif

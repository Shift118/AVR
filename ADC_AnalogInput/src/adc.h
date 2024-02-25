#ifndef _ADC_H_
#define _ADC_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

void ADC_init(void);
uint16 ADC_readChannel(uint8 channel_num);
#endif











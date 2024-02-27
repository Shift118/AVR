#ifndef COMMON_MACROS
#define COMMON_MACROS

#define setBit(REG,BIT) (REG |= (1<<BIT))
#define clearBit(REG,BIT) (REG &= ~(1<<BIT))
#define toggleBit(REG,BIT) (REG ^= (1<<BIT))

#define ROR(REG,num) (REG =  (REG>>num) | (REG << (8-num)))
#define ROL(REG,num) (REG =  (REG<<num) | (REG >> (8-num)))

#define bitIsSet(REG,BIT) (REG & (1<<BIT))
#define bitIsClear(REG,BIT) (!(REG & (1<<BIT)))

#endif

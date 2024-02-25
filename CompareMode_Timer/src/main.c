#include <avr/io.h>
#include <avr/interrupt.h>
int count = 0;
ISR(TIMER0_COMP_vect){
	count++;
}
int main(int argc, char **argv) {
	DDRC |= (1<<PC0);
	PORTC &= ~(1<<PC0);
	////////////////////////////
	SREG |= (1<<7);
	TCCR0 |= (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
	TIMSK |= (1<<OCIE0);
	TCNT0 = 0;
	OCR0 = 243;
	for(;;){
		if(count == 4){
			PORTC ^= (1<<PC0);
			count = 0;
		}
	}
}

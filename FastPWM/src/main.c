#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Non-Inverted: Wave begins with High and when Met with compare it toggle and when Met with overflow it toggles
// Duty Cycle = Ton / (Ton+Toff) = OCR0 / 256
// If Duty Cycle 70% is needed then OCR0 = 70% * 256.
//                                                                      DC  *  256
//Inverted: Wave begins with Low and when Met with compare it toggle and when Met with overflow it toggles
// Duty Cycle in inverted = (256-OCR0) / 256
// Since it is easier to use Non-Inverted we use it.

//FreqPWM = fclk / (N*256) , N is the prescale Factor (1,8,64,256,1024).


void Timer_PWM_init (unsigned char setDutyCycle){
	DDRB |= (1<<PB3); // OC0 as output pin
	TCNT0 = 0;
	OCR0 = setDutyCycle;
	TCCR0 |=  (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
}

int main(int argc, char **argv) {
	for(;;){
		Timer_PWM_init(255); // 100% duty Cycle
		_delay_ms(5000);
		Timer_PWM_init(192); // 75% duty Cycle
		_delay_ms(5000);
		Timer_PWM_init(128); // 50% duty Cycle
		_delay_ms(5000);
		Timer_PWM_init(64); // 25% duty Cycle
		_delay_ms(5000);
	}
}

#include <avr/io.h>
#include <util/delay.h>

void motor_left(){
	PORTB |= (1<<1);
	PORTB &= ~(1<<0);
}
void motor_right(){
	PORTB |= (1<<0);
	PORTB &= ~(1<<1);
}
void motor_stop(){
	PORTB &= ~(1<<1);
	PORTB &= ~(1<<0);
}

void init_adc(){
	
	ADMUX |= (1<<REFS0);
	ADMUX |= (1<<MUX1);
	ADCSRA |= (1<<ADEN)|(1<<0)|(1<<1)|(1<<2);
	 
	
}
void init_pwm(unsigned char p){
	
	TCNT0 =0;
	OCR0A =p;
	TCCR0B |= (1<<CS02);
	TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
	
}


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "motor.c"
#include "uart_printf.h"



int main(void){
	init_usart_printf(115200);
	init_adc();
	init_pwm(200);
	UCSR0B |= (1<<RXEN0);
	unsigned char commn;
	int16_t error,ref = 512;
	int64_t feedback;
	uint8_t gain=1;
	
	while(1){
	
	ADMUX &= ~(1<<MUX1);
	ADCSRA |= (1<<ADSC); 

	while(!(ADCSRA & (1<<ADIF))){
		;
	}
	
	
	
	if(feedback>0){
		motor_right();
	}else if(feedback<0){
		motor_left();
	}else {
		motor_stop();
	}
	
	
	error=ref-ADC;
	feedback=gain*error;
	
	if(abs(feedback)>255){
		OCR0A=255;
	}else{
		OCR0A=abs(feedback);
	}
	if((UCSR0A & (1<<RXC0))) 
	   commn=UDR0;
	   if(commn == 'd'){
	   	ref=300;
	   }else if(commn == 'f'){
	   	ref=700;
	   }
	   
	   printf("ref=%d,error=%d,gain=%d\n", (int)ref,(int)error,(int)gain);
	}
	
	

}

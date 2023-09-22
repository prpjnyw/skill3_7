//printf using UART for 16.0 XTAL
#include <avr/io.h>
#include <stdio.h>
#include <math.h>


int uart_putchar(char c, FILE *stream);

FILE usart_out =
   FDEV_SETUP_STREAM(uart_putchar, NULL,
   _FDEV_SETUP_WRITE);

int uart_putchar(char c, FILE *stream){
   if(c=='\n'){
       uart_putchar('\r', stream);
   }
   // Wait for empty transmit buffer
#if defined (__AVR_ATmega32__)||defined (__AVR_ATmega32A__)
   while(!(UCSRA & (1<<UDRE)) );	
   UDR=c;
   return 0;
#else
   while(!(UCSR0A & (1<<UDRE0)) );
   UDR0=c;
   return 0;
#endif
}

void init_usart_printf(unsigned long baud){
#if defined (__AVR_ATmega32__)||defined (__AVR_ATmega32A__)
	UBRRH=0;
	UBRRL = round((F_CPU/16.0/baud)-1);
	UCSRB = (1<<TXEN);
	//Set frame to 8data, 2stop bit.
	UCSRC = (1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
#else
   //Set baud rate, baud=Fosc/(16*(UBRR+1))
	//since Arduino use 16MHz that has error the use rounding
	UBRR0 = round((F_CPU/16.0/baud)-1);
	//UBRR0=round(f);
   //UBRR0=(uint16_t)(F_CPU/16/baud)-1;
   //UBRR0 = 8;	//baud = 115200 bps
   UCSR0B = (1<<TXEN0); 
   //Set frame to 8data, 2stop bit.
   UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
#endif	
   stdout = &usart_out;
}

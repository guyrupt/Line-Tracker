#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
uint16_t ADCRead(const int);
void USART_putstring(char* StringPtr);
int main(void){
	CLKPR=0b10000000;
	CLKPR=0b00000000;
	DDRC = 0;
	DDRD=0xFF; // PORTD as output
	DDRB=0xFF;
	TCCR0A=0b10100011; // phase correct PWM
	TCCR0B=0b00000010; // timer
	TCCR2A=0b10100011; // phase correct PWM
	TCCR2B=0b00000010; // timer
	ADCSRA |= (1<<ADEN);
	unsigned int BaudR = 9600;
	unsigned int ubrr = (F_CPU / (BaudR*16UL))-1;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<TXEN0);
	while(1){
		float AAA = 0;
		float BBB = 0;
		float CCC=0;
		AAA = (float)ADCRead(1);
		BBB = (float)ADCRead(3);
		CCC = (float)ADCRead(2);
		_delay_ms(1);
		
		if(CCC>500&&AAA<500&&BBB<500)
		{
			OCR0B=238; 
			
			OCR2B=255;
			
		}
		else if(CCC>500&&AAA>500&&BBB>500)
		{
			OCR0B=238;
			
			OCR2B=255; 
			
		}
		else if(AAA>500)
		{
			
			OCR0B=238; 
			
			OCR2B=55; 
			
		}
		else if(BBB>500)
		{
			
			OCR0B=60; 

			OCR2B=255; 
			
		}
	}
}
uint16_t ADCRead(const int channel) {
	ADMUX = 0b01000000;
	ADMUX |= channel;
	ADCSRA |= (1<<ADSC) | (1<<ADIF);
	while ( (ADCSRA & (1<<ADIF)) == 0);
	ADCSRA &= ~(1<<ADSC);
	return ADC;
}



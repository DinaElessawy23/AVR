/*
 * Mini_Project2.c
 *
 *  Created on: Sep 15, 2021
 *      Author: Dina Elessawy
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/delay.h"

unsigned char hr = 0;
unsigned char min = 0;
unsigned char sec = 0;

ISR(TIMER1_COMPA_vect)
{
	sec++;
	if(sec==60){
		sec=0;
		min++;
	}
	if(min==60){
		sec=0;
		min=0;
		hr++;
	}
}


ISR(INT0_vect)
{
	//Stop Watch time should be reset.
	sec=0;
	min=0;
	hr=0;
}
ISR(INT1_vect)
{
	// Stop Watch time should be paused.
	TCCR1A=0;
	TCCR1B=0;
	TIMSK &=~ (1<<OCIE1A);


}
ISR(INT2_vect)
{
	//Stop Watch time should be resumed.
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12) | (1<<CS10)| (1<<CS11);
	TIMSK |= (1<<OCIE1A);

}
void Timer1_CTC_Init(void)
{
	TCNT1 = 0;		/* Set timer1 initial count to zero */

	OCR1A = 15624;             //fOCn=fclk/	2 * N (1 + OCRn) ,fOCn=0.5HZ,N=64,fclk=1MHZ

	SREG  |= (1<<7);           // Enable interrupts by setting I-bit
	TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=1
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A = (1<<FOC1A)|(1<<FOC1B);

	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/64 CS10=1 CS11=1 CS12=0
	 */
	TCCR1B = (1<<WGM12) | (1<<CS10)| (1<<CS11);
}

void INT0_Init(void)
{
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	PORTD |= (1<<PD2);                  // Enable the internal pull up resistor at PD2 pin
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC01);                // Trigger INT0 with the falling edge
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}


void INT1_Init(void)
{
		DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
		GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
		// Trigger INT1 with the rising edge
		MCUCR |= (1<<ISC10)|(1<<ISC11);
		SREG  |= (1<<7);       // Enable interrupts by setting I-bit

}
void INT2_Init(void)
{
	DDRB   &= (~(1<<PB2));   // Configure INT2/PB2 as input pin
	PORTB |= (1<<PB2);       // Enable the internal pull up resistor at PB2 pin
	GICR   |= (1<<INT2);	 // Enable external interrupt pin INT2
	MCUCSR &= ~(1<<ISC2);     // Trigger INT2 with the falling edge
	SREG   |= (1<<7);        // Enable interrupts by setting I-bit
}
int main(void)
{
	//6. Connect 7447 decoder 4-pins to the first 4-pins in PORTC.
	DDRC  = 0x0f; 			// Configure the first four pins in PORTC as output pins.
	PORTC = 0x00; 		    // 7-segment display zero at the beginning.
   	//7. Use first 6-pins in PORTA as the enable/disable pins for the six 7-segments.
//	DDRA |=0x3F;
//    PORTA &=0xC0;
	DDRA  =0xff;
	PORTA =0xff;

	INT0_Init();              // Enable external INT0
	INT1_Init();             // Enable external INT1
	INT2_Init(); 			// Enable external INT2
    Timer1_CTC_Init	();


    while(1)
    {

       	 PORTA=(1<<5);
       	 PORTC=sec%10;
         _delay_ms(7);
       	 PORTA=(1<<4);
       	 PORTC=sec/10;
         _delay_ms(7);
       	 PORTA=(1<<3);
       	 PORTC=min%10;
       	  _delay_ms(7);
         PORTA=(1<<2);
       	 PORTC=min/10;
       	_delay_ms(7);
		 PORTA=(1<<1);
		PORTC = hr % 10;
		_delay_ms(7);
		PORTA= (1 <<0);
		PORTC = hr / 10;
		_delay_ms(7);


    }
}














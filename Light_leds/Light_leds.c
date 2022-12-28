/*
 * Light_leds.c
 *
 *  Created on: Dec 8, 2022
 *      Author: DINA ELESSAWY
 */

#include "avr/io.h"
#include "util/delay.h"

void main(void)
{
	DDRA=0b11111111;
    long mask=0b10000000;
	while(1)
	{
		for(int i=0;i<8;i++)
		   {
			   PORTA|=(1<<i);
			   	_delay_ms(100);//to wait 1 second
			   PORTA&=(~(1<<i));
			   	_delay_ms(100);//to wait 1 second
		   }
		   for(int i=8;i>0;i--)
		      {
		   	   PORTA|=(1<<i);
			   	_delay_ms(100);//to wait 1 second
		   	   PORTA&=(~(1<<i));
			   	_delay_ms(100);//to wait 1 second
		      }

		for(int i=0;i<8;i++)
		   {
			   PORTA|=(1<<i);
			   PORTA|=(mask>>i);

			   	_delay_ms(100);//to wait 1 second
			   PORTA&=(~(1<<i));
			   PORTA&=~(mask>>i);

			   	_delay_ms(100);//to wait 1 second
		   }

		for(int i=0;i<8;i++)
				   {
					   PORTA|=(1<<i);
					   	_delay_ms(100);//to wait 1 second
					  PORTA&=(~(1<<i));

					   PORTA|=(mask>>i);

					   	_delay_ms(100);//to wait 1 second
					   PORTA&=~(mask>>i);

					   	_delay_ms(100);//to wait 1 second
				   }

	}
}

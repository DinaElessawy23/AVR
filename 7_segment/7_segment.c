/*
 * 7_segment.c
 *
 *  Created on: Dec 8, 2022
 *      Author: DINA ELESSAWY
 */

#include "avr/io.h"
#include "util/delay.h"

int numbers[10] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
void main(void)
{
	DDRA=0b11111111;
	DDRD=0b11111111;

	while(1)
	{

		for(int i=0;i<10;i++)
		{
		PORTD=numbers[i];
		for(int j=0;j<10;j++)
		{
			PORTA=numbers[j];
        	_delay_ms(1000);
		}
		}

	}
}

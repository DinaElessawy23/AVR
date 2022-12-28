/*
 * main.c
 *
 *  Created on: Dec 17, 2022
 *      Author: DINA ELESSAWY
 */
#include  "std_types.h"
#include "dio_int.h"
#include "util/delay.h"

void main(void)
{
	DIO_u8SetPinDir(PORT_A , PIN_1 , OUTPUT);
	while(1)
	{
		DIO_u8SetPinVal(PORT_A , PIN_1 , HIGH);
		_delay_ms(1000);
		DIO_u8SetPinVal(PORT_A , PIN_1 , LOW);
		_delay_ms(1000);

	}
}

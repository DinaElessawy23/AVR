/*
 * main.c
 *
 *  Created on: Dec 18, 2022
 *      Author: DINA ELESSAWY
 */

#include  "std_types.h"
#include  "dio_int.h"
#include  "util/delay.h"
#include  "bit_math.h"
#include  "DIO_REG.h"
void main(void) {
	DIO_u8SetPinDir(PORT_A, PIN_0, OUTPUT); //RED_LED
	DIO_u8SetPinDir(PORT_A, PIN_1, OUTPUT); //GREEN_LED
	DIO_u8SetPinDir(PORT_A, PIN_4, OUTPUT); //BUZZER
	DIO_u8SetPinDir(PORT_A, PIN_2, INPUT); //SWITCH_ENTER
	DIO_u8SetPinVal(PORT_A, PIN_2, PUE);
	//SET_BIT(PORTA_REG,PIN_2);

	DIO_u8SetPinDir(PORT_A, PIN_3, INPUT); //SWWITCH_CLOSE
	DIO_u8SetPinVal(PORT_A, PIN_3, PUE);
	DIO_u8SetPortDir(PORT_C, 0xFF); //7_SEGMENT
	DIO_u8SetPortDir(PORT_D, 0x00); //DIP_SWITCH
	DIO_u8SetPortVal(PORT_D, 0xFF); //PULL UP

	uint8 password = 0b11001010; //1356//reverse as it pull up
	uint8 PORTD_VAL;
	uint8 Flag = 0;
	 int count = 0;
	int numbers[4] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111 };
	DIO_u8SetPinVal(PORT_A, PIN_0, HIGH); //RED_LED OPEN

	while (1) {
		DIO_u8SetPortVal(PORT_C, numbers[0]); //write 0 to 7-segment
		if (!(PINA_REG >> PIN_2 & 1)) {
			_delay_ms(25); //debouncing
			if (!(PINA_REG >> PIN_2 & 1)) { //DIO_u8SetPinVal(PORT_A,PIN_1,HIGH);//GREEN_LED OPEN

				DIO_u8GetPortVal(PORT_D, &PORTD_VAL);
				if (PORTD_VAL == password) {
					DIO_u8SetPinVal(PORT_A, PIN_0, LOW); //RED_LED OFF
					DIO_u8SetPinVal(PORT_A, PIN_1, HIGH); //GREEN_LED OPEN
					DIO_u8SetPortVal(PORT_C, 0b00111111); //write 0 to 7-segment*/
				} else {
					++count;
				     DIO_u8SetPinVal(PORT_A, PIN_4, HIGH); //open Buzzer
				     _delay_ms(500);
				     DIO_u8SetPinVal(PORT_A, PIN_4, LOW); //close Buzzer
				     DIO_u8SetPortVal(PORT_C, numbers[count]); //write i to 7-segment
							while(count<4)
							{//++count;
					if (!(GET_BIT(PINA_REG, PIN_2))) {
						_delay_ms(25); //debouncing
						if (!(GET_BIT(PINA_REG, PIN_2))) {


								DIO_u8GetPortVal(PORT_D, &PORTD_VAL);

								if (PORTD_VAL == password) {
									Flag=1;
									DIO_u8SetPinVal(PORT_A, PIN_0, LOW); //RED_LED OFF
									DIO_u8SetPinVal(PORT_A, PIN_1, HIGH); //GREEN_LED OPEN
									DIO_u8SetPortVal(PORT_C, 0b00111111); //write 0 to 7-segment
									break;
								}
								else {
													++count;
												     DIO_u8SetPinVal(PORT_A, PIN_4, HIGH); //open Buzzer
												     _delay_ms(500);
												     DIO_u8SetPinVal(PORT_A, PIN_4, LOW); //close Buzzer
												     DIO_u8SetPortVal(PORT_C, numbers[count]); //write i to 7-segment
								}

						}
					}
					}
							if(Flag==0)
							{
								count=0;
								DIO_u8SetPinVal(PORT_A, PIN_4, HIGH); //open Buzzer
								DIO_u8SetPortVal(PORT_C, 0b01111001); //write E to 7-segment
							}

				}
			}
		}
		if (!(GET_BIT(PINA_REG, PIN_3))) {
			_delay_ms(25); //debouncing
			if (!(GET_BIT(PINA_REG, PIN_3))) {
				DIO_u8SetPinVal(PORT_A, PIN_0, HIGH); //RED_LED OPEN
				DIO_u8SetPortVal(PORT_C, numbers[0]); //write 0 to 7-segment
				DIO_u8SetPinVal(PORT_A, PIN_4, LOW); //close Buzzer
				DIO_u8SetPinVal(PORT_A, PIN_1, LOW); //GREEN_LED OPEN



			}
		}

	}
}

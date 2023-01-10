/*
 * buzzer.c
 *
 *  Created on: Nov 1, 2021
 *      Author: Dina Elessawy
 */

#include "buzzer.h"

#include "gpio.h"
#include <avr/io.h>
#include "util/delay.h"
#include "common_macros.h"

void Buzzer_init(void){
	 GPIO_setupPinDirection(Buzzer_Led_PORT_ID,  Buzzer_PIN_ID, PIN_OUTPUT);

	 GPIO_setupPinDirection(Buzzer_Led_PORT_ID,  Led_PIN_ID, PIN_OUTPUT);

	 GPIO_writePort( Buzzer_Led_PORT_ID,0xF3 );
}

void Buzzer_state(enum buzzer_State Alarm_state){
   if(Alarm_state==ON){
	TOGGLE_BIT(	PORTD,Buzzer_PIN_ID);

	TOGGLE_BIT( PORTD ,Led_PIN_ID);

	 _delay_ms(60000);
   }
   else if(Alarm_state==OFF){
 	CLEAR_BIT(PORTD , Buzzer_PIN_ID);
	CLEAR_BIT(PORTD , Led_PIN_ID );

   }




}










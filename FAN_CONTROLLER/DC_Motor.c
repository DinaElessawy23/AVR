 /******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: DC_Motor.c
 *
 * Created on: Oct 10, 2021
 *
 * Description: Source file for the ATmega16 PWM driver
 *
 * Author: Dina Elessawy
 *
 *******************************************************************************/


#include <avr/io.h>
#include "gpio.h"
#include "DC_Motor.h"
#include "common_macros.h"
#include "PWM.h"

void DcMotor_Init(void) {

	/* configure pin PB0 and PB1 as output pins */
	GPIO_setupPinDirection( DC_Motor_IN1_PORT_ID, DC_Motor_IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection( DC_Motor_IN2_PORT_ID, DC_Motor_IN2_PIN_ID,PIN_OUTPUT);
	//DDRB |= (1<<PB0);
	//DDRB |= (1<<PB1);
	//DDRC |= 0x03;
//	DDRB |= 0x0B;

	/* Motor is stop at the beginning */
	PORTB &= 0xFC;
}

void DcMotor_Rotate(enum DcMotor_State state, uint8 speed) {
	if (state == CW)
	{
		// Rotate the motor --> clock wise
		PORTB &= (~(1 << PB0));
		PORTB |= (1 << PB1);
	}
	else if (state == A_CW)
	{
		// Rotate the motor --> anti-clock wise
		PORTB &= (~(1 << PB1));
		PORTB |= (1 << PB0);

//			SET_BIT(DC_Motor_IN1_PORT_ID,DC_Motor_IN1_PIN_ID);
//			CLEAR_BIT(DC_Motor_IN2_PORT_ID,DC_Motor_IN2_PIN_ID);

	}
	else if (state == stop) {
		// Stop the motor
		PORTB &= (~(1 << PB0));
		PORTB &= (~(1 << PB1));

//			CLEAR_BIT(DC_Motor_IN1_PORT_ID,DC_Motor_IN1_PIN_ID);
//			CLEAR_BIT(DC_Motor_IN2_PORT_ID,DC_Motor_IN2_PIN_ID);
	}

	if (speed == 0) {
		PORTB &= (~(1 << PB0));
		PORTB &= (~(1 << PB1));

		// Stop the motor
//			CLEAR_BIT(DC_Motor_IN1_PORT_ID,DC_Motor_IN1_PIN_ID);
//			CLEAR_BIT(DC_Motor_IN2_PORT_ID,DC_Motor_IN2_PIN_ID);

	}

	 if (speed == 25) {
		Timer0_PWM_Init(64); //generate duty cycle 25%
	}
	 if (speed == 50) {
		Timer0_PWM_Init(128); //generate duty cycle 50% to get half motor speed
	}
	 if (speed == 75) {
		Timer0_PWM_Init(192); //generate duty cycle 75%
	}
	 if (speed == 100) {
		Timer0_PWM_Init(255); //generate duty cycle 100%

	}

}

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

void DcMotor_Init(void) {

	/* configure pin PC6 and PC7 as output pins */

	GPIO_setupPinDirection( DC_Motor_IN1_PORT_ID , DC_Motor_IN1_PIN_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection( DC_Motor_IN2_PORT_ID, DC_Motor_IN2_PIN_ID,PIN_OUTPUT);

	/* Motor is stop at the beginning */
	GPIO_writePin(DC_Motor_IN1_PORT_ID,DC_Motor_IN1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(DC_Motor_IN2_PORT_ID,DC_Motor_IN2_PIN_ID,LOGIC_LOW);
}

void DcMotor_Rotate(enum DcMotor_State state) {
	if (state == CW)
	{
		// Rotate the motor --> clock wise
		GPIO_writePin(DC_Motor_IN1_PORT_ID,DC_Motor_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_Motor_IN2_PORT_ID,DC_Motor_IN2_PIN_ID,LOGIC_HIGH);

	}
	else if (state == A_CW)
	{
		// Rotate the motor --> anti-clock wise
		GPIO_writePin(DC_Motor_IN1_PORT_ID,DC_Motor_IN1_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(DC_Motor_IN2_PORT_ID,DC_Motor_IN2_PIN_ID,LOGIC_LOW);


	}
	else if (state == stop) {
		// Stop the motor
		GPIO_writePin(DC_Motor_IN1_PORT_ID,DC_Motor_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_Motor_IN2_PORT_ID,DC_Motor_IN2_PIN_ID,LOGIC_LOW);

	}


}

 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.c
 *
 * Created on: Oct 11, 2021
 *
 * Description: Source file for the ATmega16 PWM driver
 *
 * Author: Dina Elessawy
 *
 *******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "PWM.h"
#include "std_types.h"

void Timer0_PWM_Init(uint8 duty_cycle)
{
	TCNT0 = 0; // Set Timer Initial Value to 0

	OCR0  = duty_cycle; // Set Compare Value
   // GPIO_setupPinDirection( OC0_PORT_ID ,  OC0_PIN_ID, PIN_OUTPUT); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

}

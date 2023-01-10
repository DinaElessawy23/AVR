/*
 * File Name: Ultrasonic.c
 * Description: source file for the Ultrasonic Sensor driver
 * Created on: Oct 13, 2021
 * Author: Dina Elessawy
 */


#include "Ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <avr/io.h> /* To use the SREG register */
#include "util/delay.h"

uint8  g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 Distance=0;


void Ultrasonic_init(void){
	/* Create configuration structure for ICU driver */
	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};

	/* Initialize the ICU driver */
	Icu_init(&Icu_Config);

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Set the Call back function pointer in the ICU driver */
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	 GPIO_setupPinDirection(Ultrasonic_TRIGGER_PORT_ID, Ultrasonic_TRIGGER_PIN_ID, PIN_OUTPUT);//Setup the direction for the trigger pin as output pin through the GPIO driver.

}
void Ultrasonic_Trigger(void)
{
	  GPIO_writePin( Ultrasonic_TRIGGER_PORT_ID,  Ultrasonic_TRIGGER_PIN_ID, LOGIC_HIGH);
	 _delay_us(10);
	  GPIO_writePin( Ultrasonic_TRIGGER_PORT_ID,  Ultrasonic_TRIGGER_PIN_ID, LOGIC_LOW);

}
uint16 Ultrasonic_readDistance(void)
{

	Ultrasonic_Trigger();
	while (g_timeHigh == 0) {
	}
	/* calculate the Distance */
	Distance = g_timeHigh / 58.8;

	return Distance;

}

void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			Icu_clearTimerValue();
			/* Detect falling edge */
			Icu_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = Icu_getInputCaptureValue();
			/* Detect rising edge */
			Icu_setEdgeDetectionType(RISING);
			Icu_DeInit(); /* Disable ICU Driver */
			g_edgeCount = 0;

		}

}

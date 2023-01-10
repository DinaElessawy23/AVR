/*
 * File Name: MC.c
 * Description: system to measure the distance using ultrasonic sensor
 * Created on: Oct 19, 2021
 * Author: Dina Elessawy
 */


#include "lcd.h"
#include "icu.h"
#include "Ultrasonic.h"

int main()
{
	uint16 Distance;
	/* Initialize the LCD driver */
	LCD_init();
	LCD_displayString("Distance =    cm");
	/* Initialize the Ultrasonic driver */
	Ultrasonic_init();
	LCD_moveCursor(0, 11);
	Distance = Ultrasonic_readDistance();
	LCD_intgerToString(Distance);

}

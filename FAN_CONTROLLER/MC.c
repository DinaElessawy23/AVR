/*
 ================================================================================================
 Name        : MC.c
 Author      : Dina Elessawy
 Description : Fan Controller system
 Date        : Created on: Oct 11, 2021
 ================================================================================================
 */


#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "common_macros.h"
#include "gpio.h"
#include "DC_Motor.h"
#include "std_types.h"
#include "PWM.h"


int main(void){
    uint8 temp;
	/* Create configuration structure for ICU driver */
	ADC_ConfigType ADC_Config = {INTERNAL,F_CPU_8};

	LCD_init(); /* initialize LCD driver */
	ADC_init(&ADC_Config); /* initialize ADC driver */

	DcMotor_Init();

	/* Display this string "Temp =   C" only once on LCD at the first row */
	LCD_moveCursor(1,0);
	LCD_displayString("Temp =    C");

    while(1)
    {

    	temp = LM35_getTemperature();

		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,7);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		if(temp>=100){
			    	LCD_moveCursor(0,0);
			    	LCD_displayString("Fan is ON");
			    	DcMotor_Rotate(CW,100);

			   }
		  else if(temp>=90){
			    	LCD_moveCursor(0,0);
			    	LCD_displayString("Fan is ON");
			    	state=CW;
			    	DcMotor_Rotate(state,75);

			   }
		  else if(temp>=60){
		 	    	LCD_moveCursor(0,0);
		 	    	LCD_displayString("Fan is ON");
		 	    	state=CW;
		 	    	DcMotor_Rotate(state,50);

		 	    }


	    else if(temp>=30){
	    	LCD_moveCursor(0,0);
	    	LCD_displayString("Fan is ON");
	    	LCD_moveCursor(0,9);
			LCD_displayCharacter(' ');


	    	state=CW;
	    	DcMotor_Rotate(state,25);
	    }
	    else if(temp<30){
	    	    	LCD_moveCursor(0,0);
	    	    	LCD_displayString("Fan is OFF");
	    	    	state=stop;
	    	    	DcMotor_Rotate(state,0);


	    	    }


    }

}

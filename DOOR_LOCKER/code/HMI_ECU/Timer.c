/*
 * Timer.c
 *
 *  Created on: Nov 1, 2021
 *      Author: Dina Elessawy
 */


#include <avr/io.h>
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/interrupt.h> /* For ICU ISR */
#include "std_types.h"
#include "Timer.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_Timer0CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer1CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer2CallBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect) {
	if (g_Timer0CallBackPtr != NULL_PTR) {
		(*g_Timer0CallBackPtr)();
	}
}

/* Timer0 compare */
ISR(TIMER0_COMP_vect) {
	if (g_Timer0CallBackPtr != NULL_PTR) {
		(*g_Timer0CallBackPtr)();
	}
}

/* Timer1 overflow*/
ISR(TIMER1_OVF_vect) {
	if (g_Timer1CallBackPtr != NULL_PTR) {
		(*g_Timer1CallBackPtr)();
	}
}

/* Timer1 compare */
ISR(TIMER1_COMPA_vect) {
	if (g_Timer1CallBackPtr != NULL_PTR) {
		(*g_Timer1CallBackPtr)();
	}
}

/* Timer2 overflow*/
ISR(TIMER2_OVF_vect) {
	if (g_Timer2CallBackPtr != NULL_PTR) {
		(*g_Timer2CallBackPtr)();
	}
}

/* Timer2 compare */
ISR(TIMER2_COMP_vect) {
	if (g_Timer2CallBackPtr != NULL_PTR) {
		(*g_Timer2CallBackPtr)();
	}
}


void Timer_init(const Timer_ConfigType * Config_Ptr){
	if (Config_Ptr->timer_ID == Timer0){
		TCCR0 &= 0X00;
		TCNT0 &= 0X00;
		OCR0 &= 0X00;
		TIMSK &= 0X00;
		TCNT0 = ( (Config_Ptr->initial_Value) ) & 0XFF;
		TCCR0 = (TCCR0  & 0xF8) | (Config_Ptr->Prescaler);


		switch(Config_Ptr->mode)
		{
		case Normal:


			TCCR0  = CLEAR_BIT(TCCR0 , WGM00);//Clear WGM00 bit in TCCR0 register
			TCCR0  = CLEAR_BIT(TCCR0 , WGM01);//Clear WGM01 bit in TCCR0 register


			TCCR0 = SET_BIT(TCCR0,FOC0);//Make FOC0 to be Active as it is overflow mode


			TIMSK = SET_BIT(TIMSK, TOIE0);//Enable Timer0 overflow interrupt
						break;


		case CTC:
			TCCR0  = CLEAR_BIT(TCCR0 , WGM00);//Clear WGM00 bit in TCCR0 register
			TCCR0  = SET_BIT(TCCR0 , WGM01);//Set WGM01 bit in TCCR0 register

			TCCR0 = SET_BIT(TCCR0,FOC0);//Make FOC0 to be Active as it is overflow mode

			OCR0  = Config_Ptr->Compare_Value; // Set Compare Value

			TIMSK = SET_BIT(TIMSK, OCIE0);//Enable Timer0 overflow interrupt

			break;
		}

	}
	else if (Config_Ptr->timer_ID == Timer1)
	{
		TCCR1A =0;
		TCNT1 = ( (Config_Ptr->initial_Value) ) & 0XFFFF;
		TCCR1B =  (TCCR1B & 0XF8) | (Config_Ptr->Prescaler);
		TCCR1A = TCCR1A & 0X0F;


		switch(Config_Ptr->mode)
					{
					case Normal:

						/*
						 * Normal Overflow mode:
						 *                      Clear WGM10/WMG11 bit in TCCR1A register
						 *                      Clear WGM12/WGM13 bit in TCCR1B register
						 */
						TCCR1A = TCCR1A & 0XFC ;
						TCCR1B = TCCR1B & 0XE7 ;

						/*
						 * Make FOC1A/FOC1B to be Active as it is overflow mode
						 */
						TCCR1A =  SET_BIT(TCCR1A,FOC1A);
						TCCR1A =  SET_BIT(TCCR1A,FOC1B);


						/*
						 * Enable Timer1 overflow interrupt
						 */
						TIMSK = SET_BIT(TIMSK,TOIE1);

						break;


					case CTC:
						/*
						 *  Compare mode:
						 *              Clear WGM10/WGM11 bits in TCCR1A register
						 *              Set WGM12 bit in TCCR1B register
						 *              Clear WGM13 bit in TCCR1B register
						 */
						TCCR1A = TCCR1A & 0XFC ;
						TCCR1B = SET_BIT(TCCR1B, WGM12);
						TCCR1B = CLEAR_BIT(TCCR1B, WGM13);

						/*
						 *  Make FOC1A/FOC1B to be Active as it is compare mode
						 */
						TCCR1A =  SET_BIT(TCCR1A,FOC1A);
						TCCR1A =  SET_BIT(TCCR1A,FOC1B);

						/*
						 * Configure Compare match value for Timer1 to start count from it
						 * 0XFFFF so that value doesn't exceed 16_bits
						 */
						OCR1A = ((Config_Ptr->Compare_Value)) & 0XFFFF;

						/*
						 * Enable Timer1 compare match interrupt
						 */
						TIMSK= SET_BIT(TIMSK,OCIE1A);


						break;
					}

	}
	else if (Config_Ptr->timer_ID == Timer2)
	{


		TCNT2 = ( (Config_Ptr->initial_Value) ) & 0XFF;
		TCCR2 = (TCCR2  & 0XF8) | (Config_Ptr->Prescaler);
		TCCR2  = CLEAR_BIT(TCCR2, COM20);
		TCCR2  = CLEAR_BIT(TCCR2, COM21);

		switch(Config_Ptr->mode)
		{
		case Normal:

			/*
			 * Normal Overflow mode:
			 *                      Clear WGM00 bit in TCCR0 register
			 *                      Clear WGM01 bit in TCCR0 register
			 */
			TCCR2  = CLEAR_BIT(TCCR2 , WGM20);
			TCCR2  = CLEAR_BIT(TCCR2 , WGM21);

			/*
			 * Make FOC2 to be Active as it is overflow mode
			 */
			TCCR2 =  SET_BIT(TCCR2 ,FOC2);


			/*
			 * Enable Timer2 overflow interrupt
			 */
			TIMSK = SET_BIT(TIMSK,TOIE2);

			break;


		case CTC:

			/*
			 *  Compare mode:
			 *               Clear WGM20 bit in TCCR2 register
			 *               Clear WGM21 bit in TCCR2 register
			 */
			TCCR2  = CLEAR_BIT(TCCR2 , WGM20);
			TCCR2  = SET_BIT(TCCR2 , WGM21);

			/*
			 *  Make FOC2 to be Active as it is compare mode
			 */
			TCCR2 =  SET_BIT(TCCR2 , FOC2);
			//g_timeValue=TCNT2;
			/*
			 * Configure compare match value for Timer2 to start count from it
			 * 0XFF so that value doesn't exceed 8_bits
			 */

			OCR2 = ((Config_Ptr->Compare_Value)) & 0XFF;

			/*
			 * Enable Timer2 compare match interrupt
			 */
			TIMSK = SET_BIT(TIMSK, OCIE2);


			break;
		}
}

}

/*
 * Description: Function to set the Call Back function address.
*/
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID timer_type )
{

	switch(timer_type)
	{
	case Timer0:
		/* Save the address of the Call back function in a global variable */
		g_Timer0CallBackPtr = a_ptr;
		break;

	case Timer1:
		/* Save the address of the Call back function in a global variable */
		g_Timer1CallBackPtr = a_ptr;
		break;

	case Timer2:
		/* Save the address of the Call back function in a global variable */
		g_Timer2CallBackPtr = a_ptr;
		break;
	}

}

/*
 * Description: Function to disable the Timer
 */

void Timer_deinit(Timer_ID timer_type)
{
	switch(timer_type)
	{
	case Timer0:
		TCCR0 = 0;
				TCNT0= 0; /* clear initial value */
				OCR0 = 0; /* clear compare value for CTC mode*/
				CLEAR_BIT(TIMSK,OCIE0); /* disable interrupts for CTC mode */
				CLEAR_BIT(TIMSK,TOIE0); /* disable interrupts for overflow mode */
		break;

	case Timer1:

		TCCR1A =0;
				TCCR1B = 0; /* disable clock */
				TCNT1 = 0;
				CLEAR_BIT(TIMSK, TOIE1); /* disable interrupts for overflow mode */
				OCR1A = 0;  /* clear compare value for CTC mode */
				CLEAR_BIT(TIMSK, OCIE1A); /* disable interrupts for CTC mode */
		break;


	case Timer2:

		TCCR2 = 0;
				TCNT2 = 0; /* clear initial value */
				OCR2 = 0; /* clear compare value for CTC mode*/
				CLEAR_BIT(TIMSK, OCIE2); /* disable interrupts for CTC mode */
				CLEAR_BIT(TIMSK, TOIE2); /* disable interrupts for overflow mode */
		break;

	}
}


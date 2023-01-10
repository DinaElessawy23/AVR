/*
 * Timer.h
 *
 *  Created on: Nov 1, 2021
 *      Author: Dina Elessawy
 */

#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	Normal,PWM,CTC,Fast_PWM
}Timer_mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,External_Falling,External_Rising
}Timer_Prescaler;
typedef enum{
	Timer0, Timer1, Timer2
}Timer_ID;

typedef struct
{
	Timer_ID timer_ID;
	Timer_mode mode ;
	Timer_Prescaler Prescaler;
    uint8 initial_Value;
	uint8 Compare_Value;



}Timer_ConfigType;
//extern volatile uint8 g_timeValue;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Timer_init( const Timer_ConfigType * Config_Ptr);
void Timer_setCallBack(void (*a_ptr)(void),Timer_ID timer_type);
void Timer_deinit(Timer_ID timer_type);

#endif /* TIMER_H_ */

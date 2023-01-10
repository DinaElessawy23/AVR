/*
 * buzzer.h
 *
 *  Created on: Nov 1, 2021
 *      Author: Dina Elessawy
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Buzzer_Led_PORT_ID       PORTD_ID

#define Buzzer_PIN_ID            PIN2_ID
#define Led_PIN_ID               PIN3_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
enum buzzer_State
{
	OFF,ON
}Alarm_state;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Buzzer_init(void);
void Buzzer_state(enum buzzer_State Alarm_state);
//void Buzzer_OFF(void);

#endif /* BUZZER_H_ */

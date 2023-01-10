 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.h
 *
 * Created on: Oct 12, 2021
 *
 * Description: header file for the ATmega16 PWM driver
 *
 * Author: Dina Elessawy
 *
 *******************************************************************************/


#ifndef PWM_H_
#define PWM_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define OC0_PORT_ID  PORTB_ID
#define OC0_PIN_ID  PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the DC_Motor driver.
 */
void Timer0_PWM_Init(uint8 duty_cycle);

#endif /* PWM_H_ */

 /******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: DC_Motor.h
 *
 * Created on: Oct 12, 2021
 *
 * Description: header file for the ATmega16 PWM driver
 *
 * Author: Dina Elessawy
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

enum DcMotor_State{
	stop,CW,A_CW
}state;
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_Motor_IN1_PORT_ID       PORTC_ID
#define DC_Motor_IN2_PORT_ID       PORTC_ID

#define DC_Motor_IN1_PIN_ID        PIN4_ID
#define DC_Motor_IN2_PIN_ID        PIN5_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the DC_Motor driver.
 */
void DcMotor_Init(void);

void DcMotor_Rotate(enum DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */

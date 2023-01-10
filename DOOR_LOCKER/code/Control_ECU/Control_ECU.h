/*
 * Control_ECU.h
 *
 *  Created on: Nov 2, 2021
 *      Author: Dina Elessawy
 */

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_




/************************************************************************************************
 *                                     DRIVERS INCLUDES                                         *
 ************************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include"external_eeprom.h"
#include"std_types.h"
#include"UART.h"
#include"common_macros.h"
#include"DC_Motor.h"
#include"Timer.h"
#include"buzzer.h"
#include"twi.h"


/************************************************************************************************
 *                                    DEFINED COMMANDS                                          *
 ************************************************************************************************/

#define READY                                              0x01
#define DONE                                               0x02
#define PASSWORD_SEND                                      0x03
#define PASSWORD_MATCH                                     0x04
#define PASSWORD_NOT_MATCHED                               0x05
#define PASSWORD_CONFIRMATION_SEND                         0x06
#define CHANGE_PASSWORD                                    0x07
#define OPEN_DOOR                                          0x08
#define CHECK_PASSWORD                                     0x09
#define WRONG_PASSWORD                                      0xA
#define CHECK_IF_SAVED                                      0xB
#define YES_SAVED                                           0xC
#define NO_SAVED_PASSWORD                                   0xD

#define FOUR_SECONDS_DELAY                                  4000
#define HALF_SECOND_DELAY                                   500
#define MAX_WRONG_COUNTER                                   3
#define PASSWORD_ARRAY_SIZE                                 5
#define DEFUALT_VALUE_OF_EEPROM                             1


/************************************************************************************************
 *                                 UART & TIMER CONFIGURATIONS                                  *
 ************************************************************************************************/
    /************************** UCSRC Description **************************
    	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
    	 * UPM1:0  = 00 Disable parity bit
    	 * USBS    = 0 One stop bit
    	 * UMSEL   = 0 Asynchronous Operation
    	 * UCSZ1:0 = 11 For 8-bit data mode
    	 * UCPOL   = 0 Used with the Synchronous operation only
    	 ***********************************************************************/

	UART_ConfigType UART_Config = {9600,Disabled,One_Bit,Eight_Bit};

	/* 0: timer_InitialValue
	 * 0: timer_compare_MatchValue
	 * F_CPU_1024 : timer_clock
	 * Compare : timer_mode
	 */
	Timer_ConfigType Timer_config= {Timer0,Normal,F_CPU_1024,0,0};



/************************************************************************************************
 *                                GLOBAL VARIABLES                                              *
 ************************************************************************************************/

uint8 g_password[5];
uint8 g_passmatch[5];
uint8 savedpass[5];
uint8 command;
uint8 g_tick=0;
uint8 g_wrong=0;
uint8 g_calc_sec_flag=0; /*Global variable indicates number of seconds*/

/************************************************************************************************
 *                                   FUNCTIONS                                                  *
 ************************************************************************************************/

/***************************************************************************************************
 * [Function Name]:   recievePassword
 *
 * [Description]:     Function to recieve password that is stored in the global array
 *
 * [Arguments]:       ARRAY of unsigned integers and it's size is 5 (password size)
 *
 * [Returns]:         VOID
 ***************************************************************************************************/
void recievePassword(uint8 a_arr[]);

/***************************************************************************************************
 * [Function Name]:   storePasswordInMemory
 *
 * [Description]:     Function to  store password in the External EEPROM
 *
 * [Arguments]:       VOID
 *
 * [Returns]:         VOID
 ***************************************************************************************************/
void storePasswordInMemory(void);

/***************************************************************************************************
 * [Function Name]:   Match_or_NoMatch
 *
 * [Description]:     Function to recieve password that is stored in the global array
 *
 * [Arguments]:       TWO ARRAYS of unsigned integers and it's size is 5 (password size)
 *
 * [Returns]:         BOOLEAN TRUE OR FALSE
 ***************************************************************************************************/
boolean Match_or_NoMatch(uint8 a_arr1[],uint8 a_arr2[]);

/***************************************************************************************************
 * [Function Name]:   recieveCommand
 *
 * [Description]:     Function to Recieve commands from the HMI ECU Using USART
 *
 * [Arguments]:       VOID
 *
 * [Returns]:         unsigned integer command number
 ***************************************************************************************************/
uint8 recieveCommand(void);

/***************************************************************************************************
 * [Function Name]:   sendCommand
 *
 * [Description]:     Function to Send commands to the hmi ECU Using USART
 *
 * [Arguments]:       unsigned integer command number
 *
 * [Returns]:         VOID
 ***************************************************************************************************/
void sendCommand(uint8 command);

/***************************************************************************************************
 * [Function Name]:   getSavedPassword
 *
 * [Description]:     Function to get the saved password in the EEPROM and store it in a global array
 *
 * [Arguments]:       Array of unsigned integers of size 5 (password size)
 *
 * [Returns]:         VOID
 ***************************************************************************************************/
void getSavedPassword(uint8 a_arr[]);

/* Description :
 * For clock = 8Mhz and prescaler F_CPU/1024 every count will take 128 microsecond
 * so put initial timer counter=0  0 --> 255 (32ms per overflow)
 */

void Calculate_time(void);


#endif /* CONTROL_ECU_H_ */


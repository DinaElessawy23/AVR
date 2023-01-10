/*
 * HMI_ECU.h
 *
 *  Created on: Nov 2, 2021
 *      Author: Dina Elessawy
 */

#ifndef HMI_ECU_H_
#define HMI_ECU_H_
/************************************************************************************************
 *                                     DRIVERS INCLUDES                                         *
 ************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include"lcd.h"
#include"keypad.h"
#include"uart.h"
#include"common_macros.h"
#include"std_types.h"
#include"Timer.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/



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
#define MAX_WRONG_COUNTER                                   3
#define PASSWORD_ARRAY_SIZE 5



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
	UART_ConfigType UART_Config={9600,Disabled,One_Bit,Eight_Bit};

	/* 0: timer_InitialValue
	 * 0: timer_compare_MatchValue
	 * F_CPU_1024 : timer_clock
	 * Compare : timer_mode
	 */
	Timer_ConfigType Timer_config= {Timer0,Normal,F_CPU_1024,0,0};

/************************************************************************************************
 *                                GLOBAL VARIABLES                                              *
 ************************************************************************************************/
	static volatile uint8 g_flag=0;               /*global flag variable to check on */
	static volatile uint8  g_stateNum;            /*global state number of the main function */
	uint8 key;                                  /*global variable to hold the key value */
	uint8 password[5];                          /*global array to store the password in it */
	uint8 command;                                /*global variable to store the commands in it */
	uint8 wrong=0;                              /*global variable to count wrong password entered times*/
	uint8 tick=0;                             /*global ticks to count timer interrupts*/
	uint8 g_calc_sec_flag=0;


	/************************************************************************************************
	 *                                   FUNCTIONS                                                  *
	 ************************************************************************************************/

	/***************************************************************************************************
	 * [Function Name]:   create_StorePassword
	 *
	 * [Description]:     Function to Create and Store password in a global array
	 *
	 * [Arguments]:       VOID
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void create_StorePassword(void);


	/***************************************************************************************************
	 * [Function Name]:   SendPassword
	 *
	 * [Description]:     Function to Send password that is stored in the global array
	 *
	 * [Arguments]:       ARRAY of unsigned integers and it's size is 5 (password size)
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void SendPassword(uint8 a_arr[]);


	/***************************************************************************************************
	 * [Function Name]:   sendCommand
	 *
	 * [Description]:     Function to Send commands to the control ECU Using USART
	 *
	 * [Arguments]:       unsigned integer command number
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void sendCommand(uint8 command);

	/***************************************************************************************************
	 * [Function Name]:   recieveCommand
	 *
	 * [Description]:     Function to Recieve commands from the control ECU Using USART
	 *
	 * [Arguments]:       VOID
	 *
	 * [Returns]:         unsigned integer command number
	 ***************************************************************************************************/
	uint8 recieveCommand(void);

	/***************************************************************************************************
	 * [Function Name]:   mainFucntion
	 *
	 * [Description]:     The main functions of the HMI_ECU that has 2 options either to open the door or
	 *                    to change the password and according to the user decision it send the chosen command
	 *                    to the control ECU
	 *
	 * [Arguments]:       VOID
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void mainFucntion(void);

	/***************************************************************************************************
	 * [Function Name]:   ifPassSavedORNOT
	 *
	 * [Description]:     It checks if it's the user had already entered a password safely and saved
	 *                    in the EEPROM or it's his first time creating a password
	 *
	 * [Arguments]:       VOID
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void ifPassSavedORNOT(void);

	/***************************************************************************************************
	 * [Function Name]:   wrongPasswordScreen
	 *
	 * [Description]:     Function used to display a wrong entered password on screen also count
	 *                    the number of times that the user entered a wrong password
	 *
	 * [Arguments]:       VOID
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void wrongPasswordScreen(void);

	/***************************************************************************************************
	 * [Function Name]:   fill_Password
	 *
	 * [Description]:     Function to Fill in the password from the user using the keypad interfacing
	                      and store it in a global array
	 *
	 * [Arguments]:       ARRAY of unsigned integers and it's size is 5 (password size)
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void fill_Password (uint8 a_arr[]);

	/***************************************************************************************************
	 * [Function Name]:   Password_MISMATCH
	 *
	 * [Description]:     Function to display a message that the password you entered don't match with each other
	 *
	 * [Arguments]:       VOID
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void Password_MISMATCH(void);

	/***************************************************************************************************
	 * [Function Name]:   ALERTscreen
	 *
	 * [Description]:     Function to display a message for 1 minute that the user entered a
	 *                    wrong password for 3 times in row
	 *
	 * [Arguments]:       VOID
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void ALERTscreen(void);

	/***************************************************************************************************
	 * [Function Name]:   doorIsOpeningCloseingScreen
	 *
	 * [Description]:     Function to display a message for 15 seconds that the door is closing
	 *                    and the door is opening for another 15 seconds
	 *
	 * [Arguments]:       VOID
	 *
	 * [Returns]:         VOID
	 ***************************************************************************************************/
	void doorIsOpeningCloseingScreen(void);



	void Calculate_time(void);




	/************************************************************************************************
	 *            ARRAY OF POINTER TO FUNCTIONS THAT TAKE VOID AS AN ARGUMENT AND RETURN VOID       *                                       *
	 ************************************************************************************************/

	void (*ptr_states[3])(void)={create_StorePassword,mainFucntion,doorIsOpeningCloseingScreen};



#endif /* HMI_ECU_H_ */

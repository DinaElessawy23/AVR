/*
 * Control_ECU.c
 *
 *  Created on: Nov 2, 2021
 *      Author: Dina Elessawy
 */



#include"CONTROL_ECU.h"



int main()
{
    UART_init(&UART_Config);
	SREG |= (1<<7);
	Timer_setCallBack(Calculate_time,Timer0);

	/*
	 * 1. After initiation of USART and the I-Bit use switch inside the
	 *    infinite loop and wait for receiving any commands from HMI_ECU
	 * 2.  Case PASSWORD_SEND command:
	 *              receive password and store it in a global array of size 5
	 * 3.  Case PASSWORD_CONFIRMATION_SEND:
	 *              receive the next password entered by the user and make sure that it matches
	 *              the previous one entered
	 *              if it matches:
	 *                            store it in the EEPROM and send command that password match
	 *              if not:
	 *                     send command NOT MATCHING
	 * 4. Case CHECK PASSWORD command:
	 *              receive the password entered by the user and make sure that it matches
	 *              the one stored in the EEPROM(which is already stored in the global array)
	 *              if it matches:
	 *                           send command password match
	 *              if not :
	 *                      send command  wrong password(password not matching)
	 *                      (there is another way to count the number of wrong password entered
	 *                      other than the one i made which is incrementing a global variable
	 *                      in this case every password not matching case and when it comes to 3 i fire
	 *                      an alarm condition to the other ECU but i did the opposite)
	 * 5. Case OPEN DOOR command:
	 *              receive the password entered by the user and compare it with the one saved
	 *              in the EEPROM
	 *              if matches: open the door by setting timer1 also init the motor
	 *              if not :(doing the other solution here as explained above)
	 *              increment the g_wrong variable and if this happened 3 times in a row
	 *              fire an alarm
	 * 6. Case CHECK IF SAVED command:
	 *              to check if it is the first time for the user to enter a password to be saved in
	 *              the EEPROM or it already has a saved password
	 *              if yes there is: send command YES_SAVED
	 *              if not : send command NO_SAVED_PASSWORD
	 */



	while(1){
		switch(recieveCommand())
		{
		case PASSWORD_SEND:
			recievePassword(g_password);
			break;
		case PASSWORD_CONFIRMATION_SEND:
			recievePassword(g_passmatch);
			if(Match_or_NoMatch(g_password,g_passmatch)){
				storePasswordInMemory();
				getSavedPassword(savedpass);
				sendCommand(PASSWORD_MATCH);
			}
			else
			{
				sendCommand(PASSWORD_NOT_MATCHED);
			}
			break;
		case CHECK_PASSWORD:
			recievePassword(g_password);
			getSavedPassword(savedpass);
			if(Match_or_NoMatch(g_password,savedpass))
			{
				sendCommand(PASSWORD_MATCH);
				g_wrong=0;
			}
			else
			{
				sendCommand(PASSWORD_NOT_MATCHED);
			}
			break;
		case OPEN_DOOR:
			DcMotor_Init();
			Timer_init(&Timer_config);
			Timer_setCallBack(Calculate_time,Timer0);
			g_tick =0; /*Initially make the tick equals zero, to start from the beginning*/
			g_calc_sec_flag =0; /*Initially make the sec_flag equals zero,to start from the beginning*/

			while(g_calc_sec_flag != 15)
			{
				DcMotor_Rotate(CW);
			}
			g_tick =0;
			g_calc_sec_flag =0;
			/*As long as it hasn't passed 3 seconds, stop the motor*/
			while(g_calc_sec_flag != 3)
			{
				DcMotor_Rotate(stop);
			}
			g_tick =0;
			g_calc_sec_flag =0;
			/*As long as it hasn't passed 15 seconds, rotate the motor anti-clockwise*/
			while(g_calc_sec_flag != 15){
				DcMotor_Rotate(A_CW);

			}

			DcMotor_Rotate(stop);


			break;
		case WRONG_PASSWORD:
			g_wrong++;
			if(g_wrong==MAX_WRONG_COUNTER)
			{
				 Buzzer_init();
				Timer_init(&Timer_config);
				Timer_setCallBack( Calculate_time,Timer0);
				g_tick =0; /*Initially make the tick equals zero, to start from the beginning*/
				g_calc_sec_flag =0; /*Initially make the sec_flag equals zero,to start from the beginning*/

				while(g_calc_sec_flag != 60)
				{
					Buzzer_state(ON );
				}
				if(g_calc_sec_flag == 60)
				{
					g_wrong=0;
					Buzzer_state(OFF );
				}
			}
			break;
		case CHECK_IF_SAVED:
			getSavedPassword(savedpass);
			uint8 counter=0;
			for(uint8 i = 0 ; i < PASSWORD_ARRAY_SIZE; i++)
			{
				if(savedpass[i] == DEFUALT_VALUE_OF_EEPROM)
				{
					counter++;
				}

			}
			if (counter==PASSWORD_ARRAY_SIZE)
			{
				sendCommand(NO_SAVED_PASSWORD);
			}
			else
			{
				sendCommand(YES_SAVED);
			}
			break;
		}
	}
}

/***************************************************************************************************
 * [Function Name]:   recievePassword
 *
 * [Description]:     Function to receive password that is stored in the global array
 *
 * [Arguments]:       ARRAY of unsigned integers and it's size is 5 (password size)
 *
 * [Returns]:         VOID
 ***************************************************************************************************/
void recievePassword(uint8 a_arr[])
{
	while(UART_recieveByte() != READY){};
	UART_sendByte(READY);
	for(int i=0 ; i<PASSWORD_ARRAY_SIZE ; i++){
		a_arr[i]=UART_recieveByte();
	}
	UART_sendByte(DONE);
}

/***************************************************************************************************
 * [Function Name]:   Match_or_NoMatch
 *
 * [Description]:     Function to receive password that is stored in the global array
 *
 * [Arguments]:       TWO ARRAYS of unsigned integers and it's size is 5 (password size)
 *
 * [Returns]:         BOOLEAN TRUE OR FALSE
 ***************************************************************************************************/
boolean Match_or_NoMatch(uint8 a_arr1[],uint8 a_arr2[])
{
	uint8 counter=0;
	for(uint8 i=0 ; i<PASSWORD_ARRAY_SIZE ; i++)
	{
		if(a_arr1[i]==a_arr2[i]){
			counter++;
		}
	}
	if(counter==PASSWORD_ARRAY_SIZE){
		return TRUE;
	}
	else{
		return FALSE;
	}
}
/***************************************************************************************************
 * [Function Name]:   storePasswordInMemory
 *
 * [Description]:     Function to  store password in the External EEPROM
 *
 * [Arguments]:       VOID
 *
 * [Returns]:         VOID
 ***************************************************************************************************/

void storePasswordInMemory(void)
{

	EEPROM_init();
	for(uint8 i=0;i<PASSWORD_ARRAY_SIZE;i++){
		EEPROM_writeByte(0x0311+i,g_password[i]);
		_delay_ms(HALF_SECOND_DELAY);
	}

}
/***************************************************************************************************
 * [Function Name]:   recieveCommand
 *
 * [Description]:     Function to Receive commands from the HMI ECU Using USART
 *
 * [Arguments]:       VOID
 *
 * [Returns]:         unsigned integer command number
 ***************************************************************************************************/
uint8 recieveCommand(void)
{
	while(UART_recieveByte() != READY){};
	UART_sendByte(READY);
	command=UART_recieveByte();
	UART_sendByte(DONE);
	return command;
}
/***************************************************************************************************
 * [Function Name]:   sendCommand
 *
 * [Description]:     Function to Send commands to the HMI ECU Using USART
 *
 * [Arguments]:       unsigned integer command number
 *
 * [Returns]:         VOID
 ***************************************************************************************************/
void sendCommand(uint8 command)
{
	UART_sendByte(READY);
	while(UART_recieveByte() != READY){};
	UART_sendByte(command);
	while(UART_recieveByte() != DONE){};

}
/***************************************************************************************************
 * [Function Name]:   getSavedPassword
 *
 * [Description]:     Function to get the saved password in the EEPROM and store it in a global array
 *
 * [Arguments]:       Array of unsigned integers of size 5 (password size)
 *
 * [Returns]:         VOID
 ***************************************************************************************************/
void getSavedPassword(uint8 a_arr[])
{
	EEPROM_init();
	for(uint8 i=0 ; i<PASSWORD_ARRAY_SIZE ; i++){
		EEPROM_readByte(0x0311+i, &a_arr[i]);
		_delay_ms(1000);
	}
}

void Calculate_time(void)
{
	g_tick ++; /*Every overflow increase ticks*/

	/*Once ticks become 30(according to the used prescalar),increase seconds flag and tick =0*/
	if(g_tick == 30)
	{
		g_calc_sec_flag ++; /*Every 30 tick, increase seconds flag*/
		g_tick =0; /*Put tick=0 to start counting new second*/
	}
}

